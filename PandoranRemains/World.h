#pragma once

#include "include\math_utils.h"
#include "Tile.h"


struct MapChunk {

  Tile* Tiles;
};

struct World
{
  MapChunk* Chunks;
};

typedef Vector2i TileIndex;
typedef Vector2i ChunkIndex;

struct WorldPosition
{
  Vector2i Absolute;
  Vector2 Relative;

  inline WorldPosition& operator+=(const Vector2& v);
  inline WorldPosition& operator-=(const Vector2& v);
  inline WorldPosition operator+(const Vector2& v) const { WorldPosition result = *this; result += v; return result; }
  inline WorldPosition operator-(const Vector2& v) const { WorldPosition result = *this; result -= v; return result; }
};


void Settle(WorldPosition* position);
ChunkIndex GetChunkIndex(WorldPosition* position);
TileIndex GetTileIndex(WorldPosition* position);
MapChunk* GetMapChunk(World *world, ChunkIndex chunkIndex);
int32 Hash(ChunkIndex index);