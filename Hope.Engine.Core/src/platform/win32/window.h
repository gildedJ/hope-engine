#pragma once

#ifndef UNICODE
#define UNICODE
#endif


#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>


struct win32_offscreen_buffer
{
  BITMAPINFO info;
  void *memory;
  int width;
  int height;
  int pitch;
};
