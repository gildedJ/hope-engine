// PandoranRemains.cpp : Defines the exported functions for the DLL application.
//

#include "../include/PandoranRemains.h"

#include "../Tile.h"
#include "../Camera.h"
#include "../Entity.h"


#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <stdio.h>

#define MAP_WIDTH 16
#define MAP_HEIGHT 9

struct game_state {
  Entity Player;
  Tile Map[MAP_WIDTH * MAP_HEIGHT];
  Camera Camera;
};

Vector2 WrapTileToCameraSpace(Vector2 tilePos, Vector2 cameraPos, Dimension screenSize)
{
  Vector2 position = tilePos - cameraPos;
  while (position.Y > screenSize.Height)
  {
    position.Y -= screenSize.Height;
  }
  while (position.Y < 0) {
    position.Y += screenSize.Height;
  }
  while (position.X < 0)
  {
    position.X += screenSize.Width;
  }
  while (position.X > screenSize.Width) {
    position.X -= screenSize.Width;
  }
  return position;
}

void InitGameState(game_state* state, Dimension screenSize)
{
  Entity player = {};
  player.Position = { 500, 250 };
  player.Velocity = { 0.0f, 0.0f };
  player.Size = { 32.0f, 48.0f };
  player.SpriteOffset = { -player.Size.Width / 2.0f, 0.0f };
  player.Color = Color{ 0.2f, 0.4f, 0.7f, 1.0f };
  player.Collision = Rect(player.SpriteOffset, { player.Size.Width, player.Size.Height / 3.0f });

  state->Player = player;

  Camera camera = {};
  camera.Position = Vector2{ 0.0f, 0.0f };
  camera.Offset = screenSize / 2.0f;
  state->Camera = camera;

  TileType Map[MAP_HEIGHT][MAP_WIDTH] = {
    {WALL,   WALL,    WALL,  WALL,   WALL,   WALL,   WALL,   GROUND, WALL,   WALL,   WALL,   WALL,   WALL,   WALL,   WALL,   WALL},
    {WALL,   EMPTY,  EMPTY,  GROUND, WALL,   GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL},
    {WALL,   EMPTY,  EMPTY,  GROUND, WALL,   WALL,   GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL},
    {WALL,   GROUND, GROUND, GROUND, GROUND, WALL,   GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL},
    {GROUND, GROUND, GROUND, WALL,   GROUND, WALL,   GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND},
    {WALL,   GROUND, GROUND, WALL,   GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL},
    {WALL,   GROUND, GROUND, WALL,   WALL,   GROUND, GROUND, GROUND, GROUND, EMPTY,  EMPTY,  GROUND, GROUND, GROUND, GROUND, WALL},
    {WALL,   GROUND, GROUND, GROUND, WALL,   GROUND, GROUND, GROUND, EMPTY,  EMPTY,  GROUND, GROUND, GROUND, GROUND, GROUND, WALL},
    {WALL,   WALL,   WALL,   WALL,   WALL,   WALL,   WALL,   GROUND, WALL,   WALL,   WALL,   WALL,   WALL,   WALL,   WALL,   WALL}
  };

  uint32 DefaultTileFlags[TILE_TYPE_COUNT] = {};
  DefaultTileFlags[EMPTY] = NONE;
  DefaultTileFlags[WALL] = BLOCKS_MOVEMENT;
  DefaultTileFlags[GROUND] = NONE;
  Color DefaultTypeColors[TILE_TYPE_COUNT] = {};
  DefaultTypeColors[EMPTY] = Color{ 0.0f, 0.0f, 0.0f, 0.0f };
  DefaultTypeColors[WALL] = Color{ 0.3f, 0.3f, 0.3f, 1.0f };
  DefaultTypeColors[GROUND] = Color{ 0.3f, 0.8f, 0.4f, 1.0f };

  Dimension tileSize{ screenSize.Width / (real32)MAP_WIDTH, screenSize.Height / (real32)MAP_HEIGHT };
  Vector2 tileOffset{ -tileSize.Width / 2.0f, -tileSize.Height / 2.0f };
  Rect tileCollision(tileOffset, tileSize);
  for (int y = 0; y < MAP_HEIGHT; y++)
  {
    for (int x = 0; x < MAP_WIDTH; x++)
    {
      Vector2 position{ (real32)x * tileSize.Width, (real32)y  * tileSize.Height };

      Tile tile = {};
      tile.Position = position;
      tile.SpriteOffset = tileOffset;
      tile.Type = Map[y][x];
      if (tile.Type == WALL)
      {
        tile.Collision = tileCollision;
      }
      else {
        tile.Collision = {};
      }
      tile.Size = tileSize;
      tile.Flags = DefaultTileFlags[tile.Type];
      tile.Color = DefaultTypeColors[tile.Type];
      state->Map[y * MAP_WIDTH + x] = tile;
    }
  }
}

GAME_UPDATE_AND_RENDER(GameUpdateAndRender)
{
  // Make sure keyboard_state.Keys array is the right size // Only works because PageDown is the last key in the struct
  Assert((ArrayCount(input->Keyboard.Keys) - 1) == (&input->Keyboard.PageDown - &input->Keyboard.Keys[0]));

  Dimension screenSize = { buffer->width, buffer->height };

  game_state* gameState = (game_state*)memory->PermanentStorage;
  if (!memory->IsInitialized)
  {
    memory->IsInitialized = true;
    InitGameState(gameState, screenSize);
  }

  Vector2* playerPos = &gameState->Player.Position;
  Vector2 PlayerSpeed = { 200.0f, 200.0f };
  Vector2 velocity = {};
  for (int i = 0; i < input->NumGamepads; i++)
  {
    if (input->Gamepads[i].isConnected)
    {
      gamepad_thumbstick leftStick = input->Gamepads[i].state.leftStick;
      velocity.X = (int)(leftStick.x * leftStick.magnitude * dt);
      velocity.Y = (int)(leftStick.y * leftStick.magnitude * dt);
    }
  }
  if (input->Keyboard.W.active) velocity.Y += dt;
  if (input->Keyboard.A.active) velocity.X -= dt;
  if (input->Keyboard.S.active) velocity.Y -= dt;
  if (input->Keyboard.D.active) velocity.X += dt;
  velocity *= PlayerSpeed;
  gameState->Player.Velocity = velocity;

  uint8 collision;
  for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
  {
    Tile tile = gameState->Map[i];
    if (tile.Flags & TileFlags::BLOCKS_MOVEMENT) {
      Rect tileCollision = tile.Collision + tile.Position;
      if (collision = CheckCollision(&gameState->Player, tileCollision))
      {
        ResolveCollision(&gameState->Player, tileCollision, collision);
      }
    }
  }
  gameState->Player.Position += gameState->Player.Velocity;

  gameState->Camera.Position = Lerp(gameState->Camera.Position, gameState->Player.Position - gameState->Camera.Offset, dt);
  Vector2 camPos = gameState->Camera.Position;

  // Clear to black
  Rect screenRect(Vector2{ 0.0f, 0.0f }, Vector2{ (real32)buffer->width, (real32)buffer->height });
  DrawRect(buffer, screenRect, {0, 0, 0, 1});

  // Prepare Mouse Info
  Color mouseColor = {
    input->Mouse.Left.active ? 1.0f : 0.5f,
    input->Mouse.Right.active ? 1.0f : 0.5f,
    input->Mouse.Middle.active ? 1.0f : 0.5f,
    1.0f
  };
  Vector2 mousePos{ input->Mouse.X - 5, (int32)screenRect.Height() - input->Mouse.Y - 5 };
  Vector2 mouseSize{ 10.0f, 10.0f };
  Rect mouseRect(mousePos, mouseSize);

  // Draw Tiles
  Color red = { 1.0f, 0.0f, 0.0f, 1.0f };
  for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
  {
    Tile tile = gameState->Map[i];
    Vector2 tilePos = WrapTileToCameraSpace(tile.Position + tile.SpriteOffset, camPos, screenSize);
    Rect tileRect(tilePos, tile.Size);
    Color tileColor = tile.Color;
    if (tile.Type == GROUND && Intersects(tileRect, Vector2{ input->Mouse.X, (int32)screenRect.Height() - input->Mouse.Y }))
    {
      tileColor = Lerp(tileColor, mouseColor, 0.8f);
    }
    DrawScreenWrappedRect(buffer, tileRect, tileColor);
    if (tile.Flags & TileFlags::BLOCKS_MOVEMENT)
    {
      Rect tileCollision = tile.Collision + tilePos - tile.SpriteOffset;
      DrawBoundingRect(buffer, tileCollision, red);
    }
  }

  // Draw Player
  Entity player = gameState->Player;
  Vector2 drawPos = player.Position + player.SpriteOffset - camPos;
  DrawRect(buffer, Rect(player.Position + player.SpriteOffset - camPos, player.Size), player.Color);
  DrawBoundingRect(buffer, player.Collision + player.Position - camPos, red);

  // Draw Mouse
  DrawRect(buffer, mouseRect, mouseColor);
}