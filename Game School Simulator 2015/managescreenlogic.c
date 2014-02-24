/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "management.h"
#include "mousebox.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/generictext.h"
#include "../Nekoengine/spritetext.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/entity.h"
#include "../NekoEngine/sprite.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "playerlogic.h"
#include "roomlogic.h"
#include "UI_build.h"
#include "schoollogic.h"
#include "managescreen.h"
#include "managescreenlogic.h"

void comp_manageScreenLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_MANAGESCREEN *data = (CDATA_MANAGESCREEN *)self->data;
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  SPACE *simSpace = game_getSpace(self->owner->space->game, "sim");
  SPACE *uiSpace = game_getSpace(self->owner->space->game, "ui");
  ENTITY *schoolData = space_getEntity(simSpace, "gameManager");
  CDATA_SCHOOLLOGIC *comData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(schoolData, COMP_SCHOOLLOGIC);
}

void comp_manageScreenLogic(COMPONENT *self) {
  VEC3 position = { 0, 0, 0 };
  VEC4 color = { 0, 0, 1, 1 };
  CDATA_MANAGESCREEN data = { 0 };
  // SPACE *uiSpace = game_getSpace(self->owner->space->game, "ui");
  
  vec3_set(&position, -50, 70, 0);
  //data.leftGPA = genericSprite_create(uiSpace, &position, NULL, "cursor/manage_button_left");
  vec3_set(&position, -50, 70, 0);
  //data.rightGPA = genericSprite_create(uiSpace, &position, NULL, "cursor/manage_button_right");
  COMPONENT_INIT(self, COMP_MANAGESCREENLOGIC, data);
  self->events.logicUpdate = comp_manageScreenLogic_logicUpdate;
}
