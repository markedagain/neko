/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "mousebox.h"
#include <stdio.h>

void comp_mouseBox_logicUpdate(COMPONENT *self, void *event) {
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  check_hover(self);
}

void comp_mouseBox(COMPONENT *self) {
  CDATA_MOUSEBOX data = { 0 };
  COMPONENT_INIT(self, COMP_MOUSEBOX, data);
  component_depend(self, COMP_TRANSFORM);
  component_depend(self, COMP_SPRITE);
  self->events.logicUpdate = comp_mouseBox_logicUpdate;
  self->events.destroy = comp_mouseBox_destroy;
  self->events.initialize = comp_mouseBox_initialize;
}

void comp_mouseBox_initialize(COMPONENT *self, void *event) {
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  trans->translation.y += 100.0f;
  set_box_sprite(self);
}

void comp_mouseBox_destroy(COMPONENT *self, void *event) {
}

void set_box(COMPONENT *self, float left, float top, float right, float bot) {
  CDATA_MOUSEBOX *data = (CDATA_MOUSEBOX *)self->data;

  data->box.topLeft.x = left;
  data->box.topLeft.y = top;
  data->box.botRight.x = right;
  data->box.botRight.y = bot;
}

void set_box_sprite(COMPONENT *self) {
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  CDATA_SPRITE *spriteData = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  SPRITE *sprite = NULL;
  TEXTURE *texture;
  float spriteWidth;
  float spriteHeight;
  VEC3 translation;
  float top;
  float left;
  float right;
  float bot;

  if (spriteData->manual.enabled) {
    texture = (TEXTURE *)dict_get(&self->owner->space->game->data.textures, spriteData->manual.textureName);
  }
  else {
    sprite = (SPRITE *)dict_get(&self->owner->space->game->data.sprites, spriteData->source);
    texture = (TEXTURE *)dict_get(&self->owner->space->game->data.textures, sprite->textureName);
  }

  spriteWidth = spriteData->manual.enabled ? spriteData->manual.width : (float)sprite->width;
  spriteHeight = spriteData->manual.enabled ? spriteData->manual.height : (float)sprite->height;

  translation = trans->translation;

  top = translation.y + spriteHeight / 2;
  left = translation.x - spriteWidth / 2;
  right = translation.x + spriteWidth / 2;
  bot = translation.y - spriteHeight / 2;

  set_box(self, left, top, right, bot);
}

void check_hover(COMPONENT *self) {
  CDATA_MOUSEBOX *data = (CDATA_MOUSEBOX *)self->data;
  POINT mousePos;
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  RECTANGLE box = data->box;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  VEC3 translation = trans->translation;
  float posX;
  float posY;

  space_mouseToWorld(self->owner->space, &input->mouse.position, &mousePos);
  
  posX = (float)mousePos.x;
  posY = (float)mousePos.y;

  if (((posX >= box.topLeft.x) && (posX <= box.botRight.x)) && ((posY <= box.topLeft.y) && (posY >= box.botRight.y)))
  {
    printf("%f", translation.y);
    data->hover = true;
  }
  else
    data->hover = false;
}

/******************************************************
  //the following code will print "butts" if the mouse is in the 'box' defined in mousebox and the lmb is down
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  CDATA_MOUSEBOX *data = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  if ((data->hover == true) && (input->mouse.left == ISTATE_DOWN))
    printf("butts");
******************************************************/