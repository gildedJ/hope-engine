#pragma once

#ifdef PANDORANREMAINS_EXPORTS
#define PR_API __declspec(dllexport)
#else
#define PR_API __declspec(dllimport)
#endif

#include "types.h"
#include "memory.h"
#include "graphics.h"
#include "input.h"
#include "io.h"
#include "math.h"

struct platform_api
{
  debug_platform_read_entire_file* DEBUGPlatformReadEntireFile;
  debug_platform_write_entire_file* DEBUGPlatformWriteEntireFile;
  debug_platform_free_file_memory* DEBUGPlatformFreeFileMemory;
};


#define GAME_UPDATE_AND_RENDER(name) void name(game_memory* memory, offscreen_buffer *buffer, game_input* input, platform_api* Engine, real32 dt)
typedef GAME_UPDATE_AND_RENDER(game_update_and_render);

extern "C" PR_API GAME_UPDATE_AND_RENDER(GameUpdateAndRender);