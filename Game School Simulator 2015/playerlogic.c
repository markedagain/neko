/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "playerLogic.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/entity.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/game.h"

void comp_playerLogic_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  if (input->keyboard.keys[KEY_SPACE]) {
    trans->scale.x *= 1.01f;
    trans->scale.y *= 1.01f;
    trans->rotation += 0.01f;
  }
  if (input->keyboard.keys[KEY_LEFT] == ISTATE_DOWN) {
    trans->translation.x -= 1.0f;
  }
  if (input->keyboard.keys[KEY_RIGHT] == ISTATE_DOWN) {
    trans->translation.x += 1.0f;
  }
  if (input->keyboard.keys[KEY_UP] == ISTATE_DOWN) {
    trans->translation.y += 1.0f;
  }
  if (input->keyboard.keys[KEY_DOWN] == ISTATE_DOWN) {
    trans->translation.y -= 1.0f;
  }
  if (input->keyboard.keys[KEY_A] == ISTATE_PRESSED) {
    trans->translation.x -= 4.0f;
  }
  if (input->keyboard.keys[KEY_D] == ISTATE_PRESSED) {
    trans->translation.x += 4.0f;
  }
  if (input->keyboard.keys[KEY_W] == ISTATE_PRESSED) {
    trans->translation.y += 4.0f;
  }
  if (input->keyboard.keys[KEY_S] == ISTATE_PRESSED) {
    trans->translation.y -= 4.0f;
  }
  /*trans->translation.x = input->mouse.position.x;
  trans->translation.y = input->mouse.position.y;*/
}

void comp_playerLogic(COMPONENT *self) {
  COMPONENT_INIT_NULL(self, COMP_PLAYERLOGIC);
  component_depend(self, COMP_TRANSFORM);
  self->events.logicUpdate = comp_playerLogic_logicUpdate;
}
