/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdlib.h>
#include <string.h>
#include "component.h"

void component_initialize(COMPONENT *component, unsigned int id, void *data, size_t dataSize) {
  int i;
  for (i = 0; i < MAX_DEPENDS; ++i)
    component->depends[i] = 0;
  component->id = id;
  component->data = malloc(dataSize);
  memcpy(component->data, data, dataSize);
}

void component_depend(COMPONENT *component, unsigned int dependId) {
  int i;
  for (i = 0; i < MAX_DEPENDS; ++i) {
    if (component->depends[i] == 0) {
      component->depends[i] = dependId;
      return;
    }
  }
  /* THROW ERROR */
}
