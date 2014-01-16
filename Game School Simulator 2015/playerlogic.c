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
    self->owner->space->systems.camera.transform.translation.x -= 4.0f;
  }
  if (input->keyboard.keys[KEY_RIGHT] == ISTATE_DOWN) {
    self->owner->space->systems.camera.transform.translation.x += 4.0f;
  }
  if (input->keyboard.keys[KEY_UP] == ISTATE_DOWN) {
    self->owner->space->systems.camera.transform.translation.y += 4.0f;
  }
  if (input->keyboard.keys[KEY_DOWN] == ISTATE_DOWN) {
    self->owner->space->systems.camera.transform.translation.y -= 4.0f;
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
  if (input->keyboard.keys[KEY_O] == ISTATE_DOWN) {
    self->owner->space->systems.camera.transform.scale.x += 0.1f;
    self->owner->space->systems.camera.transform.scale.y += 0.1f;
  }
  if (input->keyboard.keys[KEY_P] == ISTATE_DOWN) {
    self->owner->space->systems.camera.transform.scale.x -= 0.1f;
    self->owner->space->systems.camera.transform.scale.y -= 0.1f;
  }
}

void comp_playerLogic(COMPONENT *self) {
  COMPONENT_INIT_NULL(self, COMP_PLAYERLOGIC);
  component_depend(self, COMP_TRANSFORM);
  self->events.logicUpdate = comp_playerLogic_logicUpdate;
}
