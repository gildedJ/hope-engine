#include "input_controller.h"

#include "types.h"

#include <Windows.h>

bool WasActiveLastFrame(key k)
{
  bool oddToggles = k.toggles % 2 == 1;
  return k.active != oddToggles;
}

bool WasPressedThisFrame(key k)
{
  return (k.active && k.toggles > 0) || k.toggles > 1;
}

uint8 TimesPressedThisFrame(key k)
{
  return (k.toggles / 2) + (k.active ? k.toggles % 2 : 0);
}

void Toggle(key* k, bool isDown)
{
  // This can be caused by Alt+Tab
  // Assert(k->active != isDown);
  
  if (k->active != isDown)
  {
    k->active = isDown;
    k->toggles++;
  }
  else 
  {
    // If we got a duplicate state, reset the toggles
    k->toggles = 1;
  }
}

void Reset(key* k)
{
  k->toggles = 0;
}


void Reset(keyboard_state* keyboard)
{
  for (int i = 0; i < ArrayCount(keyboard->Keys); i++)
  {
    Reset(&keyboard->Keys[i]);
  }
}

void ProcessKeyToggle(keyboard_state* keyboard, uint32 keyCode, bool isDown)
{
  switch (keyCode)
  {
  case 'W':
    Toggle(&keyboard->W, isDown);
    break;
  case 'A':
    Toggle(&keyboard->A, isDown);
    break;
  case 'S':
    Toggle(&keyboard->S, isDown);
    break;
  case 'D':
    Toggle(&keyboard->D, isDown);
    break;
  case VK_SPACE:
    Toggle(&keyboard->Space, isDown);
    break;
  case VK_BACK:
    Toggle(&keyboard->Backspace, isDown);
    break;
  case VK_TAB:
    Toggle(&keyboard->Tab, isDown);
    break;
  case VK_RETURN:
    Toggle(&keyboard->Enter, isDown);
    break;
  case VK_LSHIFT:
    Toggle(&keyboard->LeftShift, isDown);
    break;
  case VK_LCONTROL:
    Toggle(&keyboard->LeftCtrl, isDown);
    break;
  case VK_LMENU:
    Toggle(&keyboard->LeftAlt, isDown);
    break;
  case VK_RSHIFT:
    Toggle(&keyboard->RightShift, isDown);
    break;
  case VK_RCONTROL:
    Toggle(&keyboard->RightCtrl, isDown);
    break;
  case VK_RMENU:
    Toggle(&keyboard->RightAlt, isDown);
    break;
  case VK_CAPITAL:
    Toggle(&keyboard->CapsLock, isDown);
    break;
  case VK_ESCAPE:
    Toggle(&keyboard->Escape, isDown);
    break;
  case VK_PRIOR:
    Toggle(&keyboard->PageUp, isDown);
    break;
  case VK_NEXT:
    Toggle(&keyboard->PageDown, isDown);
    break;
  case VK_END:
    Toggle(&keyboard->End, isDown);
    break;
  case VK_HOME:
    Toggle(&keyboard->Home, isDown);
    break;
  case VK_LEFT:
    Toggle(&keyboard->Left, isDown);
    break;
  case VK_RIGHT:
    Toggle(&keyboard->Right, isDown);
    break;
  case VK_UP:
    Toggle(&keyboard->Up, isDown);
    break;
  case VK_DOWN:
    Toggle(&keyboard->Down, isDown);
    break;
  case VK_INSERT:
    Toggle(&keyboard->Insert, isDown);
    break;
  case VK_DELETE:
    Toggle(&keyboard->Delete, isDown);
    break;
  case '0':
    Toggle(&keyboard->Zero, isDown);
    break;
  case '1':
    Toggle(&keyboard->One, isDown);
    break;
  case '2':
    Toggle(&keyboard->Two, isDown);
    break;
  case '3':
    Toggle(&keyboard->Three, isDown);
    break;
  case '4':
    Toggle(&keyboard->Four, isDown);
    break;
  case '5':
    Toggle(&keyboard->Five, isDown);
    break;
  case '6':
    Toggle(&keyboard->Six, isDown);
    break;
  case '7':
    Toggle(&keyboard->Seven, isDown);
    break;
  case '8':
    Toggle(&keyboard->Eight, isDown);
    break;
  case '9':
    Toggle(&keyboard->Nine, isDown);
    break;
  case 'Q':
    Toggle(&keyboard->Q, isDown);
    break;
  case 'E':
    Toggle(&keyboard->E, isDown);
    break;
  case 'R':
    Toggle(&keyboard->R, isDown);
    break;
  case 'T':
    Toggle(&keyboard->T, isDown);
    break;
  case 'Y':
    Toggle(&keyboard->Y, isDown);
    break;
  case 'U':
    Toggle(&keyboard->U, isDown);
    break;
  case 'I':
    Toggle(&keyboard->I, isDown);
    break;
  case 'O':
    Toggle(&keyboard->O, isDown);
    break;
  case 'P':
    Toggle(&keyboard->P, isDown);
    break;
  case 'F':
    Toggle(&keyboard->F, isDown);
    break;
  case 'G':
    Toggle(&keyboard->G, isDown);
    break;
  case 'H':
    Toggle(&keyboard->H, isDown);
    break;
  case 'J':
    Toggle(&keyboard->J, isDown);
    break;
  case 'K':
    Toggle(&keyboard->K, isDown);
    break;
  case 'L':
    Toggle(&keyboard->L, isDown);
    break;
  case 'Z':
    Toggle(&keyboard->Z, isDown);
    break;
  case 'X':
    Toggle(&keyboard->X, isDown);
    break;
  case 'C':
    Toggle(&keyboard->C, isDown);
    break;
  case 'V':
    Toggle(&keyboard->V, isDown);
    break;
  case 'B':
    Toggle(&keyboard->B, isDown);
    break;
  case 'N':
    Toggle(&keyboard->N, isDown);
    break;
  case 'M':
    Toggle(&keyboard->M, isDown);
    break;
  case VK_NUMPAD0:
    Toggle(&keyboard->Num0, isDown);
    break;
  case VK_NUMPAD1:
    Toggle(&keyboard->Num1, isDown);
    break;
  case VK_NUMPAD2:
    Toggle(&keyboard->Num2, isDown);
    break;
  case VK_NUMPAD3:
    Toggle(&keyboard->Num3, isDown);
    break;
  case VK_NUMPAD4:
    Toggle(&keyboard->Num4, isDown);
    break;
  case VK_NUMPAD5:
    Toggle(&keyboard->Num5, isDown);
    break;
  case VK_NUMPAD6:
    Toggle(&keyboard->Num6, isDown);
    break;
  case VK_NUMPAD7:
    Toggle(&keyboard->Num7, isDown);
    break;
  case VK_NUMPAD8:
    Toggle(&keyboard->Num8, isDown);
    break;
  case VK_NUMPAD9:
    Toggle(&keyboard->Num9, isDown);
    break;
  case VK_F1:
    Toggle(&keyboard->F1, isDown);
    break;
  case VK_F2:
    Toggle(&keyboard->F2, isDown);
    break;
  case VK_F3:
    Toggle(&keyboard->F3, isDown);
    break;
  case VK_F4:
    Toggle(&keyboard->F4, isDown);
    break;
  case VK_F5:
    Toggle(&keyboard->F5, isDown);
    break;
  case VK_F6:
    Toggle(&keyboard->F6, isDown);
    break;
  case VK_F7:
    Toggle(&keyboard->F7, isDown);
    break;
  case VK_F8:
    Toggle(&keyboard->F8, isDown);
    break;
  case VK_F9:
    Toggle(&keyboard->F9, isDown);
    break;
  case VK_F10:
    Toggle(&keyboard->F10, isDown);
    break;
  case VK_F11:
    Toggle(&keyboard->F11, isDown);
    break;
  case VK_F12:
    Toggle(&keyboard->F12, isDown);
    break;
  case VK_OEM_COMMA:
    Toggle(&keyboard->Comma, isDown);
    break;
  case VK_OEM_PLUS:
    Toggle(&keyboard->Equals, isDown);
    break;
  case VK_OEM_MINUS:
    Toggle(&keyboard->Minus, isDown);
    break;
  case VK_OEM_PERIOD:
    Toggle(&keyboard->Period, isDown);
    break;
  case VK_OEM_2:
    Toggle(&keyboard->ForwardSlash, isDown);
    break;
  case VK_OEM_3:
    Toggle(&keyboard->Tilde, isDown);
    break;
  case VK_OEM_4:
    Toggle(&keyboard->LeftBracket, isDown);
    break;
  case VK_OEM_5:
    Toggle(&keyboard->Backslash, isDown);
    break;
  case VK_OEM_6:
    Toggle(&keyboard->RightBracket, isDown);
    break;
  case VK_OEM_7:
    Toggle(&keyboard->Apostrophe, isDown);
    break;
  case VK_OEM_8:
    Toggle(&keyboard->SemiColon, isDown);
    break;
  default: break;

  }
}