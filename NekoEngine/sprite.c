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
#include <stdio.h>

void comp_sprite_initialize(COMPONENT *self, void *event) {
  CDATA_SPRITE *comData = (CDATA_SPRITE *)self->data;
}

void comp_sprite_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
}

void comp_sprite_destroy(COMPONENT *self, void *event) {
  CDATA_SPRITE *comData = (CDATA_SPRITE *)self->data;
  if (comData->mesh != NULL)
    AEGfxMeshFree(comData->mesh);
}

void comp_sprite_draw(COMPONENT *self, void *event) {
  CDATA_SPRITE* comData = (CDATA_SPRITE *)self->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  MATRIX3 transform = { 0 };
  VEC3 baseScale = { 0 };
  VEC3 spriteScale = { 0 };
  VEC3 screenScaleVec = { 0 };
  VEC3 camScale = { 0 };
  float screenScale;
  int screenWidth = self->owner->space->game->innerWindow.width;
  int screenHeight = self->owner->space->game->innerWindow.height;
  float screenRadius;
  float spriteRadius;
  float spriteWidth;
  float spriteHeight;
  VEC3 translation;
  SPRITE *sprite = NULL;
  TEXTURE *texture;
  float u, v;

  vec3_copy(&translation, &trans->world.translation);

  if (!comData->visible)
    return;

  if (comData->manual.enabled) {
    texture = (TEXTURE *)dict_get(&self->owner->space->game->data.textures, comData->manual.textureName);
  }
  else {
    sprite = (SPRITE *)dict_get(&self->owner->space->game->data.sprites, comData->source);
    texture = (TEXTURE *)dict_get(&self->owner->space->game->data.textures, sprite->textureName);
  }

  // checks to see if the sprite should be drawn
  screenRadius = (float)(0.5 * sqrt((float)(screenWidth * screenWidth + screenHeight * screenHeight)));
  spriteWidth = comData->manual.enabled ? comData->manual.width : (float)sprite->width;
  spriteHeight = comData->manual.enabled ? comData->manual.height : (float)sprite->height;
  translation.x -= self->owner->space->systems.camera.transform.translation.x;
  translation.y -= self->owner->space->systems.camera.transform.translation.y;
  camScale.x = self->owner->space->systems.camera.transform.scale.x;
  camScale.y = self->owner->space->systems.camera.transform.scale.y;
  translation.x *= camScale.x;
  translation.y *= camScale.y;
  spriteWidth *= camScale.x;
  spriteHeight *= camScale.y;

  baseScale.x = comData->manual.enabled ? comData->manual.width : (float)sprite->width;
  baseScale.y = comData->manual.enabled ? comData->manual.height : (float)sprite->height;
  spriteScale.x = comData->size.x;
  spriteScale.y = comData->size.y;

  if (((float)self->owner->space->game->innerWindow.width / (float)self->owner->space->game->innerWindow.height) <= self->owner->space->game->dimensions.aspectRatio)
    screenScale = (float)self->owner->space->game->innerWindow.width / self->owner->space->game->dimensions.width;
  else
    screenScale = (float)self->owner->space->game->innerWindow.height / self->owner->space->game->dimensions.height;
  translation.x *= screenScale;
  translation.y *= screenScale;
  spriteWidth *= screenScale;
  spriteHeight *= screenScale;
  screenScaleVec.x = screenScale;
  screenScaleVec.y = screenScale;

  spriteRadius = (float)(sqrt(spriteWidth * spriteWidth + spriteHeight * spriteHeight));

  matrix3_identity(&transform);
  matrix3_scale(&transform, &baseScale);
  matrix3_scale(&transform, &spriteScale);
  matrix3_scale(&transform, &camScale);
  matrix3_scale(&transform, &trans->world.scale);
  matrix3_scale(&transform, &screenScaleVec);
  matrix3_rotate(&transform, trans->world.rotation);
  matrix3_translate(&transform, &translation);

  if(vec3_magnitude(&translation) > screenRadius + spriteRadius) {
    return;
  }

  if (comData->source == NULL && !(comData->manual.enabled && comData->manual.textureName != NULL))
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
  else
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
  AEGfxSetTransparency(comData->color.a);
  AEGfxSetTintColor(comData->color.r, comData->color.g, comData->color.b, comData->color.a);
  //AEGfxTextureSet(texture->data, (float)comData->size.x * sprite->u, (float)comData->size.y * sprite->v);

  u = comData->manual.enabled ? comData->manual.u : sprite->u;
  v = comData->manual.enabled ? comData->manual.v : sprite->v;

  AEGfxTextureSet(texture->data, (float)((float)texture->width * u), (float)((float)texture->height * v));
  AEGfxSetTransform(transform.m);
  spriteWidth = comData->manual.enabled ? comData->manual.width : (float)sprite->width;
  spriteHeight = comData->manual.enabled ? comData->manual.height : (float)sprite->height;
  if (comData->mesh == NULL)
    comp_sprite_buildMesh(self, u, v, spriteWidth / (float)texture->width, spriteHeight / (float)texture->height);
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
  data.size.x = 1;
  data.size.y = 1;
  data.visible = true;

  COMPONENT_INIT(self, COMP_SPRITE, data);
  component_depend(self, COMP_TRANSFORM);
  self->events.initialize = comp_sprite_initialize;
  self->events.draw = comp_sprite_draw;
  self->events.logicUpdate = comp_sprite_logicUpdate;
  self->events.destroy = comp_sprite_destroy;
}

void comp_sprite_buildMesh(COMPONENT *self, float u, float v, float width, float height) {
  CDATA_SPRITE *comData = (CDATA_SPRITE *)self->data;

  float u1, v1, u2, v2, w, h;
  w = width * 0.5f;
  h = height * 0.5f;
  u1 = u - w;
  v1 = v - h;

  u2 = u + w;
  v2 = v + h;

	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00FF00FF, u1, v2,
		0.5f,  -0.5f, 0x00FFFF00, u2, v2,
		-0.5f,  0.5f, 0x00F00FFF, u1, v1);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00FFFFFF, u2, v2,
		0.5f,  0.5f, 0x00FFFFFF, u2, v1,
		-0.5f,  0.5f, 0x00FFFFFF, u1, v1);
  comData->mesh = AEGfxMeshEnd();
  AE_ASSERT_MESG(comData->mesh, "Failed to create mesh!");
}

void comp_sprite_clearMesh(COMPONENT *self) {
  CDATA_SPRITE *comData = (CDATA_SPRITE *)self->data;
  if (comData->mesh == NULL)
    return;
  AEGfxMeshFree(comData->mesh);
  comData->mesh = NULL;
}
