#include "ghostroomlogic.h"
#include "mousebox.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/transform.h"

void comp_ghostRoomLogic_logicUpdate(COMPONENT *self, void *event) {
  SPACE *uiSpace = game_getSpace(self->owner->space->game, "ui");
  ENTITY *cursor = space_getEntity(uiSpace, "cursor");
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  CDATA_TRANSFORM *cursorTrans = (CDATA_TRANSFORM *)entity_getComponentData(cursor, COMP_TRANSFORM);
  VEC3 camTranslate = { 0 };
  SPACE *mg = game_getSpace(self->owner->space->game, "mg");
  VEC3 camScale = { 0 };

  camScale.x = mg->systems.camera.transform.scale.x;
  camScale.y = mg->systems.camera.transform.scale.y;

  camTranslate.x = mg->systems.camera.transform.translation.x;
  camTranslate.y = mg->systems.camera.transform.translation.y;

  

  trans->translation.x = cursorTrans->translation.x + camTranslate.x;
  trans->translation.y = cursorTrans->translation.y + camScale.y * self->owner->space->game->innerWindow.height / 2; //camTranslate.y;


  //printf("%f============%f\n", camTranslate.x, camTranslate.y + cursorTrans->translation.y);
}

void comp_ghostRoomLogic_initialize(COMPONENT *self, void *event) {
  CDATA_GHOSTROOMLOGIC *data = (CDATA_GHOSTROOMLOGIC *)self->data;
  data->constructed = false;
}

void comp_ghostRoomLogic(COMPONENT *self) {
  CDATA_GHOSTROOMLOGIC data = { 0 };
  COMPONENT_INIT(self, COMP_GHOSTROOMLOGIC, data);
  self->events.logicUpdate = comp_ghostRoomLogic_logicUpdate;
  self->events.initialize = comp_ghostRoomLogic_initialize;
}