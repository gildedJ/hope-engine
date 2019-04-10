#pragma once

#include "include\math_utils.h"
#include "World.h"

struct Entity {
  Vector2 Position;
  Dimension Size;
  Vector2 SpriteOffset;
  Color Color;
  Rect Collision;
  Vector2 Velocity;
};


enum CollisionFlags {
  NONE = 0,
  UPPER = 1,
  LOWER = 2,
  LEFT = 4,
  RIGHT = 8
};

CollisionFlags CheckCollision(Entity* entity, Rect collidable);
void ResolveCollision(Entity* entity, Rect collidable, uint8 collisionFlags);