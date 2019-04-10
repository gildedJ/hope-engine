#pragma once

#include "types.h"

struct game_memory {
  uint32 PermanentStorageSize;
  void* PermanentStorage;
  uint32 TransientStorageSize;
  void* TransientStorage;
  bool IsInitialized;
};