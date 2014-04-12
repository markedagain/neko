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
  LIST_NODE *node = multi->entities->first;
  comp_transform_frameUpdate(entity_getComponent(self->owner, COMP_TRANSFORM), NULL);
  while (node) {
    comp_transform_frameUpdate(entity_getComponent((ENTITY *)node->data, COMP_TRANSFORM), NULL);
    node = node->next;
  }
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
  size_t lineLengths[SPRITETEXT_MAXLENGTH] = { 0 };
  size_t curLine = 0;
  size_t lines = 0;
  size_t textLength = strlen(text);
  size_t listLength = multiData->entities->count;

  if (!text)
    return;

  if (strcmp(data->text, text) == 0)
    return;

  for (i = 0; i < SPRITETEXT_MAXLENGTH; ++i) {
    textCopy[i] = 0;
  }

  for (i = 0; i < SPRITETEXT_MAXLENGTH; ++i) {
    data->text[i] = 0;
  }
  strcpy(data->text, text);

  for (i = 0; i < textLength; ++i) {
    if (text[i] != '\n') {
      textCopy[j++] = text[i];
      lineLengths[curLine]++;
    }
    else
      curLine++;
  }
  textLength = strlen(textCopy); // now we have the length of the string, minus newlines

  if (textLength > listLength) {
    for (i = 0; i < textLength - listLength; ++i) {
      VEC3 position = { 0, 0, 0 };
      multiSprite_addSprite(multi, genericSprite_create(self->owner->space, &position, "_TEXT_CHAR", NULL));
    }
  }
  if (textLength < listLength) {
   size_t lastIndex = textLength;
   LIST_NODE *nextNode;
   i = 0;
   node = multiData->entities->first;
   while (i < lastIndex) {
     node = node->next;
     ++i;
   }
   while (node != NULL) {
     ENTITY *ent;
     nextNode = node->next;
     ent = (ENTITY *)list_remove(multiData->entities, node);
     entity_destroy(ent);
     node = nextNode;
   }
  }

  if (multiData->entities->count == 0)
    return;

  node = multiData->entities->first;
  i = 0;
  lines = curLine + 1;
  curLine = 0;

  if (data->alignment.x == TEXTALIGN_LEFT)
    offset.x = (float)fontSize.x / 2.0f;
  if (data->alignment.x == TEXTALIGN_CENTER)
    offset.x = -(float)fontSize.x * ((float)lineLengths[curLine] - 1.0f) / 2.0f;
  if (data->alignment.x == TEXTALIGN_RIGHT)
    offset.x = -(float)fontSize.x * ((float)lineLengths[curLine] + 0.5f);
  if (data->alignment.y == TEXTALIGN_TOP)
    offset.y = -(float)fontSize.y / 2.0f;
  if (data->alignment.y == TEXTALIGN_MIDDLE)
    offset.y = (((float)lines - 1.0f) / 2.0f) * (float)fontSize.y;
  if (data->alignment.y == TEXTALIGN_BOTTOM)
    offset.y = ((float)lines - 0.5f) * (float)fontSize.y;

  while (node != NULL) {
    ENTITY *ent = (ENTITY *)node->data;
    CDATA_SPRITE *sprData = (CDATA_SPRITE *)entity_getComponentData(ent, COMP_SPRITE);
    CDATA_TRANSFORM *sprTrans = (CDATA_TRANSFORM *)entity_getComponentData(ent, COMP_TRANSFORM);
    char ch;
    sprData->manual.enabled = true;
    sprData->manual.textureName = data->font;
    sprData->manual.width = fontSize.x;
    sprData->manual.height = fontSize.y;
    comp_sprite_clearMesh(entity_getComponent(ent, COMP_SPRITE));
    vec4_copy(&sprData->color, &data->color);
    while (text[i] == '\n') {
      ++i;
      curLine++;
      if (data->alignment.x == TEXTALIGN_LEFT)
        offset.x = (float)fontSize.x / 2.0f;
      if (data->alignment.x == TEXTALIGN_CENTER)
        offset.x = -(float)fontSize.x * ((float)lineLengths[curLine] - 1.0f) / 2.0f;
      if (data->alignment.x == TEXTALIGN_RIGHT)
        offset.x = -(float)fontSize.x * ((float)lineLengths[curLine] + 0.5f);
      //if (data->alignment.y == TEXTALIGN_TOP)
        offset.y -= (float)fontSize.y;
    }
    sprTrans->translation.x = offset.x;
    sprTrans->translation.y = offset.y;
    ch = text[i];
    sprData->manual.u = (float)((ch % 16 * sprData->manual.width) + (sprData->manual.width / 2)) / (float)(16 * sprData->manual.width);
    sprData->manual.v = (float)((ch / 16 * sprData->manual.height) + (sprData->manual.height / 2)) / (float)(16 * sprData->manual.height);
    offset.x += fontSize.x;
    node = node->next;
    ++i;
  }
}

void comp_spriteText(COMPONENT *self) {
  int i = 0;
  CDATA_SPRITETEXT data = { 0 };
  data.color.r = 1;
  data.color.g = 1;
  data.color.b = 1;
  data.color.a = 1;
  data.alignment.x = TEXTALIGN_LEFT;
  data.alignment.y = TEXTALIGN_TOP;
  for (i = 0; i < SPRITETEXT_MAXLENGTH; ++i)
    data.text[i] = 0;
  COMPONENT_INIT(self, COMP_SPRITETEXT, data);
  self->events.initialize = comp_spriteText_initialize;
  component_depend(self, COMP_MULTISPRITE);
}

void spriteText_outline(ENTITY *entity, bool enabled, VEC4 *color) {
  CDATA_MULTISPRITE *multi = (CDATA_MULTISPRITE *)entity_getComponentData(entity, COMP_MULTISPRITE);
  LIST_NODE *node = multi->entities->first;
  while (node) {
    CDATA_SPRITE *comData = (CDATA_SPRITE *)entity_getComponentData((ENTITY *)node->data, COMP_SPRITE);
    comData->outline.enabled = enabled;
    comData->outline.color.r = color->r;
    comData->outline.color.g = color->g;
    comData->outline.color.b = color->b;
    comData->outline.color.a = color->a;
    node = node->next;
  }
}