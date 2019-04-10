#pragma once

#include "include\math_utils.h"

enum TileType {
  EMPTY = 0,
  GROUND,
  WALL,
  TILE_TYPE_COUNT
};

enum TileFlags {
  BLOCKS_VISION = 1,
  BLOCKS_MOVEMENT = 2,
  IS_TRIGGER = 4
};

struct Tile {
  TileType Type;
  Vector2 Position;
  Dimension Size;
  Vector2 SpriteOffset;
  Color Color;
  Rect Collision;
  bool32 Flags;
};

