#pragma once

#include "types.h"
#include "input.h"

bool WasActiveLastFrame(key k);
bool WasPressedThisFrame(key k);
uint8 TimesPressedThisFrame(key k);
void Toggle(key* k, bool isDown);
void Reset(key* k);
void Reset(keyboard_state* keyboard);
void ProcessKeyToggle(keyboard_state* keyboard, uint32 keyCode, bool isDown);
