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


void comp_managementUpdate(COMPONENT *self, void *event) {
  CDATA_MANAGEMENT *data = (CDATA_MANAGEMENT *)self->data;
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  VEC2 dimensions = { 40.0f, 20.0f };
  VEC3 position = { 10, 10, 0 };
  VEC4 color = { 0, 0, 1, 1 };
  SPACE *uiSpace = game_getSpace(self->owner->space->game, "ui");

  if (mbox->left.down) {
    input->mouse.handled[MBUTTON_LEFT] = 2;
  }

  if (mbox->over) {
    sprite->color.r = min(sprite->color.r + 0.05f, 1);
    sprite->color.b = max(sprite->color.b - 0.05f, 1);
    sprite->color.g = max(sprite->color.g - 0.05f, 0);
  }
  else {
    sprite->color.r = max(sprite->color.r - 0.05f, 0);
    sprite->color.b = min(sprite->color.b + 0.05f, 1);
    sprite->color.g = min(sprite->color.g + 0.05f, 1);
  }
  
  /*if (mbox->entered && data->ent1 == NULL) {
    //vec3_set(&position, &input->mouse.position.x, &input->mouse.position.y, 0);
    data->ent1 = genericSprite_createBlank(uiSpace, &position, &dimensions, &color, "why dad");;
    sprite->color.r = sprite->color.r + 0.5f;
  }
  if (mbox->exited && data->ent1) {
    entity_destroy(data->ent1);
    data->ent1 = NULL;
  }*/
  
  if (mbox->entered && data->ent3 == NULL) {
    vec3_set(&position, 250, 70, 0);
    data->ent3 = genericSprite_create(uiSpace, &position, NULL, "cursor/management");
  }
  else if (mbox->exited && data->ent3) {
    entity_destroy(data->ent3);
    data->ent3 = NULL;
  }

  if(mbox->left.pressed && data->ent2 == NULL) {
    vec3_set(&position, 50, 20, 20);
    data->ent2 = genericSprite_create(uiSpace, &position, NULL, "backgrounds/i_love_you");
  }
  else if(mbox->left.pressed && data->ent2) {
    entity_destroy(data->ent2);
    data->ent2 = NULL;
  }
}

void comp_management(COMPONENT *self) {
  CDATA_MANAGEMENT data = { 0 };
  COMPONENT_INIT(self, COMP_MANAGEMENT, data);
  component_depend(self, COMP_MOUSEBOX);
  self->events.logicUpdate = comp_managementUpdate;
}