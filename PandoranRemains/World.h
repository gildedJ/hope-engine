#pragma once

#include "include\math_utils.h"
#include "Tile.h"

struct World
{
  real32 TileSizeInMeters; // 5ft
  int32 TileSizeInPixels;

  int32 TileWidth;
  int32 TileHeight;
  
  int32 ChunkWidth;
  int32 ChunkHeight;


  Tile* Tiles;
};

typedef Vector3i ChunkIndex;

struct WorldPosition
{
  ChunkIndex Chunk;
  Vector2 Relative;
};

int32 Hash(ChunkIndex index);