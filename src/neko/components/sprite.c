/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdlib.h>
#include <string.h>
#include "sprite.h"
#include "../component.h"
#include "../entity.h"
#include "transform.h"
#include "../../alpha/AEEngine.h"

void comp_sprite_initialize(COMPONENT *self, void *data) {
  CDATA_SPRITE *comData = (CDATA_SPRITE *)self->data;

  comData->texture = AEGfxTextureLoad(comData->source);
  AE_ASSERT_MESG(comData->texture, "Failed to load texture!");

  AEGfxMeshStart();
  AEGfxTriAdd(-32.0f, -32.0f, 0xFFFFFFFF, 0.0f, 1.0f,
               32.0f, -32.0f, 0xFFFFFFFF, 1.0f, 1.0f,
               -32.0f, 32.0f, 0xFFFFFFFF, 0.0f, 0.0f);
  AEGfxTriAdd( 32.0f, -32.0f, 0xFFFFFFFF, 1.0f, 1.0f,
               32.0f,  32.0f, 0xFFFFFFFF, 1.0f, 0.0f,
               -32.0f, 32.0f, 0xFFFFFFFF, 0.0f, 0.0f);
  comData->mesh = AEGfxMeshEnd();
  AE_ASSERT_MESG(comData->mesh, "Failed to create mesh!");
}

void comp_sprite_frameUpdate(COMPONENT *self, void *data) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)data;

}

void comp_sprite_destroy(COMPONENT *self, void *data) {

}

void comp_sprite_draw(COMPONENT *self, void *data) {
  CDATA_SPRITE* comData = (CDATA_SPRITE *)data;
  AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(100.0f, -60.0f);
	// Set texture for object 2
	AEGfxTextureSet(comData->texture, 0.0f, 0.0f);
	AEGfxSetTransparency(1.0f);
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(comData->mesh, AE_GFX_MDM_TRIANGLES);
}

void comp_sprite(COMPONENT *self) {
  CDATA_SPRITE* data = (CDATA_SPRITE *)malloc(sizeof(CDATA_SPRITE));
  data->mesh = NULL;
  data->source = NULL;
  data->texture = NULL;

  COMPONENT_INIT(self, COMP_SPRITE, data);
  self->events.initialize = comp_sprite_initialize;
  self->events.destroy = comp_sprite_destroy;
  self->events.draw = comp_sprite_draw;
  self->events.frameUpdate = comp_sprite_frameUpdate;
  component_depend(self, COMP_TRANSFORM);
}