#include "Entity.h"



CollisionFlags CheckCollision(Entity* entity, Rect collidable)
{
  real32 epsilon = 1e-3;

  Rect entityCollision = entity->Collision + entity->Position + entity->Velocity;
  if (collidable.Width() == 0 && collidable.Height() == 0)
  {
    return CollisionFlags::NONE; // non-existant collidable
  }
  if (!Intersects(entityCollision, collidable))
  {
    return CollisionFlags::NONE;
  }

  Rect startingPoint = entity->Collision + entity->Position;
  Vector2 entityMidPoint = MidPoint(startingPoint);
  Vector2 colliableMidPoint = MidPoint(collidable);

  bool biasX = entityMidPoint.X < colliableMidPoint.X;
  bool biasY = entityMidPoint.Y < colliableMidPoint.Y;

  real32 penetrationX = biasX ? (entityCollision.Right - collidable.Left) : (collidable.Right - entityCollision.Left);
  real32 penetrationY = biasY ? (entityCollision.Top - collidable.Bottom) : (collidable.Top - entityCollision.Bottom);
  real32 difference = penetrationX - penetrationY;

  if (difference > epsilon)
  {
    return biasY ? LOWER : UPPER;
  }
  else if (difference < -epsilon)
  {
    return biasX ? LEFT : RIGHT;
  }
  //else {
  //  // Corner collision
  //  return ((biasY ? UPPER : LOWER) | (biasX ? LEFT : RIGHT));
  //}
}

void ResolveCollision(Entity* entity, Rect collidable, uint8 collisionFlags)
{
  real32 epsilon = 0.0f;
  Rect entityCollision = entity->Collision + entity->Position + entity->Velocity;
  if (collisionFlags & UPPER)
  {
    entity->Position.Y +=  collidable.Top - entityCollision.Bottom + epsilon;
    //if (entity->Velocity.Y > 0) entity->Velocity.Y = 0;
  }
  else if (collisionFlags & LOWER)
  {
    entity->Position.Y -= entityCollision.Top - collidable.Bottom + epsilon;
    //if (entity->Velocity.Y < 0) entity->Velocity.Y = 0;
  }

  if (collisionFlags & LEFT)
  {
    entity->Position.X -= entityCollision.Right - collidable.Left + epsilon;
    //if (entity->Velocity.X > 0) entity->Velocity.X = 0;
  }
  else if (collisionFlags & RIGHT)
  {
    entity->Position.X += collidable.Right - entityCollision.Left + epsilon;
    //if (entity->Velocity.X < 0) entity->Velocity.X = 0;
  }
}