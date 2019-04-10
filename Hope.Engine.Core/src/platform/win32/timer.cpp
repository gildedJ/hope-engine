#include "timer.h"



static uint64 gFrequency;

void Win32_InitTimers()
{
  LARGE_INTEGER frequency;
  QueryPerformanceFrequency(&frequency);
  gFrequency = frequency.QuadPart;
}


uint64 Win32_GetWallClock()
{
  LARGE_INTEGER clockTime;
  QueryPerformanceCounter(&clockTime);
  return clockTime.QuadPart;
}


real32 Win32_GetSecondsElapsed(uint64 start, uint64 end)
{
  return (real32)(end - start) / gFrequency;
}