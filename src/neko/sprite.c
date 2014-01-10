/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sprite.h"
#include "component.h"
#include "entity.h"
#include "transform.h"
#include "../alpha/AEEngine.h"
#include "util.h"

void comp_sprite_initialize(COMPONENT *self, void *data) {
  CDATA_SPRITE *comData = (CDATA_SPRITE *)self->data;
  float w = comData->size.x / 2;
  float h = comData->size.y / 2;

  comData->texture = AEGfxTextureLoad(comData->source);
  AE_ASSERT_MESG(comData->texture, "Failed to load texture!");

  AEGfxMeshStart();
  AEGfxTriAdd(-w, -h, 0xFFFFFFFF, 0.0f, 1.0f,
               w, -h, 0xFFFFFFFF, 1.0f, 1.0f,
               -h, w, 0xFFFFFFFF, 0.0f, 0.0f);
  AEGfxTriAdd( w, -h, 0xFFFFFFFF, 1.0f, 1.0f,
               w,  h, 0xFFFFFFFF, 1.0f, 0.0f,
               -w, h, 0xFFFFFFFF, 0.0f, 0.0f);
  comData->mesh = AEGfxMeshEnd();
  AE_ASSERT_MESG(comData->mesh, "Failed to create mesh!");
}

void comp_sprite_logicUpdate(COMPONENT *self, void *data) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)data;
}

void comp_sprite_destroy(COMPONENT *self, void *data) {
  CDATA_SPRITE *comData = (CDATA_SPRITE *)self->data;
  AEGfxMeshFree(comData->mesh);
}

void comp_sprite_draw(COMPONENT *self, void *data) {
  CDATA_SPRITE* comData = (CDATA_SPRITE *)self->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  MATRIX3 transform = { 0 };
  if (!comData->visible)
    return;
  AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
  /*matrix3_identity(&transform);
  matrix3_scale(&transform, vec2_fromVec3(trans->scale));
  matrix3_rotate(&transform, trans->rotation);
  AEGfxSetTransform(transform);*/
  AEGfxSetPosition(trans->translation.x, trans->translation.y);
  AEGfxTextureSet(comData->texture, comData->offset.x, comData->offset.x);
  AEGfxSetTransparency(comData->color.a);
  AEGfxSetTintColor(comData->color.r, comData->color.g, comData->color.b, comData->color.a);
  AEGfxMeshDraw(comData->mesh, AE_GFX_MDM_TRIANGLES);
}

void comp_sprite(COMPONENT *self) {
  CDATA_SPRITE data = { 0 };
  data.mesh = NULL;
  data.source = NULL;
  data.texture = NULL;
  data.color.r = 1;
  data.color.g = 1;
  data.color.b = 1;
  data.color.a = 1;
  data.offset.x = 0;
  data.offset.y = 0;
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