/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "pausescreenlogic.h"
#include "custombutton.h"
#include "colors.h"
#include "generictext.h"
#include "mousebox.h"

void comp_pauseScreenLogic_frameUpdate(COMPONENT *self, void *event) {
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  
  if (input->keyboard.keys[KEY_Q] == ISTATE_PRESSED) {
    self->owner->space->game->destroying = true;
  }
  
  if (mbox->left.pressed) {
    SPACE *ui = game_getSpace(self->owner->space->game, "ui");
    CDATA_PLAYERLOGIC *playerData = (CDATA_PLAYERLOGIC *)entity_getComponentData(space_getEntity(ui, "player"), COMP_PLAYERLOGIC);
    CDATA_PAUSESCREEN *data = (CDATA_PAUSESCREEN *)self->data;
    ENTITY *pauseText = space_getEntity(self->owner->space, "pauseText");

    playerData->currentMode = data->lastMode;

    if (pauseText)
      entity_destroy(pauseText);

    self->owner->space->game->systems.time.scale = 1;
    entity_destroy(self->owner);
  }
}

void comp_pauseScreenLogic(COMPONENT *self) {
  CDATA_PAUSESCREEN data = { GM_DEFAULT };
  COMPONENT_INIT(self, COMP_PAUSESCREENLOGIC, data);
  self->events.frameUpdate = comp_pauseScreenLogic_frameUpdate;
  self->events.initialize = comp_pauseScreenLogic_initialize;
}

void comp_pauseScreenLogic_initialize(COMPONENT *self, void *event) {
  VEC3 position = { 0 };
  VEC4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
  ENTITY *text = genericText_create(self->owner->space, &position, "pauseText", "fonts/gothic/28", "Click anywhere to continue\nPress Q to quit!", &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);

  sprite->color.a = 0.65f;

  vec4_set(&color, 0, 0, 0, 1.0f);
  spriteText_outline(text, true, &color);

  self->owner->space->game->systems.time.scale = 0;
}
