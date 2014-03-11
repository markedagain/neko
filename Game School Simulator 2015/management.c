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
#include "buttonfunctions.h"
#include "custombutton.h"


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
    comp_managementDisplay(self);
  }

  else if (mbox->left.pressed && data->gpa && !data->triggered) {
    comp_managementRemove(self);
  }
  else if (!mbox->left.pressed)
    data->triggered = false;
  }

void comp_managementDisplay(COMPONENT *self) {
  CDATA_MANAGEMENT *data = (CDATA_MANAGEMENT *)self->data;
  SPACE *simSpace = game_getSpace(self->owner->space->game, "sim");
  SPACE *uiSpace = game_getSpace(self->owner->space->game, "ui");
  ENTITY *schoolData = space_getEntity(simSpace, "gameManager");
  CDATA_SCHOOLLOGIC *comData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(schoolData, COMP_SCHOOLLOGIC);
  char titleBuffer[40];  
  VEC3 position = { 0, 0, 0 };  
  VEC4 color = { 0.7f, 0.5f, 0.5f, 1 }; 
  VEC4 textColor = { 0, 0, 0, 1.0f };
   
  data->triggered = true;
  
  vec3_set(&position, 0, 0, 0);    

  data->manageWindow = space_addEntityAtPosition(uiSpace, arch_manageScreen, "manage_screen", &position);

  // TITLE TITLE
  strncpy(titleBuffer, "MANAGEMENT", _countof(titleBuffer));
  vec3_set(&position, 0, 100, 0);
  data->titleText = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/28", titleBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
  
  // GPA
  vec3_set(&position, -100, 70, 0);    
  data->gpaTitle = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/28", "Minimum GPA", &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
  vec3_set(&position, -100, 30, 0); 
  data->gpa = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/20", data->gpaBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
  
  // Tuition
  vec3_set(&position, -100, -10, 0);
  data->tuitionTitle = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/28", "Tuition", &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
  vec3_set(&position, -100, -50, 0); 
  data->tuition = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/20", data->tuitionBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
  
  // Costs/Upkeep
  vec3_set(&position, 100, -80, 0);
  data->currCosts = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/20", data->costsBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
  
  // Student Population
  vec3_set(&position, 100, 70, 0);
  data->studentPopTitle = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/20", "Student Population", &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
  vec3_set(&position, 100, 50, 0);
  data->studentPop = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", data->studentPopBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
  
  // Incoming Students
  vec3_set(&position, 100, 30, 0);
  data->studentIncTitle = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/20", "Incoming Students", &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
  vec3_set(&position, 100, 10, 0);
  data->studentInc = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", data->studentIncBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
  
  // Reputation
  vec3_set(&position, 100, -10, 0);
  data->rep = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/20", data->reputationBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);

  // Expected Income
  vec3_set(&position, 100, -40, 0);
  data->incomeTitle = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/20", "Expected Income:", &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
  vec3_set(&position, 100, -60, 0);
  data->income = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/20", data->incomeBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
  
  // Increase GPA button
  vec3_set(&position, -40, 30, 0);
  createCustomButton(increaseGPA_onEntered, NULL, increaseGPA_onPressed, increaseGPA_onExit, NULL,
                         self->owner->space, &position, "managementButton",
                         1.0f, 1.0f,
                         true, "backgrounds/white_box", NULL, &color,
                         true, "+GPA", "fonts/gothic/12", 
                         &textColor, TEXTALIGN_CENTER, TEXTALIGN_CENTER);
  
  // Decrease GPA button
  vec3_set(&position, -160, 30, 0);
  createCustomButton(decreaseGPA_onEntered, NULL, decreaseGPA_onPressed, decreaseGPA_onExit, NULL,
                         self->owner->space, &position, "managementButton",
                         1.0f, 1.0f,
                         true, "backgrounds/white_box", NULL, &color,
                         true, "-GPA", "fonts/gothic/12", 
                         &textColor, TEXTALIGN_CENTER, TEXTALIGN_CENTER);
  
  // Increase tuition button
  vec3_set(&position, -40, -50, 0);
  createCustomButton(increaseTuition_onEntered, NULL, increaseTuition_onPressed, increaseTuition_onExit, NULL,
                         self->owner->space, &position, "managementButton",
                         1.0f, 1.0f,
                         true, "backgrounds/white_box", NULL, &color,
                         true, "+Tuition", "fonts/gothic/12", 
                         &textColor, TEXTALIGN_CENTER, TEXTALIGN_CENTER);    
  
  // Decrease tuition button
  vec3_set(&position, -160, -50, 0);   
  createCustomButton(decreaseTuition_onEntered, NULL, decreaseTuition_onPressed, decreaseTuition_onExit, NULL,
                         self->owner->space, &position, "managementButton",
                         1.0f, 1.0f,
                         true, "backgrounds/white_box", NULL, &color,
                         true, "-Tuition", "fonts/gothic/12", 
                         &textColor, TEXTALIGN_CENTER, TEXTALIGN_CENTER);
}

void comp_managementRemove(COMPONENT *self) {
  CDATA_MANAGEMENT *data = (CDATA_MANAGEMENT *)self->data;
  SPACE *simSpace = game_getSpace(self->owner->space->game, "sim");
  SPACE *uiSpace = game_getSpace(self->owner->space->game, "ui");
  ENTITY *schoolData = space_getEntity(simSpace, "gameManager");
  CDATA_SCHOOLLOGIC *comData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(schoolData, COMP_SCHOOLLOGIC);
  LIST_NODE *node;
  LIST *buttons = list_create(); 
  data->triggered = true;

  entity_destroy(data->gpaTitle);
  data->gpaTitle = NULL;
  entity_destroy(data->tuitionTitle);
  data->tuitionTitle = NULL;
  entity_destroy(data->studentPopTitle);
  data->studentPopTitle = NULL;
  entity_destroy(data->studentIncTitle);
  data->studentIncTitle = NULL;    
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
  entity_destroy(data->rep);
  data->rep = NULL;
  entity_destroy(data->incomeTitle);
  data->incomeTitle = NULL;
  entity_destroy(data->income);
  data->income = NULL;
  space_getAllEntities(self->owner->space, "managementButton", buttons);
  node = buttons->first;
  while (node) {
    entity_destroy((ENTITY *)node->data);
    node = node->next;
  }
  list_destroy(buttons);
}

void comp_management(COMPONENT *self) {
  CDATA_MANAGEMENT data = { 0 };
  data.triggered = false;
  COMPONENT_INIT(self, COMP_MANAGEMENT, data);
  component_depend(self, COMP_MOUSEBOX);
  self->events.logicUpdate = comp_managementUpdate;
}