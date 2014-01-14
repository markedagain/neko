/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "input.h"
#include <stdio.h>

void input_initialize(INPUT_CONTAINER *input) {
  int i;
  for (i = 0; i < KEY_LAST; ++i) {
    input->keyboard.keys[i] = ISTATE_UP;
  }
  for (i = 0; i < MBUTTON_LAST; ++i) {
    input->mouse.buttons[i] = ISTATE_UP;
  }
  input->mouse.position.x = 0;
  input->mouse.position.y = 0;
}

void input_update(INPUT_CONTAINER *input, HWND *window) {
  int i;
  POINT cursorPos;
  for (i = 0; i < KEY_LAST; ++i) {
    input->keyboard.keys[i] = (INPUT_STATE)GetAsyncKeyState(i);
  }
  //GetCursorPos(&input->mouse.position);
  //ScreenToClient(*window, &input->mouse.position);
}