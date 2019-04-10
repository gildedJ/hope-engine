#pragma once

#include <stdint.h>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef int32 bool32;
typedef int64 bool64;

typedef float real32;
typedef double real64;

#define internal static
#define local_persist static
#define global_variable static

#define Kilobytes(x) ((x) * 1024LL)
#define Megabytes(x) (Kilobytes(x) * 1024LL)
#define Gigabytes(x) (Megabytes(x) * 1024LL)
#define Terabytes(x) (Gigabytes(x) * 1024LL)

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))

#ifdef DEBUG
#define Assert(Expression) \
  if (!(Expression)) {*(int *)0 = 0;}
#else
#define Assert(Expression)
#endif


inline uint32 SafeTruncateUInt64(uint64 value)
{
  Assert(value <= 0xFFFFFFFF);
  uint32 value32 = (uint32)value;
  return value32;
}