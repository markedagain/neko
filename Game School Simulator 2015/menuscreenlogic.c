/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "menuscreenlogic.h"
#include "genericsprite.h"
#include "generictext.h"
#include "UI_button.h"
#include "UI_build.h"

void comp_menuScreenLogic_logicUpdate(COMPONENT *self, void *event) {
}

void comp_menuScreenLogic(COMPONENT *self) {
  COMPONENT_INIT_NULL(self, COMP_MENUSCREENLOGIC);
  self->events.logicUpdate = comp_menuScreenLogic_logicUpdate;
  self->events.initialize = comp_menuScreenLogic_initialize;
}

void comp_menuScreenLogic_initialize(COMPONENT *self, void *event) {
  VEC3 position = { 0 };
  VEC4 color = { 1.0f, 1.0f, 1.0f, 1.0f, };

  ENTITY *created = genericSprite_create(self->owner->space, &position, "menubox", "blank");
  CDATA_UI_BUTTON *buttonData;
  CDATA_SPRITE *spriteData = (CDATA_SPRITE *)entity_getComponentData(created, COMP_SPRITE);
  
  spriteData->size.x = 500.0f;
  spriteData->size.y = 500.0f;

  position.y = 80.0f;
  created = space_addEntityAtPosition(self->owner->space, arch_uibuild, "new_game", &position);
  buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(created, COMP_UI_BUTTON);
  spriteData = (CDATA_SPRITE *)entity_getComponentData(created, COMP_SPRITE);
  spriteData->source = "newgame";
  buttonData->type = BUTTON_NEWGAME;

  position.y = -80.0f;
  position.x = -125.0f;
  created = space_addEntityAtPosition(self->owner->space, arch_uibuild, "new_game", &position);
  buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(created, COMP_UI_BUTTON);
  spriteData = (CDATA_SPRITE *)entity_getComponentData(created, COMP_SPRITE);
  spriteData->source = "options";
  buttonData->type = BUTTON_OPTIONS;

  position.x = 125.0f;
  created = space_addEntityAtPosition(self->owner->space, arch_uibuild, "new_game", &position);
  buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(created, COMP_UI_BUTTON);
  spriteData = (CDATA_SPRITE *)entity_getComponentData(created, COMP_SPRITE);
  spriteData->source = "exit";
  buttonData->type = BUTTON_EXIT;
}
