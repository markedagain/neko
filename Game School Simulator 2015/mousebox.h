/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_MOUSEBOX__
#define __COMP_MOUSEBOX__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/sprite.h"
#include "../NekoEngine/game.h"
#include <math.h>

#define COMP_MOUSEBOX HASH("COMP_MOUSEBOX")

void comp_mouseBox_logicUpdate(COMPONENT *self, void *event);
void comp_mouseBox(COMPONENT *self);
void comp_mouseBox_initialize(COMPONENT *self, void *event);
void comp_mouseBox_destroy(COMPONENT *self, void *event);
void set_box(COMPONENT *self, float left, float top, float right, float bot);
void check_hover(COMPONENT *self);

typedef struct {
  RECTANGLE box;
  bool hover;
} CDATA_MOUSEBOX;

#endif