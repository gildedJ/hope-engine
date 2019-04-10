#pragma once

#include <xinput.h>

#include "../../input_controller.h"


void Win32_XInput_Init();
void Win32_XInput_UpdateControllers(gamepad_state *controllers, real32 dt);