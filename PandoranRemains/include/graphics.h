#pragma once

#include "math_utils.h"

struct offscreen_buffer
{
  void *memory;
  int width;
  int height;
  int pitch;
};

void DrawRect(offscreen_buffer* buffer, Rect rect, Color color);
void DrawScreenWrappedRect(offscreen_buffer* buffer, Rect rect, Color color);
void DrawBoundingRect(offscreen_buffer* buffer, Rect rect, Color color);