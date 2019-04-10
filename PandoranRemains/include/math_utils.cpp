#include "math_utils.h"

#include "../Entity.h"

uint32 ToValue(Color color)
{
  uint8 alpha = (uint8)(color.Alpha * 255.0f);
  uint8 red = (uint8)(color.Red * 255.0f);
  uint8 green = (uint8)(color.Green * 255.0f);
  uint8 blue = (uint8)(color.Blue * 255.0f);
  uint32 value = (alpha << 24) | (red << 16) | (green << 8) | blue;
  return value;
}

bool Intersects(Rect r1, Rect r2)
{
  bool overlapX = (r1.MaxX > r2.MinX) && (r1.MinX < r2.MaxX);
  bool overlapY = (r1.MaxY > r2.MinY) && (r1.MinY < r2.MaxY);
  bool result = overlapX && overlapY;
  return result;
}

bool Intersects(Rect r, Vector2 v)
{
  bool result = (v.X >= r.MinX && v.X < r.MaxX && v.Y >= r.MinY && v.Y < r.MaxY);
  return result;
}

Vector2 MidPoint(Rect r)
{
  Vector2 result = { (r.MinX + r.MaxX) / 2, (r.MinY + r.MaxY) / 2 };
  return result;
}

real32 Lerp(real32 start, real32 end, real32 dt)
{
  real32 difference = (end - start);
  real32 result = start + difference * dt;
  return result;
}

Vector2 Lerp(Vector2 start, Vector2 end, real32 dt)
{
  Clamp(&dt, 0.0f, 1.0f);
  Vector2 difference = (end - start);
  Vector2 step = difference * dt;
  Vector2 result = start + step;
  return result;
}

Vector4 Lerp(Vector4 start, Vector4 end, real32 dt)
{
  Clamp(&dt, 0.0f, 1.0f);
  Vector4 difference = (end - start);
  Vector4 step = difference * dt;
  Vector4 result = start + step;
  return result;
}

void Clamp(real32* value, real32 min, real32 max)
{
  if (*value < min) { *value = min; }
  if (*value > max) { *value = max; }
}
void Clamp(real64* value, real64 min, real64 max)
{
  if (*value < min) { *value = min; }
  if (*value > max) { *value = max; }
}
void Clamp(int32* value, int32 min, int32 max)
{
  if (*value < min) { *value = min; }
  if (*value > max) { *value = max; }
}
void Clamp(uint32* value, uint32 min, uint32 max)
{
  if (*value < min) { *value = min; }
  if (*value > max) { *value = max; }
}
void Clamp(int64* value, int64 min, int64 max)
{
  if (*value < min) { *value = min; }
  if (*value > max) { *value = max; }
}
void Clamp(uint64* value, uint64 min, uint64 max)
{
  if (*value < min) { *value = min; }
  if (*value > max) { *value = max; }
}