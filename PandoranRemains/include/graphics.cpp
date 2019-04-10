#include "graphics.h"
#include "math_utils.h"

void DrawPoint(offscreen_buffer* buffer, int32 x, int32 y, Color color)
{
  uint32* memory = (uint32*)buffer->memory;
  uint32 colorVal = ToValue(color);
  memory[(buffer->height - y - 1) * buffer->width + x] = colorVal;
}

void DrawRect(offscreen_buffer* buffer, Rect rect, Color color)
{
  // Clamp rect to buffer space
  rect.MinX = rect.MinX < 0 ? 0 : rect.MinX;
  rect.MinY = rect.MinY < 0 ? 0 : rect.MinY;
  rect.MaxX = rect.MaxX > buffer->width ? buffer->width : rect.MaxX;
  rect.MaxY = rect.MaxY > buffer->height ? buffer->height : rect.MaxY;

  for (int y = rect.MinY; y < rect.MaxY; y++)
  {
    for (int x = rect.MinX; x < rect.MaxX; x++)
    {
      DrawPoint(buffer, x, y, color);
    }
  }
}


void DrawScreenWrappedRect(offscreen_buffer* buffer, Rect rect, Color color)
{
  for (int j = rect.MinY; j < rect.MaxY; j++)
  {
    for (int i = rect.MinX; i < rect.MaxX; i++)
    {
      int x = i;
      int y = j;
      if (y < 0) { y += buffer->height; }
      if (y >= buffer->height) { y -= buffer->height; }
      if (x < 0) { x += buffer->width; }
      if (x >= buffer->width) { x -= buffer->width; }

      DrawPoint(buffer, x, y, color);
    }
  }
}

void DrawVerticalLine(offscreen_buffer* buffer, Vector2 start, Vector2 end, Color color)
{
  int32 minY = (int32)start.Y;
  int32 maxY = (int32)end.Y;
  if (minY > maxY)
  {
    minY = (int32)end.Y;
    maxY = (int32)start.Y;
  }

  // clip line to buffer
  if (start.X < 0) return;
  if (start.X >= buffer->width) return;
  if (minY < 0) minY = 0;
  if (maxY > buffer->height) maxY = buffer->height;
  if (minY > maxY) return;

  int32 x = (int32)start.X;
  for (int32 y = minY; y < maxY; y++)
  {
    DrawPoint(buffer, x, y, color);
  }
}

void DrawHorizontalLine(offscreen_buffer* buffer, Vector2 start, Vector2 end, Color color)
{
  int32 minX = (int32)start.X;
  int32 maxX = (int32)end.X;
  if (minX > maxX)
  {
    minX = (int32)end.X;
    maxX = (int32)start.X;
  }

  // Clip line to buffer
  if (start.Y < 0) return;
  if (start.Y >= buffer->height) return;
  if (minX < 0) minX = 0;
  if (maxX > buffer->width) maxX = buffer->width;
  if (maxX < minX) return;

  int32 y = (int32)start.Y;
  for (int32 x = minX; x < maxX; x++)
  {
    DrawPoint(buffer, x, y, color);
  }
}

static void _drawLineLow(offscreen_buffer* buffer, Vector2 start, Vector2 end, Color color)
{
  int32 dX = (int32)(end.X - start.X);
  int32 dY = (int32)(end.Y - start.Y);
  int32 yi = 1;
  if (dY < 0)
  {
    yi = -1;
    dY = -dY;
  }
  int32 D = 2 * dY - dX;
  int32 y = (int32)start.Y;
  for (int32 x = (int32)start.X; x < (int32)end.X; x++)
  {
    if (x >= 0 && x < buffer->width && y >= 0 && y < buffer->height)
    {
      DrawPoint(buffer, x, y, color);
    }
    if (D > 0)
    {
      y += yi;
      D -= 2 * dX;
    }
    D += 2 * dY;
  }
}

void _drawLineHigh(offscreen_buffer* buffer, Vector2 start, Vector2 end, Color color)
{
  int32 dX = (int32)(end.X - start.X);
  int32 dY = (int32)(end.Y - start.Y);
  int32 xi = 1;
  if (dX < 0)
  {
    xi = -1;
    dX = -dX;
  }
  int32 D = 2 * dX - dY;
  int32 x = (int32)start.X;
  for (int32 y = (int32)start.Y; y < (int32)end.Y; y++)
  {
    if (x >= 0 && x < buffer->width && y >= 0 && y < buffer->height)
    {
      DrawPoint(buffer, x, y, color);
    }
    if (D > 0)
    {
      x += xi;
      D -= 2 * dY;
    }
    D += 2 * dX;
  }
}

void DrawLine(offscreen_buffer* buffer, Vector2 start, Vector2 end, Color color)
{
  if ((int32)start.X == (int32)end.X)
  {
    DrawVerticalLine(buffer, start, end, color);
  }
  if ((int32)start.Y == (int32)end.Y)
  {
    DrawHorizontalLine(buffer, start, end, color);
  }

  Vector2 delta = end - start;
  if (fabsf(delta.Y) < fabsf(delta.X))
  {
    if (start.X > end.X)
    {
      _drawLineLow(buffer, end, start, color);
    }
    else
    {
      _drawLineLow(buffer, start, end, color);
    }
  }
  else
  {
    if (start.Y > end.Y)
    {
      _drawLineHigh(buffer, end, start, color);
    }
    else
    {
      _drawLineHigh(buffer, end, start, color);
    }
  }
}


void DrawBoundingRect(offscreen_buffer* buffer, Rect rect, Color color)
{
  DrawVerticalLine(buffer, { rect.Left, rect.Top - 1 }, { rect.Left, rect.Bottom }, color);
  DrawHorizontalLine(buffer, { rect.Left + 1, rect.Top - 1 }, { rect.Right - 1, rect.Top - 1 }, color);
  DrawVerticalLine(buffer, { rect.Right - 1, rect.Top - 2 }, { rect.Right - 1, rect.Bottom }, color);
  DrawHorizontalLine(buffer, { rect.Left + 1, rect.Bottom }, { rect.Right - 2, rect.Bottom }, color);
}