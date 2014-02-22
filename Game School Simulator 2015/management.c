#include "management.h"
#include "mousebox.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/generictext.h"
#include "../Nekoengine/spritetext.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/entity.h"
#include "../NekoEngine/sprite.h"
#include <math.h>
#include <stdio.h>
#include "playerlogic.h"
#include "roomlogic.h"
#include "UI_build.h"
#include "schoollogic.h"
#include "managescreen.h"


void comp_managementUpdate(COMPONENT *self, void *event) {
  CDATA_MANAGEMENT *data = (CDATA_MANAGEMENT *)self->data;
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  SPACE *simSpace = game_getSpace(self->owner->space->game, "sim");
  SPACE *uiSpace = game_getSpace(self->owner->space->game, "ui");
  ENTITY *schoolData = space_getEntity(simSpace, "gameManager");
  CDATA_SCHOOLLOGIC *comData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(schoolData, COMP_SCHOOLLOGIC);

  if (mbox->over) {
    sprite->color.r = min(sprite->color.r + 0.05f, 1);
    sprite->color.b = max(sprite->color.b - 0.05f, 1);
    sprite->color.g = max(sprite->color.g - 0.05f, 0);
  }
  else {
    sprite->color.r = max(sprite->color.r - 0.05f, 0);
    sprite->color.b = min(sprite->color.b + 0.05f, 1);
    sprite->color.g = min(sprite->color.g + 0.05f, 1);
  }

  if (mbox->left.pressed && data->ent1 == NULL && !data->triggered) {
    char gpaBuffer[40];
    char tuitionBuffer[40];
    VEC3 position = { 0, 0, 0 };
    VEC4 color = { 0, 0, 1, 1 };

    data->triggered = true;
    printf("%f\n", comData->minGpa);
    sprintf(gpaBuffer, "Min GPA: %f", comData->minGpa);
    sprintf(tuitionBuffer, "Tuition: $%i", comData->tuition);
    data->ent1 = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", gpaBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
    vec3_set(&position, 0, -10, 0);
    data->ent2 = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", tuitionBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
    vec3_set(&position, 0, 0, 0);
    // data->ent3 = space_addEntityAtPosition(uiSpace, arch_managescreen, "manage_screen", &position);
  }
  else if (mbox->left.pressed && data->ent1 && !data->triggered) {
    data->triggered = true;
    entity_destroy(data->ent1);
    printf("%i\n", comData->tuition);
    data->ent1 = NULL;
    entity_destroy(data->ent2);
    data->ent2 = NULL;
    // entity_destroy(data->ent3);
    // data->ent3 = NULL;
  }
  else if (!mbox->left.pressed)
    data->triggered = false;
  }

void comp_management(COMPONENT *self) {
  CDATA_MANAGEMENT data = { 0 };
  data.triggered = false;
  COMPONENT_INIT(self, COMP_MANAGEMENT, data);
  component_depend(self, COMP_MOUSEBOX);
  self->events.logicUpdate = comp_managementUpdate;
}