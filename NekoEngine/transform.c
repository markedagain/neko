/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "transform.h"
#include "component.h"
#include "entity.h"
#include "event.h"
#include "util.h"

void comp_transform_frameUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_TRANSFORM *comData = (CDATA_TRANSFORM *)self->data;
  CDATA_TRANSFORM *parentTransform = NULL;
  MATRIX3 parentMatrix = { 0 };
  VEC3 childTranslation = { 0 };
  VEC3 scale = { 0 };
  comData->rotation = (float)fmod(comData->rotation, 2.0f * (float)M_PI);
  if (comData->rotation < 0)
    comData->rotation += 2.0f * (float)M_PI;
  if (self->owner->parent == NULL) {
    vec3_copy(&comData->world.translation, &comData->translation);
    vec3_copy(&comData->world.scale, &comData->scale);
    comData->world.rotation = comData->rotation;
  }
  else {
    parentTransform = (CDATA_TRANSFORM *)entity_getComponentData(self->owner->parent, COMP_TRANSFORM);
    comData->world.scale.x = parentTransform->world.scale.x * comData->scale.x;
    comData->world.scale.y = parentTransform->world.scale.y * comData->scale.y;
    comData->world.scale.z = parentTransform->world.scale.z * comData->scale.z;
    comData->world.rotation = angle_normalize(parentTransform->world.rotation + comData->rotation);
    // TODO: Use 2x2 matrix math to transform the translation based on parent's rotation and scale
    // currently does not work with un-uniform scaling
    childTranslation = comData->translation;
    matrix3_identity(&parentMatrix);
    scale.x = parentTransform->world.scale.x;
    scale.y = parentTransform->world.scale.y;
    matrix3_scale(&parentMatrix, &scale);
    matrix3_rotate(&parentMatrix, parentTransform->world.rotation);
    matrix3_apply_to_vector(&childTranslation, &parentMatrix);

    //all my scaling stuff
    vec3_add(&comData->world.translation, &parentTransform->world.translation, &childTranslation);
  }
}

void comp_transform_destroy(COMPONENT *self, void *event) {
}

void comp_transform(COMPONENT *self) {
  CDATA_TRANSFORM initData = { { 0, 0, 0 }, { 1, 1, 1 }, 0, { { 0, 0, 0 }, { 1, 1, 1 }, 0 } };
  COMPONENT_INIT(self, COMP_TRANSFORM, initData);
  self->events.frameUpdate = comp_transform_frameUpdate;
}
