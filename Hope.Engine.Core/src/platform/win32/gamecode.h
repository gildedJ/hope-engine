#pragma once

#include "memory.h"
#include "input.h"
#include "graphics.h"
#include "io.h"
#include "PandoranRemains.h"

#include <Windows.h>

struct win32_game_code
{
  HMODULE CodeDLL;

  game_update_and_render* UpdateAndRender;
};


void Win32_LoadGameCode(win32_game_code* code);
void Win32_UnloadGameCode(win32_game_code* code);