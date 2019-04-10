#include <windows.h>
#include <math.h>

#include "xinput.h"

//// XInputGetState
#define X_INPUT_GET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_STATE *pState)
typedef X_INPUT_GET_STATE(x_input_get_state);
X_INPUT_GET_STATE(XInputGetStateStub)
{
  return ERROR_DEVICE_NOT_CONNECTED;
}
static x_input_get_state *XInputGetState_ = XInputGetStateStub;
#define XInputGetState XInputGetState_

//// XInputSetState
#define X_INPUT_SET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_VIBRATION *pVibration)
typedef X_INPUT_SET_STATE(x_input_set_state);
X_INPUT_SET_STATE(XInputSetStateStub)
{
  return 0;
}
static x_input_set_state *XInputSetState_ = XInputSetStateStub;
#define XInputSetState XInputSetState_



void Win32_XInput_Init()
{
  HMODULE XInputLibrary = LoadLibrary("xinput1_4.dll");
  if (!XInputLibrary)
  {
	  XInputLibrary = LoadLibrary("xinput1_3.dll");
  }
  if (!XInputLibrary)
  {
	  XInputLibrary = LoadLibrary("xinput9_1_0.dll");
  }
  if (XInputLibrary)
  {
    XInputGetState = (x_input_get_state *)GetProcAddress(XInputLibrary, "XInputGetState");
    XInputSetState = (x_input_set_state *)GetProcAddress(XInputLibrary, "XInputSetState");
  }
}


static void Win32_XInput_UpdateTrigger(gamepad_trigger *trigger, float magnitude)
{
  if (magnitude < XINPUT_GAMEPAD_TRIGGER_THRESHOLD) magnitude = 0;
  else magnitude -= XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
  trigger->magnitude = magnitude / (65534 - XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
}

static void
Win32_XInput_UpdateButton(gamepad_button *button, bool isPressed, real32 dt)
{
  if (isPressed)
  {
    if (button->isPressed)
    {
      button->pressedSeconds += dt;
    }
    else
    {
      button->pressedSeconds = 0;
    }
  }
  else if (!button->isPressed)
  {
     button->pressedSeconds = 0;
  }
  button->isPressed = isPressed;
}

static void
Win32_XInput_UpdateThumbStick(gamepad_thumbstick *stick, float x, float y, SHORT DEADZONE)
{
  float magnitude = (float)sqrt(x*x + y*y);
  float norm_x = x / magnitude;
  float norm_y = y / magnitude;
  float norm_magnitude = 0;
  if (magnitude > DEADZONE)
  {
    if (magnitude > 32767) magnitude = 32767;
    magnitude -= DEADZONE;
    norm_magnitude = magnitude / (32767 - DEADZONE);
  }
  stick->magnitude = norm_magnitude;
  stick->x = norm_x;
  stick->y = norm_y;
}

void
Win32_XInput_UpdateControllers(gamepad_state *controllers, real32 dt)
{
  for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
  {
    gamepad_state *controller = &controllers[i];
    if (!controller->isConnected && controller->lastCheckedSeconds < 5.0f && controller->packetNumber == 1)
    {
      // Less than 5 seconds since last check of this disconnected controller
      controller->lastCheckedSeconds += dt; // mark the passage of time
      continue; // and skip it for now
    }

    XINPUT_STATE state;
    ZeroMemory(&state, sizeof(XINPUT_STATE));
    DWORD result = XInputGetState(i, &state);

    if (result != ERROR_SUCCESS)
    {
      // Controller not connected
      controller->isConnected = false;
      controller->lastCheckedSeconds = 0;
      controller->packetNumber = 1; // differentiates from initial zero state
    }
    else if (controller->packetNumber != state.dwPacketNumber)
    {
      controller->isConnected = true;
      controller->packetNumber = state.dwPacketNumber;
      gamepad *pad = &controller->state;

      Win32_XInput_UpdateThumbStick(&pad->leftStick, state.Gamepad.sThumbLX, state.Gamepad.sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
      Win32_XInput_UpdateThumbStick(&pad->rightStick, state.Gamepad.sThumbRX, state.Gamepad.sThumbRY, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
      
      WORD buttons = state.Gamepad.wButtons;
      Win32_XInput_UpdateButton(&pad->up,            buttons & XINPUT_GAMEPAD_DPAD_UP, dt);
      Win32_XInput_UpdateButton(&pad->down,          buttons & XINPUT_GAMEPAD_DPAD_DOWN, dt);
      Win32_XInput_UpdateButton(&pad->left,          buttons & XINPUT_GAMEPAD_DPAD_LEFT, dt);
      Win32_XInput_UpdateButton(&pad->right,         buttons & XINPUT_GAMEPAD_DPAD_RIGHT, dt);
      Win32_XInput_UpdateButton(&pad->start,         buttons & XINPUT_GAMEPAD_START, dt);
      Win32_XInput_UpdateButton(&pad->back,          buttons & XINPUT_GAMEPAD_BACK, dt);
      Win32_XInput_UpdateButton(&pad->a,             buttons & XINPUT_GAMEPAD_A, dt);
      Win32_XInput_UpdateButton(&pad->b,             buttons & XINPUT_GAMEPAD_B, dt);
      Win32_XInput_UpdateButton(&pad->x,             buttons & XINPUT_GAMEPAD_X, dt);
      Win32_XInput_UpdateButton(&pad->y,             buttons & XINPUT_GAMEPAD_Y, dt);
      Win32_XInput_UpdateButton(&pad->leftShoulder,  buttons & XINPUT_GAMEPAD_LEFT_SHOULDER, dt);
      Win32_XInput_UpdateButton(&pad->rightShoulder, buttons & XINPUT_GAMEPAD_RIGHT_SHOULDER, dt);
      Win32_XInput_UpdateButton(&pad->leftThumb,     buttons & XINPUT_GAMEPAD_LEFT_THUMB, dt);
      Win32_XInput_UpdateButton(&pad->rightThumb,    buttons & XINPUT_GAMEPAD_RIGHT_THUMB, dt);
      
      Win32_XInput_UpdateTrigger(&pad->leftTrigger, state.Gamepad.bLeftTrigger);
      Win32_XInput_UpdateTrigger(&pad->rightTrigger, state.Gamepad.bRightTrigger);
    }
  }
}