/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "spritetext.h"
#include "entity.h"
#include "transform.h"
#include "vectormath.h"
#include "dictionary.h"
#include <stdio.h>
#include <string.h>

void comp_spriteText_initialize(COMPONENT *self, void *event) {
  CDATA_SPRITETEXT *data = (CDATA_SPRITETEXT *)self->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  CDATA_MULTISPRITE *multi = (CDATA_MULTISPRITE *)entity_getComponentData(self->owner, COMP_MULTISPRITE);
}

void comp_spriteText_setText(COMPONENT *self, char *text) {
  CDATA_SPRITETEXT *data = (CDATA_SPRITETEXT *)self->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  CDATA_MULTISPRITE *multiData = (CDATA_MULTISPRITE *)entity_getComponentData(self->owner, COMP_MULTISPRITE);
  COMPONENT *multi = entity_getComponent(self->owner, COMP_MULTISPRITE);
  TEXTURE *texture = (TEXTURE *)dict_get(&self->owner->space->game->data.textures, data->font);
  POINT fontSize = { texture->width / 16, texture->height / 16 };
  VEC2 offset = { (float)fontSize.x / 2.0f, -(float)fontSize.y / 2.0f };
  unsigned int i = 0;
  int j = 0;
  LIST_NODE *node;
  char textCopy[SPRITETEXT_MAXLENGTH];
  size_t textLength = strlen(text);
  size_t listLength = multiData->entities->count;

  for (i = 0; i < SPRITETEXT_MAXLENGTH; ++i) {
    textCopy[i] = 0;
  }

  for (i = 0; i < SPRITETEXT_MAXLENGTH; ++i) {
    data->text[i] = 0;
  }
  strcpy(data->text, text);

  for (i = 0; i < textLength; ++i) {
    if (text[i] != '\n')
      textCopy[j++] = text[i];
  }
  textLength = strlen(textCopy); // now we have the length of the string, minus newlines

  if (textLength > listLength) {
    for (i = 0; i < textLength - listLength; ++i) {
      VEC3 position = { 0, 0, 0 };
      multiSprite_addSprite(multi, genericSprite_create(self->owner->space, &position, "_TEXT_CHAR", NULL));
    }
  }
  if (textLength < listLength) {
    // TODO: Handle
  }

  if (multiData->entities->count == 0)
    return;

  node = multiData->entities->first;
  i = 0;
  while (node != NULL) {
    VEC3 position = { offset.x, offset.y };
    ENTITY *ent = (ENTITY *)node->data;
    CDATA_SPRITE *sprData = (CDATA_SPRITE *)entity_getComponentData(ent, COMP_SPRITE);
    CDATA_TRANSFORM *sprTrans = (CDATA_TRANSFORM *)entity_getComponentData(ent, COMP_TRANSFORM);
    bool newline = false;
    char ch;
    sprTrans->translation.x = position.x;
    sprTrans->translation.y = position.y;
    sprData->manual.enabled = true;
    sprData->manual.textureName = data->font;
    sprData->manual.width = fontSize.x;
    sprData->manual.height = fontSize.y;
    comp_sprite_clearMesh(entity_getComponent(ent, COMP_SPRITE));
    vec4_copy(&sprData->color, &data->color);
    ch = text[i];
    if (text[i] == '\n') {
      newline = true;
      ch = ' ';
    }
    sprData->manual.u = (float)((ch % 16 * sprData->manual.width) + (sprData->manual.width / 2)) / (float)(16 * sprData->manual.width);
    sprData->manual.v = (float)((ch / 16 * sprData->manual.height) + (sprData->manual.height / 2)) / (float)(16 * sprData->manual.height);
    if (newline) {
      offset.x = (float)fontSize.x / 2.0f;
      offset.y -= (float)fontSize.y;
    }
    else
      offset.x += fontSize.x;
    node = node->next;
    ++i;
  }
}

void comp_spriteText(COMPONENT *self) {
  CDATA_SPRITETEXT data = { 0 };
  data.color.r = 1;
  data.color.g = 1;
  data.color.b = 1;
  data.color.a = 1;
  COMPONENT_INIT(self, COMP_SPRITETEXT, data);
  self->events.initialize = comp_spriteText_initialize;
  component_depend(self, COMP_MULTISPRITE);
}
