#pragma once

#include "types.h"

#include <Windows.h>



void Win32_InitTimers();
uint64 Win32_GetWallClock();
real32 Win32_GetSecondsElapsed(uint64 start, uint64 end);