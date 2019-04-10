#include "World.h"

#define CHUNK_SHIFT 4
#define CHUNK_SIZE (1 << CHUNK_SHIFT)
#define CHUNK_MASK (CHUNK_SIZE - 1)

// 5 feet in meters
#define TILE_SIZE (1.524f)

inline WorldPosition& WorldPosition::operator+=(const Vector2& v)
{
  Relative += v;
  Settle(this);
  return *this;
}

inline WorldPosition& WorldPosition::operator-=(const Vector2& v)
{
  Relative -= v;
  Settle(this);
  return *this;
}


int32 Hash(ChunkIndex index) {
  return 0;
}

void Settle(WorldPosition* position)
{
  int32 xOffset = FloorReal32ToInt32(position->Relative.X / TILE_SIZE);
  position->Absolute.X += xOffset;
  position->Relative.X -= xOffset * TILE_SIZE;

  int32 yOffset = FloorReal32ToInt32(position->Relative.Y / TILE_SIZE);
  position->Absolute.Y += yOffset;
  position->Relative.Y -= yOffset * TILE_SIZE;
}

MapChunk* GetMapChunk(World *world, ChunkIndex chunkIndex)
{
  MapChunk* chunk = &world->Chunks[Hash(chunkIndex)];
  return chunk;
}

ChunkIndex GetChunkIndex(WorldPosition* position)
{
  int x = position->Absolute.X >> CHUNK_SHIFT;
  int y = position->Absolute.Y >> CHUNK_SHIFT;

  return ChunkIndex(x, y);
}

TileIndex GetTileIndex(WorldPosition* position)
{
  int x = position->Absolute.X & CHUNK_MASK;
  int y = position->Absolute.Y & CHUNK_MASK;

  return TileIndex(x, y);
}