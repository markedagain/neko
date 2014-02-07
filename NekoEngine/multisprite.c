/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "multisprite.h"

void comp_multiSprite_destroy(COMPONENT *self, void *event) {
  CDATA_MULTISPRITE *data = (CDATA_MULTISPRITE *)self->data;
  LIST_NODE *node = data->entities->first;
  while (node != NULL) {
    entity_destroy((ENTITY *)node->data);
    node = node->next;
  }
}

void comp_multiSprite(COMPONENT *self) {
  CDATA_MULTISPRITE data = { 0 };
  data.entities = list_create();
  COMPONENT_INIT(self, COMP_MULTISPRITE, data);
  self->events.destroy = comp_multiSprite_destroy;
  component_depend(self, COMP_TRANSFORM);
}