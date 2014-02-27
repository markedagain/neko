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
#include <stdlib.h>
#include "playerlogic.h"
#include "roomlogic.h"
#include "UI_build.h"
#include "UI_button.h"
#include "schoollogic.h"
#include "managescreen.h"


void comp_managementUpdate(COMPONENT *self, void *event) {
  CDATA_MANAGEMENT *data = (CDATA_MANAGEMENT *)self->data;
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  SPACE *fgSpace = game_getSpace(self->owner->space->game, "fg");
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

  if (mbox->left.pressed && data->gpa == NULL && !data->triggered) {
    char titleBuffer[40];
    VEC3 position = { 0, 0, 0 };
    VEC4 color = { 0, 0, 1, 1 };

    data->triggered = true;
    sprintf(data->tuitionBuffer, "Tuition: $%i", comData->tuition);
    strncpy(titleBuffer, "MANAGEMENT SCREEN 4 UR BUM", _countof(titleBuffer));
    vec3_set(&position, 0, 0, 0);    
    data->manageWindow = space_addEntityAtPosition(uiSpace, arch_manageScreen, "manage_screen", &position);
    data->gpa = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", data->gpaBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
    vec3_set(&position, 0, -10, 0);
    data->tuition = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", data->tuitionBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
    vec3_set(&position, 0, 100, 0);
    data->titleText = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/20", titleBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
    vec3_set(&position, 0, -20, 0);
    data->currCosts = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", data->costsBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
    vec3_set(&position, 0, -30, 0);
    data->studentPop = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", data->studentPopBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
    vec3_set(&position, 0, -40, 0);
    data->studentInc = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", data->studentIncBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
    //vec3_set(&position, -50, 70, 0);
    //data->leftGPA = genericSprite_create(uiSpace, &position, NULL, "cursor/manage_button_left");
    //vec3_set(&position, -50, 70, 0);
    //data->rightGPA = genericSprite_create(uiSpace, &position, NULL, "cursor/manage_button_right");
    //UI_button_createRoomButton(self, BUTTON_GPA_INCREMENT, &position, &color, "Increment GPA");
  }
  else if (mbox->left.pressed && data->gpa && !data->triggered) {
    data->triggered = true;
    entity_destroy(data->gpa);
    data->gpa = NULL;
    entity_destroy(data->tuition);
    data->tuition = NULL;
    entity_destroy(data->manageWindow);
    data->manageWindow = NULL;
    entity_destroy(data->titleText);
    data->titleText = NULL;
    entity_destroy(data->currCosts);
    data->currCosts = NULL;
    entity_destroy(data->studentPop);
    data->studentPop = NULL;
    entity_destroy(data->studentInc);
    data->studentInc = NULL;
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