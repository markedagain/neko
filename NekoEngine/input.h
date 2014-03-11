/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __INPUT_H__
#define __INPUT_H__

#include <Windows.h>
#include "neko.h"

#define INPUT_MAX_ASCII_KEYS_PER_FRAME 8

typedef enum keyboardKey_t {
  KEY_0 = 0x30,
  KEY_1,
  KEY_2,
  KEY_3,
  KEY_4,
  KEY_5,
  KEY_6,
  KEY_7,
  KEY_8,
  KEY_9,
  KEY_A = 0x41,
  KEY_B,
  KEY_C,
  KEY_D,
  KEY_E,
  KEY_F,
  KEY_G,
  KEY_H,
  KEY_I,
  KEY_J,
  KEY_K,
  KEY_L,
  KEY_M,
  KEY_N,
  KEY_O,
  KEY_P,
  KEY_Q,
  KEY_R,
  KEY_S,
  KEY_T,
  KEY_U,
  KEY_V,
  KEY_W,
  KEY_X,
  KEY_Y,
  KEY_Z,
  KEY_SPACE = 0x20,
  KEY_BACKSPACE = 0x08,
  KEY_TAB,
  KEY_SHIFT = 0x10,
  KEY_CONTROL,
  KEY_ALT,
  KEY_CAPSLOCK = 0x14,
  KEY_NUMLOCK = 0x90,
  KEY_ENTER = 0x0D,
  KEY_LEFTSHIFT = 0xA0,
  KEY_RIGHTSHIFT,
  KEY_LEFTCONTROL,
  KEY_RIGHTCONTROL,
  KEY_ESCAPE = 0x1B,
  KEY_DELETE = 0x2E,
  KEY_LEFT = 0x25,
  KEY_UP,
  KEY_RIGHT,
  KEY_DOWN,
  KEY_NUM0 = 0x60,
  KEY_NUM1,
  KEY_NUM2,
  KEY_NUM3,
  KEY_NUM4,
  KEY_NUM5,
  KEY_NUM6,
  KEY_NUM7,
  KEY_NUM8,
  KEY_NUM9,
  KEY_MULTIPLY,
  KEY_ADD,
  KEY_SEPARATOR,
  KEY_SUBTRACT,
  KEY_DECIMAL,
  KEY_DIVIDE,
  KEY_F1,
  KEY_F2,
  KEY_F3,
  KEY_F4,
  KEY_F5,
  KEY_F6,
  KEY_F7,
  KEY_F8,
  KEY_F9,
  KEY_F10,
  KEY_F11,
  KEY_F12,
  KEY_COLON = 0xBA,
  KEY_EQUALS,
  KEY_COMMA,
  KEY_MINUS,
  KEY_PERIOD,
  KEY_QUESTIONMARK,
  KEY_TILDE,
  KEY_LEFTBRACKET = 0xDB,
  KEY_BACKSLASH,
  KEY_RIGHTBRACKET,
  KEY_QUOTE,  
  KEY_LAST
} KEYBOARD_KEY;

typedef enum {
  ISTATE_UP = 0,
  ISTATE_PRESSED,
  ISTATE_DOWN,
  ISTATE_RELEASED
} INPUT_STATE;

typedef enum {
  MBUTTON_LEFT = 0,
  MBUTTON_MIDDLE,
  MBUTTON_RIGHT,
  MBUTTON_LAST
} MOUSE_BUTTON;

typedef struct inputContainer_t {
  struct {
    union {
      struct {
        INPUT_STATE left;
        INPUT_STATE middle;
        INPUT_STATE right;
      };
      INPUT_STATE buttons[MBUTTON_LAST];
    };
    int buffer[MBUTTON_LAST];
    bool quickClicked[MBUTTON_LAST];
    bool handled[MBUTTON_LAST];
    struct {
      int delta;
      int direction;
    } wheel;
    POINT position;
  } mouse;
  struct {
    INPUT_STATE keys[KEY_LAST];
    char ascii[INPUT_MAX_ASCII_KEYS_PER_FRAME + 1];
    bool anyKey;
  } keyboard;
} INPUT_CONTAINER;

void input_initialize(INPUT_CONTAINER *input);
void input_update(INPUT_CONTAINER *input, HWND *window);
void input_reset_logic(INPUT_CONTAINER *input);
void input_reset_frame(INPUT_CONTAINER *input);
NEKO_API void input_setMousePos(INPUT_CONTAINER *input, int x, int y);
NEKO_API void input_lockMouse(INPUT_CONTAINER *input);
NEKO_API void input_unlockMouse(INPUT_CONTAINER *input);

#endif