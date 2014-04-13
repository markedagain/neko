/******************************************************************************
Filename: management.c

Project Name: Game School Simulator 2015

Author: Samuel Valdez

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "management.h"
#include "mousebox.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/generictext.h"
#include "../Nekoengine/spritetext.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/entity.h"
#include "../NekoEngine/sprite.h"
#include "playerlogic.h"
#include "roomlogic.h"
#include "UI_build.h"
#include "UI_button.h"
#include "schoollogic.h"
#include "managescreen.h"
#include "buttonfunctions.h"
#include "custombutton.h"
#include "colors.h"
#include "tutorial.h"

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
  CDATA_MANAGEMENT *managementData = (CDATA_MANAGEMENT *)entity_getComponentData(self->owner, COMP_MANAGEMENT);


  if (mbox->entered) {
    if (!managementData->hoverText) {
      VEC3 position;
      vec3_set(&position, -242, 151, 0);
      managementData->hoverText = genericText_create(uiSpace, &position, NULL, "fonts/gothic/12", "Management!", &colors[C_NAVY_DARK], TEXTALIGN_CENTER, TEXTALIGN_TOP);
    } 
    sound_playSound(&self->owner->space->game->systems.sound, "hover");
    sprite->color.a = 0.8f;
  }

  if (mbox->exited) {
    if (managementData->hoverText) {
      entity_destroy(managementData->hoverText);
      managementData->hoverText = NULL;
    }
    sprite->color.a = 1.0f;

  }

  if (mbox->left.pressed && data->gpa == NULL && !data->triggered) {
    comp_managementDisplay(self);

    if (self->owner->space->game->config.tutorial) {
      if (!data->alreadyActivated) {
        createFifthTutorial(uiSpace);
        data->alreadyActivated = true;
      }
    }
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
  VEC3 position = { 0, 0, 0 };  
  VEC4 color = colors[C_WHITE_LIGHT];
  ENTITY *newsFeed = space_getEntity(uiSpace, "newsFeed");
  CDATA_MOUSEBOX *newsFeedBox = (CDATA_MOUSEBOX *)entity_getComponentData(newsFeed, COMP_MOUSEBOX);
   
  newsFeedBox->active = false;

  data->triggered = true;
  
  vec3_set(&position, 0, 0, 0);

  data->manageWindow = space_addEntityAtPosition(uiSpace, arch_manageScreen, "manage_screen", &position);

  // GPA
  vec3_set(&position, 10, 30, 0); 
  data->gpa = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/16", data->gpaBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
  
  // Tuition
  vec3_set(&position, 10, 10, 0); 
  data->tuition = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/16", data->tuitionBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
  
  // Costs/Upkeep
  vec3_set(&position, 100, -65, 0);
  data->currCosts = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/20bold", data->costsBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
  
  // Student Population
  vec3_set(&position, -70, -31, 0);
  data->studentPop = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", data->studentPopBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
  
  // Incoming Students
  vec3_set(&position, -70, -43, 0);
  data->studentInc = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", data->studentIncBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
  
  // Reputation
  vec3_set(&position, 100, 20, 0);
  data->rep = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/20bold", data->reputationBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);

  // Expected Income
  vec3_set(&position, 100, -40, 0);
  data->income = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/20bold", data->incomeBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
  
  // Graduates
  vec3_set(&position, -70, -59, 0);
  data->grads = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", data->graduateBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);

  // Dropouts
  vec3_set(&position, -70, -71, 0);
  data->dropoutsText = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", data->dropoutBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);

  // Increase GPA button
  vec4_set(&color, 0.75f, 0.75f, 0.75f, 1.0f);
  vec3_set(&position, 45, 30, 0);
  createCustomButton(increaseGPA_onEntered, NULL, increaseGPA_onPressed, increaseGPA_onExit, NULL,
                         self->owner->space, &position, "managementButton",
                         1.0f, 1.0f,
                         true, "ui/button_plus", NULL, &color,
                         false, "+GPA", "fonts/gothic/12", 
                         NULL, TEXTALIGN_CENTER, TEXTALIGN_CENTER);
  
  // Decrease GPA button
  vec3_set(&position, -25, 30, 0);
  createCustomButton(decreaseGPA_onEntered, NULL, decreaseGPA_onPressed, decreaseGPA_onExit, NULL,
                         self->owner->space, &position, "managementButton",
                         1.0f, 1.0f,
                         true, "ui/button_minus", NULL, &color,
                         false, "-GPA", "fonts/gothic/12", 
                         NULL, TEXTALIGN_CENTER, TEXTALIGN_CENTER);
  
  // Increase tuition button
  vec3_set(&position, 45, 10, 0);
  createCustomButton(increaseTuition_onEntered, NULL, increaseTuition_onPressed, increaseTuition_onExit, NULL,
                         self->owner->space, &position, "managementButton",
                         1.0f, 1.0f,
                         true, "ui/button_plus", NULL, &color,
                         false, "+Tuition", "fonts/gothic/12", 
                         NULL, TEXTALIGN_CENTER, TEXTALIGN_CENTER);    
  
  // Decrease tuition button
  vec3_set(&position, -25, 10, 0);   
  createCustomButton(decreaseTuition_onEntered, NULL, decreaseTuition_onPressed, decreaseTuition_onExit, NULL,
                         self->owner->space, &position, "managementButton",
                         1.0f, 1.0f,
                         true, "ui/button_minus", NULL, &color,
                         false, "-Tuition", "fonts/gothic/12", 
                         NULL, TEXTALIGN_CENTER, TEXTALIGN_CENTER);
}

void comp_managementRemove(COMPONENT *self) {
  SPACE *simSpace = game_getSpace(self->owner->space->game, "sim");
  SPACE *uiSpace = game_getSpace(self->owner->space->game, "ui");
  CDATA_MANAGEMENT *data = (CDATA_MANAGEMENT *)entity_getComponentData(space_getEntity(uiSpace, "manage_button"), COMP_MANAGEMENT);
  ENTITY *schoolData = space_getEntity(simSpace, "gameManager");
  CDATA_SCHOOLLOGIC *comData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(schoolData, COMP_SCHOOLLOGIC);
  LIST_NODE *node;
  LIST *buttons = list_create(); 
  ENTITY *newsFeed = space_getEntity(uiSpace, "newsFeed");
  CDATA_MOUSEBOX *newsFeedBox = (CDATA_MOUSEBOX *)entity_getComponentData(newsFeed, COMP_MOUSEBOX);
   
  data->triggered = true;

  newsFeedBox->active = true;

  if(data->closed == 0)
    data->closed = 1;
    
  entity_destroy(data->gpa);
  data->gpa = NULL;
  entity_destroy(data->tuition);
  data->tuition = NULL;
  entity_destroy(data->manageWindow);
  data->manageWindow = NULL;
  entity_destroy(data->currCosts);
  data->currCosts = NULL;
  entity_destroy(data->studentPop);
  data->studentPop = NULL;
  entity_destroy(data->studentInc);
  data->studentInc = NULL;
  entity_destroy(data->rep);
  data->rep = NULL;
  entity_destroy(data->income);
  data->income = NULL;
  entity_destroy(data->grads);
  data->grads = NULL;
  entity_destroy(data->dropoutsText);
  data->dropoutsText = NULL;
  space_getAllEntities(uiSpace, "managementButton", buttons);
  
  node = buttons->first;
  while (node) {
    entity_destroy((ENTITY *)node->data);
    node = node->next;
  }
  list_destroy(buttons);
}

void comp_management(COMPONENT *self) {
  CDATA_MANAGEMENT data = { 0 };
  strcpy(data.studentPopBuffer, "0");
  strcpy(data.reputationBuffer, "0");
  strcpy(data.graduateBuffer, "0");
  strcpy(data.dropoutBuffer, "0");
  strcpy(data.costsBuffer, "$0");
  strcpy(data.incomeBuffer, "$0");
  strcpy(data.studentIncBuffer, "0");
  data.triggered = false;
  COMPONENT_INIT(self, COMP_MANAGEMENT, data);
  component_depend(self, COMP_MOUSEBOX);
  self->events.logicUpdate = comp_managementUpdate;
}