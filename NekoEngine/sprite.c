/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdlib.h>
#include <string.h>
#include "sprite.h"
#include "component.h"
#include "entity.h"
#include "transform.h"
#include "../AlphaEngine/AEEngine.h"
#include "util.h"
#include <math.h>

void comp_sprite_initialize(COMPONENT *self, void *event) {
  CDATA_SPRITE *comData = (CDATA_SPRITE *)self->data;
  float w = comData->size.x / 2;
  float h = comData->size.y / 2;

  AEGfxMeshStart();

  
  AEGfxTriAdd(-w, -h, 0xFFFFFFFF, 0.0f, 1.0f,
              w, -h, 0xFFFFFFFF, 1.0f, 1.0f,
              -h, w, 0xFFFFFFFF, 0.0f, 0.0f);
  AEGfxTriAdd( w, -h, 0xFFFFFFFF, 1.0f, 1.0f,
              w,  h, 0xFFFFFFFF, 1.0f, 0.0f,
              -w, h, 0xFFFFFFFF, 0.0f, 0.0f);
  comData->mesh = AEGfxMeshEnd();
  AE_ASSERT_MESG(comData->mesh, "Failed to create mesh!");

  /*if (comData->source != NULL) {
    comData->texture = AEGfxTextureLoad(comData->source);
    AE_ASSERT_MESG(comData->texture, "Failed to load texture!");
  }*/
}

void comp_sprite_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
}

void comp_sprite_destroy(COMPONENT *self, void *event) {
  CDATA_SPRITE *comData = (CDATA_SPRITE *)self->data;
  AEGfxMeshFree(comData->mesh);
}

void comp_sprite_draw(COMPONENT *self, void *event) {
  CDATA_SPRITE* comData = (CDATA_SPRITE *)self->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  MATRIX3 transform = { 0 };
  VEC3 camScale = { 0 };
  int screenWidth = self->owner->space->game->window.width;
  int screenHeight = self->owner->space->game->window.height;
  float screenRadius = (float)(0.5 * sqrt((float)(screenWidth * screenWidth + screenHeight * screenHeight)));
  float spriteRadius = (float)(comData->size.x * comData->size.x + comData->size.y * comData->size.y);
  VEC3 translation = trans->translation;
  VEC3 camTranslate = { 0 };
  SPRITE *sprite;
  AEGfxTexture *texture;

  if (!comData->visible)
    return;

  sprite = (SPRITE *)dict_get(&self->owner->space->game->data.sprites, comData->source);
  texture = sprite->texture->data;

  translation.x -= self->owner->space->systems.camera.transform.translation.x;
  translation.y -= self->owner->space->systems.camera.transform.translation.y;
  camScale.x = self->owner->space->systems.camera.transform.scale.x;
  camScale.y = self->owner->space->systems.camera.transform.scale.y;
  translation.x *= camScale.x;
  translation.y *= camScale.y;

  matrix3_identity(&transform);
  matrix3_scale(&transform, &camScale);
  matrix3_rotate(&transform, trans->rotation);
  matrix3_scale(&transform, &trans->scale);
  matrix3_translate(&transform, &translation);

  if(vec3_magnitude(&translation) > screenRadius + spriteRadius) {
    return;
  }

  if (comData->source == NULL)
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
  else
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
  AEGfxSetTransparency(comData->color.a);
  AEGfxSetTintColor(comData->color.r, comData->color.g, comData->color.b, comData->color.a);
  AEGfxTextureSet(texture, (float)comData->size.x * sprite->u, (float)comData->size.y * sprite->v);
  AEGfxSetTransform(transform.m);
  AEGfxMeshDraw(comData->mesh, AE_GFX_MDM_TRIANGLES);
}

void comp_sprite(COMPONENT *self) {
  CDATA_SPRITE data = { 0 };
  data.mesh = NULL;
  data.source = NULL;
  data.color.r = 1;
  data.color.g = 1;
  data.color.b = 1;
  data.color.a = 1;
  data.size.x = 32;
  data.size.y = 32;
  data.visible = true;

  COMPONENT_INIT(self, COMP_SPRITE, data);
  component_depend(self, COMP_TRANSFORM);
  self->events.initialize = comp_sprite_initialize;
  self->events.draw = comp_sprite_draw;
  self->events.logicUpdate = comp_sprite_logicUpdate;
  self->events.destroy = comp_sprite_destroy;
}