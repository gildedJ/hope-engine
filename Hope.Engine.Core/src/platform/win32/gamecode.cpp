#include "gamecode.h"


GAME_UPDATE_AND_RENDER(UpdateAndRenderStub) {}


void Win32_LoadGameCode(win32_game_code* code)
{
  // Load DLL
  code->CodeDLL = LoadLibraryA("PandoranRemains.dll");
  if (code->CodeDLL)
  {
    // Update and Render
    code->UpdateAndRender = (game_update_and_render*)GetProcAddress(code->CodeDLL, "GameUpdateAndRender");
    if (!code->UpdateAndRender)
    {
      code->UpdateAndRender = UpdateAndRenderStub;
    }

  }
  else
  {
    // Failed to load dll.  Load all stubs
    code->UpdateAndRender = UpdateAndRenderStub;
  }
}


void Win32_UnloadGameCode(win32_game_code* code)
{
  if (code->CodeDLL)
  {
    FreeLibrary(code->CodeDLL);
    DeleteFile("PandoranRemains_live.dll");
    code->CodeDLL = NULL;
  }
  code->UpdateAndRender = UpdateAndRenderStub;
}