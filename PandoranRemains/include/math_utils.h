#pragma once

#include "types.h"

struct Vector2 {
  Vector2() : X(0.0f), Y(0.0f) {}
  Vector2(const int32& x, const int32& y) : X((real32)x), Y((real32)y) {}
  Vector2(const real32& x, const real32& y) : X(x), Y(y) {}
  union {
    struct {
      real32 X;
      real32 Y;
    };
    struct
    {
      real32 Width;
      real32 Height;
    };
  };
  inline Vector2& operator+=(const Vector2& v) { X += v.X; Y += v.Y; return *this; }
  inline Vector2& operator-=(const Vector2& v) { X -= v.X; Y -= v.Y; return *this; }
  inline Vector2& operator*=(const Vector2& v) { X *= v.X; Y *= v.Y; return *this; }
  inline Vector2& operator*=(const int32& scalar) { X *= scalar; Y *= scalar; return *this; }
  inline Vector2& operator*=(const real32& scalar) { X *= scalar; Y *= scalar; return *this; }
  inline Vector2& operator/=(const Vector2& v) { X /= v.X; Y /= v.Y; return *this; }
  inline Vector2& operator/=(const int32& scalar) { X /= scalar; Y /= scalar; return *this; }
  inline Vector2& operator/=(const real32& scalar) { X /= scalar; Y /= scalar; return *this; }
  inline Vector2 operator+(const Vector2& other) const { Vector2 result = *this; result += other; return result; }
  inline Vector2 operator-(const Vector2& other) const { Vector2 result = *this; result -= other; return result; }
  inline Vector2 operator*(const Vector2& other) const { Vector2 result = *this; result *= other; return result; }
  inline Vector2 operator/(const Vector2& other) const { Vector2 result = *this; result /= other; return result; }
  inline Vector2 operator*(const real32 scalar) const { return Vector2(X * scalar, Y * scalar); }
  inline Vector2 operator*(const int32 scalar) const { return Vector2(X * scalar, Y * scalar); }
  inline Vector2 operator/(const real32 scalar) const { return Vector2(X / scalar, Y / scalar); }
  inline Vector2 operator/(const int32 scalar) const { return Vector2(X / scalar, Y / scalar); }
};

struct Vector2i {
  Vector2i() : X(0), Y(0) {}
  Vector2i(const int32& x, const int32& y) : X(x), Y(y) {}
  Vector2i(const real32& x, const real32& y) : X((int32)x), Y((int32)y) {}

  int32 X;
  int32 Y;

  inline Vector2i& operator+=(const Vector2i& v) { X += v.X; Y += v.Y; return *this; }
  inline Vector2i& operator-=(const Vector2i& v) { X -= v.X; Y -= v.Y; return *this; }
  inline Vector2i& operator*=(const Vector2i& v) { X *= v.X; Y *= v.Y; return *this; }
  inline Vector2i& operator*=(const int32& scalar) { X *= scalar; Y *= scalar; return *this; }
  inline Vector2i& operator*=(const real32& scalar) { X *= scalar; Y *= scalar; return *this; }
  inline Vector2i& operator/=(const Vector2i& v) { X /= v.X; Y /= v.Y; return *this; }
  inline Vector2i& operator/=(const int32& scalar) { X /= scalar; Y /= scalar; return *this; }
  inline Vector2i& operator/=(const real32& scalar) { X /= scalar; Y /= scalar; return *this; }
  inline Vector2i operator+(const Vector2i& other) const { Vector2i result = *this; result += other; return result; }
  inline Vector2i operator-(const Vector2i& other) const { Vector2i result = *this; result -= other; return result; }
  inline Vector2i operator*(const Vector2i& other) const { Vector2i result = *this; result *= other; return result; }
  inline Vector2i operator/(const Vector2i& other) const { Vector2i result = *this; result /= other; return result; }
  inline Vector2i operator*(const real32 scalar) const { return Vector2i(X * scalar, Y * scalar); }
  inline Vector2i operator*(const int32 scalar) const { return Vector2i(X * scalar, Y * scalar); }
  inline Vector2i operator/(const real32 scalar) const { return Vector2i(X / scalar, Y / scalar); }
  inline Vector2i operator/(const int32 scalar) const { return Vector2i(X / scalar, Y / scalar); }
};


typedef Vector2 Dimension;

struct Vector3 {
  Vector3() : X(0.0f), Y(0.0f), Z(0.0f) {}
  Vector3(const int32& x, const int32& y, const int32& z) : X((real32)x), Y((real32)y), Z((real32)z) {}
  Vector3(const real32& x, const real32& y, const real32& z) : X(x), Y(y), Z(z) {}
  union {
    struct {
      real32 X;
      real32 Y;
      real32 Z;
    };
    struct {
      real32 Red;
      real32 Green;
      real32 Blue;
    };
  };

  inline Vector3& operator+=(const Vector3& v) { X += v.X; Y += v.Y; Z += v.Z; return *this; }
  inline Vector3& operator-=(const Vector3& v) { X -= v.X; Y -= v.Y; Z -= v.Z; return *this; }
  inline Vector3& operator*=(const Vector3& v) { X *= v.X; Y *= v.Y; Z *= v.Z; return *this; }
  inline Vector3& operator*=(const int32& scalar) { X *= scalar; Y *= scalar; Z *= scalar; return *this; }
  inline Vector3& operator*=(const real32& scalar) { X *= scalar; Y *= scalar; return *this; }
  inline Vector3& operator/=(const Vector3& v) { X /= v.X; Y /= v.Y; Z /= v.Z; return *this; }
  inline Vector3& operator/=(const int32& scalar) { X /= scalar; Y /= scalar; Z /= scalar; return *this; }
  inline Vector3& operator/=(const real32& scalar) { X /= scalar; Y /= scalar; Z /= scalar; return *this; }
  inline Vector3 operator+(const Vector3& other) const { Vector3 result = *this; result += other; return result; }
  inline Vector3 operator-(const Vector3& other) const { Vector3 result = *this; result -= other; return result; }
  inline Vector3 operator*(const Vector3& other) const { Vector3 result = *this; result *= other; return result; }
  inline Vector3 operator/(const Vector3& other) const { Vector3 result = *this; result /= other; return result; }
  inline Vector3 operator*(const real32 scalar) const { return Vector3(X * scalar, Y * scalar, Z * scalar); }
  inline Vector3 operator*(const int32 scalar) const { return Vector3(X * scalar, Y * scalar, Z * scalar); }
  inline Vector3 operator/(const real32 scalar) const { return Vector3(X / scalar, Y / scalar, Z / scalar); }
  inline Vector3 operator/(const int32 scalar) const { return Vector3(X / scalar, Y / scalar, Z / scalar); }
};

struct Vector3i {
  Vector3i() : X(0), Y(0), Z(0) {}
  Vector3i(const int32& x, const int32& y, const int32& z) : X(x), Y(y), Z(z) {}
  Vector3i(const real32& x, const real32& y, const real32& z) : X((int32)x), Y((int32)y), Z((int32)z) {}

  int32 X;
  int32 Y;
  int32 Z;


  inline Vector3i& operator+=(const Vector3i& v) { X += v.X; Y += v.Y; Z += v.Z; return *this; }
  inline Vector3i& operator-=(const Vector3i& v) { X -= v.X; Y -= v.Y; Z -= v.Z; return *this; }
  inline Vector3i& operator*=(const Vector3i& v) { X *= v.X; Y *= v.Y; Z *= v.Z; return *this; }
  inline Vector3i& operator*=(const int32& scalar) { X *= scalar; Y *= scalar; Z *= scalar; return *this; }
  inline Vector3i& operator*=(const real32& scalar) { X *= scalar; Y *= scalar; return *this; }
  inline Vector3i& operator/=(const Vector3i& v) { X /= v.X; Y /= v.Y; Z /= v.Z; return *this; }
  inline Vector3i& operator/=(const int32& scalar) { X /= scalar; Y /= scalar; Z /= scalar; return *this; }
  inline Vector3i& operator/=(const real32& scalar) { X /= scalar; Y /= scalar; Z /= scalar; return *this; }
  inline Vector3i operator+(const Vector3i& other) const { Vector3i result = *this; result += other; return result; }
  inline Vector3i operator-(const Vector3i& other) const { Vector3i result = *this; result -= other; return result; }
  inline Vector3i operator*(const Vector3i& other) const { Vector3i result = *this; result *= other; return result; }
  inline Vector3i operator/(const Vector3i& other) const { Vector3i result = *this; result /= other; return result; }
  inline Vector3i operator*(const real32 scalar) const { return Vector3i(X * scalar, Y * scalar, Z * scalar); }
  inline Vector3i operator*(const int32 scalar) const { return Vector3i(X * scalar, Y * scalar, Z * scalar); }
  inline Vector3i operator/(const real32 scalar) const { return Vector3i(X / scalar, Y / scalar, Z / scalar); }
  inline Vector3i operator/(const int32 scalar) const { return Vector3i(X / scalar, Y / scalar, Z / scalar); }
};

struct Vector4 {
  Vector4() : X(0.0f), Y(0.0f), Z(0.0f), W(0.0f) {}
  Vector4(const int32& x, const int32& y, const int32& z, const int32& w) : X((real32)x), Y((real32)y), Z((real32)z), W((real32)w) {}
  Vector4(const real32& x, const real32& y, const real32& z, const real32& w) : X(x), Y(y), Z(z), W(w) {}
  union {
    struct {
      real32 X;
      real32 Y;
      real32 Z;
      real32 W;
    };
    struct {
      real32 Red;
      real32 Green;
      real32 Blue;
      real32 Alpha;
    };
  };
  inline Vector4& operator+=(const Vector4& v) { X += v.X; Y += v.Y; Z += v.Z; W += v.W; return *this; }
  inline Vector4& operator-=(const Vector4& v) { X -= v.X; Y -= v.Y; Z -= v.Z; W -= v.W; return *this; }
  inline Vector4& operator*=(const Vector4& v) { X *= v.X; Y *= v.Y; Z *= v.Z; W *= v.W; return *this; }
  inline Vector4& operator*=(const int32& scalar) { X *= scalar; Y *= scalar; Z *= scalar; W *= scalar; return *this; }
  inline Vector4& operator*=(const real32& scalar) { X *= scalar; Y *= scalar; Z *= scalar; W *= scalar; return *this; }
  inline Vector4& operator/=(const Vector4& v) { X /= v.X; Y /= v.Y; Z /= v.Z; W /= v.W; return *this; }
  inline Vector4& operator/=(const int32& scalar) { X /= scalar; Y /= scalar; Z /= scalar; W /= scalar; return *this; }
  inline Vector4& operator/=(const real32& scalar) { X /= scalar; Y /= scalar; Z /= scalar; W /= scalar; return *this; }
  inline Vector4 operator+(const Vector4& other) const { Vector4 result = *this; result += other; return result; }
  inline Vector4 operator-(const Vector4& other) const { Vector4 result = *this; result -= other; return result; }
  inline Vector4 operator*(const Vector4& other) const { Vector4 result = *this; result *= other; return result; }
  inline Vector4 operator/(const Vector4& other) const { Vector4 result = *this; result /= other; return result; }
  inline Vector4 operator*(const real32 scalar) const { return Vector4(X * scalar, Y * scalar, Z * scalar, W * scalar); }
  inline Vector4 operator*(const int32 scalar) const { return Vector4(X * scalar, Y * scalar, Z * scalar, W * scalar); }
  inline Vector4 operator/(const real32 scalar) const { return Vector4(X / scalar, Y / scalar, Z / scalar, W / scalar); }
  inline Vector4 operator/(const int32 scalar) const { return Vector4(X / scalar, Y / scalar, Z / scalar, W / scalar); }
};

typedef Vector4 Quaternion;
typedef Vector4 Color;


uint32 ToValue(Color color);


struct Rect {
  Rect(Vector2 pos, Vector2 size) : Left(pos.X), Top(pos.Y + size.Height), Right(pos.X + size.Width), Bottom(pos.Y) {}
  Rect() : Left(0), Right(0), Top(0), Bottom(0) {}
  union {
    struct {
      real32 Left;
      real32 Top;
      real32 Right;
      real32 Bottom;
    };
    struct {
      real32 MinX;
      real32 MaxY;
      real32 MaxX;
      real32 MinY;
    };
  };
  real32 Width() { return Right - Left; }
  real32 Height() { return Top - Bottom; }
  inline Rect& operator+=(const Vector2& v) { MinX += v.X; MaxX += v.X; MinY += v.Y; MaxY += v.Y; return *this; }
  inline Rect& operator-=(const Vector2& v) { MinX -= v.X; MaxX -= v.X; MinY -= v.Y; MaxY -= v.Y; return *this; }
  inline Rect operator+(const Vector2& v) const { Rect result = *this; result += v; return result; }
  inline Rect operator-(const Vector2& v) const { Rect result = *this; result -= v; return result; }
};

Vector2 MidPoint(Rect r);

bool Intersects(Rect r1, Rect r2);
bool Intersects(Rect r, Vector2 v);

real32 Lerp(real32 start, real32 end, real32 dt);
Vector2 Lerp(Vector2 start, Vector2 end, real32 dt);
Vector4 Lerp(Vector4 start, Vector4 end, real32 dt);

void Clamp(real32* value, real32 min, real32 max);
void Clamp(real64* value, real64 min, real64 max);
void Clamp(int32* value, int32 min, int32 max);
void Clamp(uint32* value, uint32 min, uint32 max);
void Clamp(int64* value, int64 min, int64 max);
void Clamp(uint64* value, uint64 min, uint64 max);

#include <math.h>

inline int32 RoundReal32ToInt32(real32 value)
{
  int32 result = (int32)(value + 0.5f);
  return result;
}

inline uint32 RoundReal32ToUInt32(real32 value)
{
  uint32 result = (uint32)(value + 0.5f);
  return result;
}

inline int32 FloorReal32ToInt32(real32 value)
{
  int32 result = (int32)floorf(value);
  return result;
}

inline int32 TruncateReal32ToInt32(real32 value)
{
  int32 result = (int32)value;
  return result;
}

inline real32 Sin(real32 angle)
{
  real32 result = sinf(angle);
  return result;
}

inline real32 Cos(real32 angle)
{
  real32 result = cosf(angle);
  return result;
}

inline real32 ATan2(real32 y, real32 x)
{
  real32 result = atan2f(y, x);
  return result;
}