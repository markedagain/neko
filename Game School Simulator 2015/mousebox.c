/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "mousebox.h"

void comp_mouseBox_logicUpdate(COMPONENT *self, void *event) {
  CDATA_MOUSEBOX *comData = (CDATA_MOUSEBOX *)self->data;
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  
  // if inactive, don't do anything
  if (!comData->active)
    return;

  if (comData->manual == false)
    set_box_sprite(self);
  else
    adjust_box(self);

  check_status(self);
}

void comp_mouseBox(COMPONENT *self) {
  CDATA_MOUSEBOX data = { 0 };
  COMPONENT_INIT(self, COMP_MOUSEBOX, data);
  self->events.frameUpdate = comp_mouseBox_logicUpdate;
  self->events.initialize = comp_mouseBox_initialize;
}

void comp_mouseBox_initialize(COMPONENT *self, void *event) {
  CDATA_MOUSEBOX *comData = (CDATA_MOUSEBOX *)self->data;
  if (entity_getComponentData(self->owner, COMP_SPRITE) == NULL)
    comData->manual = true;
  else
    comData->manual = false;

  comData->initBox.topLeft.x = 0.0f;
  comData->initBox.topLeft.y = 0.0f;
  comData->initBox.botRight.x = 0.0f;
  comData->initBox.botRight.y = 0.0f;
  comData->active = true;
}


void set_box(COMPONENT *self, float left, float top, float right, float bot) {
  CDATA_MOUSEBOX *data = (CDATA_MOUSEBOX *)self->data;

  data->box.topLeft.x = left;
  data->box.topLeft.y = top;
  data->box.botRight.x = right;
  data->box.botRight.y = bot;
}

// this is not tested
void adjust_box(COMPONENT *self) {
  CDATA_MOUSEBOX *comData = (CDATA_MOUSEBOX *)self->data;
  SPRITE *sprite = NULL;
  VEC3 topLeft;
  VEC3 botRight;
  VEC3 camScale;
  VEC3 screenScaleVec;
  MATRIX3 transform = { 0 };
  float screenScale;
  VEC3 translation;

  translation.x = -self->owner->space->systems.camera.transform.translation.x;
  translation.y = -self->owner->space->systems.camera.transform.translation.y;

  camScale.x = self->owner->space->systems.camera.transform.scale.x;
  camScale.y = self->owner->space->systems.camera.transform.scale.y;

  screenScale = (float)self->owner->space->game->innerWindow.width / self->owner->space->game->dimensions.width;
  screenScaleVec.x = screenScale;
  screenScaleVec.y = screenScale;

  topLeft.x = comData->initBox.topLeft.x;
  topLeft.y = comData->initBox.topLeft.y;
  botRight.x = comData->initBox.botRight.x;
  botRight.y = comData->initBox.botRight.y;

  matrix3_identity(&transform);
  matrix3_scale(&transform, &camScale);
  matrix3_scale(&transform, &screenScaleVec);
  
  matrix3_apply_to_vector(&topLeft, &transform);
  matrix3_apply_to_vector(&botRight, &transform);
  matrix3_apply_to_vector(&translation, &transform);
  matrix3_translate(&transform, &translation);

  set_box(self, topLeft.x, topLeft.y, botRight.x, botRight.y);
}

void set_box_sprite(COMPONENT *self) {
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  CDATA_SPRITE *spriteData = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  SPRITE *sprite = NULL;
  TEXTURE *texture;
  float spriteWidth;
  float spriteHeight;
  VEC3 translation;
  VEC3 topLeft;
  VEC3 botRight;
  VEC3 size;
  VEC3 camScale;
  VEC3 worldScale = trans->world.scale;
  float worldRotation = trans->world.rotation;
  MATRIX3 transform = { 0 };

  if (spriteData->source == 0)
    return;

  size.x = spriteData->size.x;
  size.y = spriteData->size.y;

  camScale.x = self->owner->space->systems.camera.transform.scale.x;
  camScale.y = self->owner->space->systems.camera.transform.scale.y;

  if (spriteData->manual.enabled) {
    texture = (TEXTURE *)dict_get(&self->owner->space->game->data.textures, spriteData->manual.textureName);
  }
  else {
    sprite = (SPRITE *)dict_get(&self->owner->space->game->data.sprites, spriteData->source);
    texture = (TEXTURE *)dict_get(&self->owner->space->game->data.textures, sprite->textureName);
  }
  
  spriteWidth = spriteData->manual.enabled ? spriteData->manual.width : (float)sprite->width;
  spriteHeight = spriteData->manual.enabled ? spriteData->manual.height : (float)sprite->height;

  translation = trans->world.translation;

  topLeft.y = translation.y + spriteHeight / 2;
  topLeft.x = translation.x - spriteWidth / 2;
  botRight.x = translation.x + spriteWidth / 2;
  botRight.y = translation.y - spriteHeight / 2;

  matrix3_identity(&transform);
  matrix3_scale(&transform, &size);
  matrix3_scale(&transform, &camScale);
  matrix3_scale(&transform, &worldScale);
  matrix3_rotate(&transform, worldRotation);

  matrix3_apply_to_vector(&topLeft, &transform);
  matrix3_apply_to_vector(&botRight, &transform);

  set_box(self, topLeft.x, topLeft.y, botRight.x, botRight.y);
}

void check_status(COMPONENT *self) {
  CDATA_MOUSEBOX *data = (CDATA_MOUSEBOX *)self->data;
  POINT mousePos;
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  RECTANGLE box = data->box;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  float posX;
  float posY;

  // translate mouse position to world position
  space_mouseToWorld(self->owner->space, &input->mouse.position, &mousePos);
  
  // reset all mouse states
  data->left.down = false;
  data->left.pressed = false;
  data->left.released = false;
  data->right.down = false;
  data->right.pressed = false;
  data->right.released = false;

  posX = (float)mousePos.x;
  posY = (float)mousePos.y;

  // checks if the mouse if over the object or not
  if ((posX >= box.topLeft.x && posX <= box.botRight.x) && (posY <= box.topLeft.y && posY >= box.botRight.y)) {
    if (data->over != true)
      data->entered = true;
    else
      data->entered = false;
    data->over = true;
  }
  else {
    if (data->entered = true) {
      data->entered = false;
      data->exited = true;
    }
    if (data->over == true)
      data->exited = true;
    else
      data->exited = false;
    data->over = false;
  }

  // if mouse is cuurrently over the object
  if (data->over == true) {
    // check for left mouse input
    switch (input->mouse.left) {
      case ISTATE_DOWN:
        if (!input->mouse.handled[MBUTTON_LEFT]) {
          data->left.down = true;
          if (!data->ghost)
            input->mouse.handled[MBUTTON_LEFT] = true;
        }
        break;
      case ISTATE_PRESSED:
        if (!input->mouse.handled[MBUTTON_LEFT]) {
          data->left.pressed = true;
          if (!data->ghost)
            input->mouse.handled[MBUTTON_LEFT] = true;
        }
        break;
      case ISTATE_RELEASED:
        if (!input->mouse.handled[MBUTTON_LEFT]) {
          data->left.released = true;
          if (!data->ghost)
            input->mouse.handled[MBUTTON_LEFT] = true;
        }
        break;
    }
    // check for right mouse input
    switch (input->mouse.right) {
      case ISTATE_DOWN:
        if (!input->mouse.handled[MBUTTON_RIGHT]) {
          data->right.down = true;
          if (!data->ghost)
            input->mouse.handled[MBUTTON_RIGHT] = true;
        }
        break;
      case ISTATE_PRESSED:
        if (!input->mouse.handled[MBUTTON_RIGHT]) {
          data->right.pressed = true;
          if (!data->ghost)
            input->mouse.handled[MBUTTON_RIGHT] = true;
        }
        break;
      case ISTATE_RELEASED:
        if (!input->mouse.handled[MBUTTON_RIGHT]) {
          data->right.released = true;
          if (!data->ghost)
            input->mouse.handled[MBUTTON_RIGHT] = true;
        }
        break;
    }
  }
}