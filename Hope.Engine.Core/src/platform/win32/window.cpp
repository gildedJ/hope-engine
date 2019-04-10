
#include "window.h"
#include "PandoranRemains.h"
#include "sound.h"
#include "fileIO.h"
#include "timer.h"
#include "xinput.h"
#include "gamecode.h"

global_variable bool gRunning;
global_variable HWND gWindow;
global_variable win32_offscreen_buffer gBackBuffer;
global_variable HDC gWindowContext;
global_variable SoundSystem sound;


Dimension Win32_GetWindowDimension()
{
  RECT windowRect;
  GetClientRect(gWindow, &windowRect);

  int width = windowRect.right - windowRect.left;
  int height = windowRect.bottom - windowRect.top;

  Dimension dimension = { width, height };

  return dimension;
}


internal void Win32_DisplayBufferInWindow(HDC context, win32_offscreen_buffer buffer)
{
  Dimension window = Win32_GetWindowDimension();
  // TODO aspect ratio correction
  StretchDIBits(context,
    // 0, 0, window.width, window.height,
    0, 0, buffer.width, buffer.height,
    0, 0, buffer.width, buffer.height,
    buffer.memory, &buffer.info,
    DIB_RGB_COLORS, SRCCOPY);
}

////

internal void Win32_ResizeOffscreenBuffer(win32_offscreen_buffer *buffer, int width, int height)
{
  if (buffer->memory)
  {
    VirtualFree(buffer->memory, 0, MEM_RELEASE);
  }

  int bytesPerPixel = 4;

  buffer->width = width;
  buffer->height = height;
  buffer->pitch = width * bytesPerPixel;

  buffer->info.bmiHeader.biSize = sizeof(buffer->info.bmiHeader);
  buffer->info.bmiHeader.biWidth = width;
  buffer->info.bmiHeader.biHeight = -height;
  buffer->info.bmiHeader.biPlanes = 1;
  buffer->info.bmiHeader.biBitCount = 32;
  buffer->info.bmiHeader.biCompression = BI_RGB;

  int bitmapSize = bytesPerPixel * width * height;
  buffer->memory = VirtualAlloc(0, bitmapSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
  // TODO clear to black?
}

////

LRESULT CALLBACK Win32_WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
  LRESULT result = 0;
  switch (message)
  {
  case WM_DESTROY:
  case WM_CLOSE:
    gRunning = false;
    break;
  case WM_PAINT:
  {
    PAINTSTRUCT paint;
    HDC context = BeginPaint(window, &paint);
    Win32_DisplayBufferInWindow(context, gBackBuffer);
    EndPaint(window, &paint);
  }
  break;
  default:
    return DefWindowProc(window, message, wParam, lParam);
  }
  return result;
}

//////////////////////////////////// Main ////////////////////////////////

bool Win32_Create_Window(const WCHAR* title, int width = 1280, int height = 720)
{
  HINSTANCE instance = GetModuleHandle(NULL);

  const wchar_t CLASS_NAME[] = L"Hope Window Class";

  WNDCLASS windowClass = {};
  windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  windowClass.lpfnWndProc = Win32_WindowProc;
  windowClass.hInstance = instance;
  windowClass.lpszClassName = CLASS_NAME;

  if (!RegisterClass(&windowClass))
  {
    // TODO logging
    return NULL;
  }

  gWindow = CreateWindowEx(0,                                // Window Styles
    CLASS_NAME,                       // Window Class
    L"Hope Engine",                   // Window Title
    WS_OVERLAPPEDWINDOW | WS_VISIBLE, // Window Style
    CW_USEDEFAULT, CW_USEDEFAULT,     // Position x,y
    width, height, //CW_USEDEFAULT, CW_USEDEFAULT,     // Size w,h
    NULL,                             // Parent Window
    NULL,                             // Menu
    instance,                         // Instance
    NULL                              // Additional App Data
  );

  if (gWindow == NULL)
  {
    // TODO logging
    return NULL;
  }

  ShowWindow(gWindow, 1);
  ShowCursor(false);

  Win32_ResizeOffscreenBuffer(&gBackBuffer, width, height);

  return true;
}

void Win32_ProcessMessages(keyboard_state* keyboard)
{
  // Deal with Windows Messages
  MSG msg = {};
  Reset(keyboard);
  while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
  {
    switch (msg.message)
    {
    case WM_KEYDOWN:
    case WM_KEYUP:
    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP: {
      uint32 VKCode = (uint32)msg.wParam;
      bool32 wasDown = ((msg.lParam & (1 << 30)) != 0);
      bool32 isDown = ((msg.lParam & (1 << 31)) == 0);
      if (wasDown != isDown)
      {
        ProcessKeyToggle(keyboard, VKCode, isDown);
      }
    }
                      break;
    default:
      TranslateMessage(&msg);
      DispatchMessage(&msg);
      break;
    }
  }
}

void Win32_Init_Graphics()
{
  gWindowContext = GetDC(gWindow);
}





int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR cmdLine, int nCmdShow)
{
  Win32_Create_Window(L"Hope Engine", 960, 540);

  gRunning = true;
  Win32_InitTimers();
  Win32_Init_Graphics();
  Win32_XInput_Init();
  sound.Initialize(gWindow);

  win32_game_code Game;
  Win32_LoadGameCode(&Game);

  platform_api API = {};
  API.DEBUGPlatformFreeFileMemory = DEBUGWin32FreeFileMemory;
  API.DEBUGPlatformReadEntireFile = DEBUGWin32ReadEntireFile;
  API.DEBUGPlatformWriteEntireFile = DEBUGWin32WriteEntireFile;


  game_memory memory = {};
  memory.PermanentStorageSize = Megabytes(64);
  LPVOID TARGET_ADDRESS = (LPVOID)Terabytes(2);
  memory.PermanentStorage = VirtualAlloc(TARGET_ADDRESS, memory.PermanentStorageSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
  Assert(memory.PermanentStorage != NULL);

  memory.TransientStorageSize = Gigabytes(1);
  memory.TransientStorage = VirtualAlloc((uint8*)memory.PermanentStorage + memory.PermanentStorageSize, memory.TransientStorageSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
  Assert(memory.TransientStorage != NULL);


  game_input input = {};
  gamepad_state controllers[XUSER_MAX_COUNT] = {};
  input.Gamepads = controllers;
  input.NumGamepads = XUSER_MAX_COUNT;


  real32 dt = 0.001f;
  const uint8 TARGET_FPS = 60;
  const real32 TARGET_FRAME_TIME = 1.0f / TARGET_FPS;
  uint64 lastTime = Win32_GetWallClock();
  uint64 lastReload = lastTime;
  // Game Loop
  while (gRunning)
  {
    // Reload game dll every 5 seconds
    //if (5.0f < Win32_GetSecondsElapsed(lastReload, lastTime))
    //{
    //  Win32_UnloadGameCode(&Game);
    //  Win32_LoadGameCode(&Game);
    //  lastReload = lastTime;
    //}

    Win32_ProcessMessages(&input.Keyboard);

    // Update XInput State
    Win32_XInput_UpdateControllers(input.Gamepads, dt);

    POINT mousePos;
    if (GetCursorPos(&mousePos))
    {
      if (ScreenToClient(gWindow, &mousePos))
      {
        input.Mouse.X = mousePos.x;
        input.Mouse.Y = mousePos.y;
      }
    }
    input.Mouse.Left.active = GetKeyState(VK_LBUTTON) & (1 << 15);
    input.Mouse.Right.active = GetKeyState(VK_RBUTTON) & (1 << 15);
    input.Mouse.Middle.active = GetKeyState(VK_MBUTTON) & (1 << 15);
    input.Mouse.X1.active = GetKeyState(VK_XBUTTON1) & (1 << 15);
    input.Mouse.X2.active = GetKeyState(VK_XBUTTON2) & (1 << 15);


    // Update &
    // Render
    {
      offscreen_buffer buffer = {};
      buffer.memory = gBackBuffer.memory;
      buffer.width = gBackBuffer.width;
      buffer.height = gBackBuffer.height;
      buffer.pitch = gBackBuffer.pitch;
      Game.UpdateAndRender(&memory, &buffer, &input, &API, dt);
      Win32_DisplayBufferInWindow(gWindowContext, gBackBuffer);
    }

    uint64 currentTime = Win32_GetWallClock();

    dt = Win32_GetSecondsElapsed(lastTime, currentTime);
    if (dt < TARGET_FRAME_TIME)
    {
      DWORD sleepMS = (DWORD)((TARGET_FRAME_TIME - dt) * 940.0f);
      Sleep(sleepMS);
      while (dt < TARGET_FRAME_TIME)
      {
        currentTime = Win32_GetWallClock();
        dt = Win32_GetSecondsElapsed(lastTime, currentTime);
      }
    }
    else
    {
      // Missed frame window
      //Assert(false);
    }

    //wchar_t buffer[256];
    //swprintf(buffer, 256, L"Milliseconds/frame: %fms\n", dt);
    //OutputDebugString(buffer);

    //swprintf(buffer, 256, L"FPS: %f\n\n", 1.0f / dt);
    //OutputDebugString(buffer);

    lastTime = currentTime;
  }

  return 0;
}