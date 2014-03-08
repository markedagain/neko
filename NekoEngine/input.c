/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "input.h"
#include "../AlphaEngine/AESystem.h"
#include <stdio.h>

void input_initialize(INPUT_CONTAINER *input) {
  int i;
  for (i = 0; i < KEY_LAST; ++i)
    input->keyboard.keys[i] = ISTATE_UP;
  for (i = 0; i < MBUTTON_LAST; ++i) {
    input->mouse.buttons[i] = ISTATE_UP;
    input->mouse.handled[i] = false;
    input->mouse.buffer[i] = 0;
    input->mouse.quickClicked[i] = false;
  }
  input->mouse.position.x = 0;
  input->mouse.position.y = 0;
  input->mouse.wheel.delta = 0;
  input->mouse.wheel.direction = 0;
  for (i = 0; i < INPUT_MAX_ASCII_KEYS_PER_FRAME + 1; ++i)
    input->keyboard.ascii[i] = 0;
}

void input_update(INPUT_CONTAINER *input, HWND *window) {
  int i;
  for (i = 0; i < KEY_LAST; ++i) {
    if (GetAsyncKeyState(i))
      input->keyboard.keys[i] = (input->keyboard.keys[i] == ISTATE_UP || input->keyboard.keys[i] == ISTATE_RELEASED ? ISTATE_PRESSED : ISTATE_DOWN);
    else
      input->keyboard.keys[i] = (input->keyboard.keys[i] == ISTATE_DOWN || input->keyboard.keys[i] == ISTATE_PRESSED ? ISTATE_RELEASED : ISTATE_UP);
  }
  for (i = 0; i < MBUTTON_LAST; ++i) {
    if (input->mouse.buffer[i] == 1) {
      input->mouse.buttons[i] = ISTATE_PRESSED;
      input->mouse.buffer[i] = 0;
    }
    else if (input->mouse.buffer[i] == -1) {
      input->mouse.buttons[i] = ISTATE_RELEASED;
      input->mouse.buffer[i] = 0;
    }
    else {
      if (input->mouse.buttons[i] == ISTATE_PRESSED)
        input->mouse.buttons[i] = ISTATE_DOWN;
      if (input->mouse.buttons[i] == ISTATE_RELEASED)
        input->mouse.buttons[i] = ISTATE_UP;
    }
  }
  input->mouse.wheel.direction = input->mouse.wheel.delta > 0 ? 1 : input->mouse.wheel.delta < 0 ? -1 : 0;
  GetCursorPos(&input->mouse.position);
  ScreenToClient(AESysGetWindowHandle(), &input->mouse.position);
}

void input_reset_logic(INPUT_CONTAINER *input) {
  int i;
  for (i = 0; i < MBUTTON_LAST; ++i)
    input->mouse.handled[i] = false;
  for (i = 0; i < INPUT_MAX_ASCII_KEYS_PER_FRAME; ++i)
    input->keyboard.ascii[i] = 0;
}

void input_reset_frame(INPUT_CONTAINER *input) {
  input->mouse.wheel.delta = 0;
  input->mouse.wheel.direction = 0;
}

void input_setMousePos(INPUT_CONTAINER *input, int x, int y) {
  if (AESysGetWindowHandle() == GetActiveWindow()) {
    POINT screenPos = { x, y };
    ClientToScreen(AESysGetWindowHandle(), &screenPos);
    SetCursorPos(screenPos.x, screenPos.y);
    input->mouse.position.x = x;
    input->mouse.position.y = y;
  }
}

void input_lockMouse(INPUT_CONTAINER *input) {
  RECT r;
  GetClientRect(AESysGetWindowHandle(), &r);
  ClientToScreen(AESysGetWindowHandle(), (LPPOINT)&r.left);
  ClientToScreen(AESysGetWindowHandle(), (LPPOINT)&r.right);
  ClipCursor(&r);
}

void input_unlockMouse(INPUT_CONTAINER *input) {
  ClipCursor(NULL);
}