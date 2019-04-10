#pragma once

#include "types.h"

struct DEBUG_read_file_result
{
  uint32 size;
  void *content;
};

#define DEBUG_PLATFORM_READ_ENTIRE_FILE(name) DEBUG_read_file_result name(char* filename)
typedef DEBUG_PLATFORM_READ_ENTIRE_FILE(debug_platform_read_entire_file);

#define DEBUG_PLATFORM_FREE_FILE_MEMORY(name) void name(void* memory)
typedef DEBUG_PLATFORM_FREE_FILE_MEMORY(debug_platform_free_file_memory);

#define DEBUG_PLATFORM_WRITE_ENTIRE_FILE(name) bool32 name(char* filename, uint32 size, void* memory)
typedef DEBUG_PLATFORM_WRITE_ENTIRE_FILE(debug_platform_write_entire_file);

DEBUG_read_file_result DEBUGPlatformReadEntireFile(char* filename);
void DEBUGPlatformFreeFileMemory(void* memory);
bool32 DEBUGPlatformWriteEntireFile(char* filename, uint32 size, void* memory);