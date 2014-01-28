/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "spritetext.h"
#include "entity.h"
#include "transform.h"
#include "vectormath.h"
#include "dictionary.h"
#include <stdio.h>

void comp_spriteText_initialize(COMPONENT *self, void *event) {
  CDATA_SPRITETEXT *data = (CDATA_SPRITETEXT *)self->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  CDATA_MULTISPRITE *multi = (CDATA_MULTISPRITE *)entity_getComponentData(self->owner, COMP_MULTISPRITE);
  TEXTURE *texture = (TEXTURE *)dict_get(&self->owner->space->game->data.textures, data->font);
  POINT fontSize = { texture->width / 16, texture->height / 16 }; // TODO: Make this dynamic, based on texture size
  VEC2 offset = { (float)fontSize.x / 2.0f, -(float)fontSize.y / 2.0f };
  int i;



  for (i = 0; i < SPRITETEXT_MAXLENGTH; ++i) {
    VEC3 position = { offset.x, offset.y };
    ENTITY *ent = genericSprite_create(self->owner->space, &position, "_TEXT_CHAR", NULL);
    CDATA_SPRITE *sprData = (CDATA_SPRITE *)entity_getComponentData(ent, COMP_SPRITE);
    bool newline = false;
    char ch;
    sprData->manual.enabled = true;
    sprData->manual.textureName = data->font;
    sprData->manual.width = fontSize.x;
    sprData->manual.height = fontSize.y;
    vec4_copy(&sprData->color, &data->color);
    ch = data->text[i];
    if (data->text[i] == '\n') {
      newline = true;
      ch = ' ';
    }
    sprData->manual.u = (float)((ch % 16 * sprData->manual.width) + (sprData->manual.width / 2)) / (float)(16 * sprData->manual.width);
    sprData->manual.v = (float)((ch / 16 * sprData->manual.height) + (sprData->manual.height / 2)) / (float)(16 * sprData->manual.height);
    entity_attach(ent, self->owner);
    if (newline) {
      offset.x = (float)fontSize.x / 2.0f;
      offset.y -= (float)fontSize.y;
    }
    else
      offset.x += fontSize.x;
    list_insert_end(multi->entities, (void *)ent);
    printf("DOIN A THING: %s\n", sprData->manual.textureName);
  }
}

void comp_spriteText_setText(COMPONENT *self, char *text) {
  CDATA_SPRITETEXT *data = (CDATA_SPRITETEXT *)self->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  CDATA_MULTISPRITE *multi = (CDATA_MULTISPRITE *)entity_getComponentData(self->owner, COMP_MULTISPRITE);


}

void comp_spriteText(COMPONENT *self) {
  CDATA_SPRITETEXT data = { 0 };
  data.color.r = 1;
  data.color.g = 1;
  data.color.b = 1;
  data.color.a = 1;
  COMPONENT_INIT(self, COMP_SPRITETEXT, data);
  //self->events.initialize = comp_spriteText_initialize;
  component_depend(self, COMP_MULTISPRITE);
}
