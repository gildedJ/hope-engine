#pragma once

#include "types.h"

struct gamepad_thumbstick
{
  real32 x;
  real32 y;
  real32 magnitude;
};

struct gamepad_button
{
  bool isPressed;
  real32 pressedSeconds; // how many seconds this button has been pressed
};

struct gamepad_trigger
{
  real32 magnitude;
};

struct gamepad
{
  gamepad_thumbstick leftStick;
  gamepad_thumbstick rightStick;

  gamepad_trigger leftTrigger;
  gamepad_trigger rightTrigger;

  gamepad_button down;
  gamepad_button right;
  gamepad_button left;
  gamepad_button up;
  gamepad_button x;
  gamepad_button y;
  gamepad_button a;
  gamepad_button b;
  gamepad_button back;
  gamepad_button start;
  gamepad_button rightShoulder;
  gamepad_button leftShoulder;
  gamepad_button leftThumb;
  gamepad_button rightThumb;
};

struct gamepad_state
{
  bool isConnected;
  real32 lastCheckedSeconds; // seconds since last checked
  uint32 packetNumber;
  gamepad state;
};

struct key
{
  bool active;
  uint8 toggles;
};

struct keyboard_state
{
  union {
    key Keys[91];
    struct {
      key W;
      key A;
      key S;
      key D;

      key Left;
      key Right;
      key Up;
      key Down;

      key One;
      key Two;
      key Three;
      key Four;
      key Five;
      key Six;
      key Seven;
      key Eight;
      key Nine;
      key Zero;

      key Q;
      key E;
      key R;
      key T;
      key Y;
      key U;
      key I;
      key O;
      key P;

      key F;
      key G;
      key H;
      key J;
      key K;
      key L;

      key Z;
      key X;
      key C;
      key V;
      key B;
      key N;
      key M;

      key Space;
      key LeftCtrl;
      key LeftAlt;
      key LeftShift;
      key RightShift;
      key RightAlt;
      key RightCtrl;
      key Enter;
      key Escape;
      key Tilde;
      key Tab;
      key CapsLock;
      key Backspace;

      key Period;
      key Comma;
      key ForwardSlash;
      key Backslash;
      key LeftBracket;
      key RightBracket;
      key SemiColon;
      key Apostrophe;
      key Minus;
      key Equals;

      key Num0;
      key Num1;
      key Num2;
      key Num3;
      key Num4;
      key Num5;
      key Num6;
      key Num7;
      key Num8;
      key Num9;

      key F1;
      key F2;
      key F3;
      key F4;
      key F5;
      key F6;
      key F7;
      key F8;
      key F9;
      key F10;
      key F11;
      key F12;

      key Home;
      key End;
      key Delete;
      key Insert;
      key PageUp;
      key PageDown;
    };
  };
};

struct mouse_state
{
  key Left;
  key Right;
  key Middle;
  key X1;
  key X2;
  int32 X;
  int32 Y;
};

struct game_input
{
  mouse_state Mouse;
  keyboard_state Keyboard;
  gamepad_state* Gamepads;
  uint8 NumGamepads;
};