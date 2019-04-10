#include "fileIO.h"


#include <Windows.h>

DEBUG_PLATFORM_READ_ENTIRE_FILE(DEBUGWin32ReadEntireFile)
{
  DEBUG_read_file_result result = {};
  HANDLE fileHandle = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
  if (fileHandle != INVALID_HANDLE_VALUE)
  {
    LARGE_INTEGER fileSize;
    if (GetFileSizeEx(fileHandle, &fileSize))
    {
      result.size = SafeTruncateUInt64(fileSize.QuadPart);
      result.content = VirtualAlloc(0, result.size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
      if (result.content)
      {
        DWORD bytesRead;
        if (!(ReadFile(fileHandle, result.content, result.size, &bytesRead, 0) && (bytesRead == result.size)))
        {
          // If read failed
          DEBUGWin32FreeFileMemory(result.content);
          result.content = NULL;
        }
      }
    }
    CloseHandle(fileHandle);
  }
  return result;
}

DEBUG_PLATFORM_FREE_FILE_MEMORY(DEBUGWin32FreeFileMemory)
{
  if (memory)
  {
    VirtualFree(memory, 0, MEM_RELEASE);
  }
}

DEBUG_PLATFORM_WRITE_ENTIRE_FILE(DEBUGWin32WriteEntireFile)
{
  bool32 result = false;
  HANDLE fileHandle = CreateFileA(filename, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
  if (fileHandle != INVALID_HANDLE_VALUE)
  {
    DWORD bytesWritten;
    if (WriteFile(fileHandle, memory, size, &bytesWritten, 0) && (bytesWritten == size))
    {
      result = true;
    }
    else
    {
      // If write failed... TODO add logging?
    }
    CloseHandle(fileHandle);
  }
  return result;
}
