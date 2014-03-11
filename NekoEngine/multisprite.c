/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "multisprite.h"

void comp_multiSprite_destroy(COMPONENT *self, void *event) {
  CDATA_MULTISPRITE *data = (CDATA_MULTISPRITE *)self->data;
  list_destroy(data->entities);
}

void comp_multiSprite(COMPONENT *self) {
  CDATA_MULTISPRITE data = { 0 };
  data.entities = list_create();
  COMPONENT_INIT(self, COMP_MULTISPRITE, data);
  self->events.destroy = comp_multiSprite_destroy;
  component_depend(self, COMP_TRANSFORM);
}

void multiSprite_addSprite(COMPONENT *self, ENTITY *sprite) {
  CDATA_MULTISPRITE *data = (CDATA_MULTISPRITE *)self->data;
  list_insert_end(data->entities, sprite);
  entity_attach(sprite, self->owner);
}
void multiSprite_removeSprite(COMPONENT *self, size_t index) {
  CDATA_MULTISPRITE *data = (CDATA_MULTISPRITE *)self->data;
  LIST_NODE *node = data->entities->first;
  ENTITY *found;
  size_t i = 0;

  if (index >= (unsigned int)data->entities->count) {
    printf("ERROR IN MULTISPRITE_DESTROY!!\n");
    return;
  }

  while (i < index)
    node = node->next;

  found = (ENTITY *)list_remove(data->entities, node);
  entity_destroy(found);
}

void multiSprite_setColor(COMPONENT *self, VEC4 *color) {
  CDATA_MULTISPRITE *data = (CDATA_MULTISPRITE *)self->data;
  LIST_NODE *node = data->entities->first;

  while (node) {
    vec4_copy(&((CDATA_SPRITE *)entity_getComponentData((ENTITY *)node->data, COMP_SPRITE))->color, color);
    node = node->next;
  }
}

void multiSprite_setAlpha(COMPONENT *self, float alpha) {
  CDATA_MULTISPRITE *data = (CDATA_MULTISPRITE *)self->data;
  LIST_NODE *node = data->entities->first;

  while (node) {
    ((CDATA_SPRITE *)entity_getComponentData((ENTITY *)node->data, COMP_SPRITE))->color.a = alpha;
    node = node->next;
  }
}

float multiSprite_getAlpha(COMPONENT *self) {
  CDATA_MULTISPRITE *data = (CDATA_MULTISPRITE *)self->data;
  LIST_NODE *node = data->entities->first;
  return (node ? ((CDATA_SPRITE *)entity_getComponentData((ENTITY *)node->data, COMP_SPRITE))->color.a : 0.0f);
}

void multiSprite_setVisible(COMPONENT *self, bool visible) {
  CDATA_MULTISPRITE *data = (CDATA_MULTISPRITE *)self->data;
  LIST_NODE *node = data->entities->first;

  while (node) {
    ((CDATA_SPRITE *)entity_getComponentData((ENTITY *)node->data, COMP_SPRITE))->visible = visible;
    node = node->next;
  }
}