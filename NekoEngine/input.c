/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "input.h"

void input_update(INPUT_CONTAINER *input, HWND *window) {
  int i;
  POINT cursorPos;
  for (i = 0; i < KEY_LAST; ++i) {
    input->keyboard.keys[i] = (INPUT_STATE)GetAsyncKeyState(input_keyboardMap[i]);
  }
  //GetCursorPos(&input->mouse.position);
  //ScreenToClient(*window, &input->mouse.position);
}