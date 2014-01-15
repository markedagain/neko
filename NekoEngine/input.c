/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "input.h"
#include "../AlphaEngine/AESystem.h"

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
  for (i = 0; i < KEY_LAST; ++i) {
    if (GetAsyncKeyState(i))
      input->keyboard.keys[i] = (input->keyboard.keys[i] == ISTATE_UP || input->keyboard.keys[i] == ISTATE_RELEASED ? ISTATE_PRESSED : ISTATE_DOWN);
    else
      input->keyboard.keys[i] = (input->keyboard.keys[i] == ISTATE_DOWN || input->keyboard.keys[i] == ISTATE_PRESSED ? ISTATE_RELEASED : ISTATE_UP);
  }
  GetCursorPos(&input->mouse.position);
  ScreenToClient(AESysGetWindowHandle(), &input->mouse.position);
}