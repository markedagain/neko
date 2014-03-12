/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "buttonfunctions.h"
#include "namescreen.h"
#include "schoollogic.h"

/********** New Game **********/
void newGame_onEntered(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  sprite->color.a = 0.8f;
  sound_playSound(&self->owner->space->game->systems.sound, "hover");

}

void newGame_onPressed(COMPONENT *self) {
  SPACE *menu = game_getSpace(self->owner->space->game, "menu");
  VEC3 position = { 0 };
  space_addEntityAtPosition(menu, arch_nameScreen, "nameScreen", &position);
}

void newGame_onExit(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  sprite->color.a = 1.0f;

}

/********** Options **********/
void options_onEntered(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  sprite->color.a = 0.8f;
  sound_playSound(&self->owner->space->game->systems.sound, "hover");

}

void options_onPressed(COMPONENT *self) {
  self->owner->space->game->destroying = true;
}

void options_onExit(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  sprite->color.a = 1.0f;

}

/********** Exit **********/
void exit_onEntered(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  sprite->color.a = 0.8f;
  sound_playSound(&self->owner->space->game->systems.sound, "hover");
}

void exit_onPressed(COMPONENT *self) {
  self->owner->space->game->destroying = true;
}

void exit_onExit(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  sprite->color.a = 1.0f;

}

/******* Increase GPA *******/
void increaseGPA_onEntered(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  sprite->color.a = 0.8f;
  sound_playSound(&self->owner->space->game->systems.sound, "hover");
}

void increaseGPA_onPressed(COMPONENT *self) {
  SPACE *simSpace = game_getSpace(self->owner->space->game, "sim");
  ENTITY *gameManager = space_getEntity(simSpace, "gameManager");
  CDATA_SCHOOLLOGIC *managementData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(gameManager, COMP_SCHOOLLOGIC);

  if (managementData->minGpa >= (float)4.0)
    managementData->minGpa = (float)4.0;
  else
    managementData->minGpa += (float)0.2;
}

void increaseGPA_onExit(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  sprite->color.a = 1.0f;

}

/******* Decrease GPA *******/
void decreaseGPA_onEntered(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  sprite->color.a = 0.8f;
  sound_playSound(&self->owner->space->game->systems.sound, "hover");
}

void decreaseGPA_onPressed(COMPONENT *self) {
  SPACE *simSpace = game_getSpace(self->owner->space->game, "sim");
  ENTITY *gameManager = space_getEntity(simSpace, "gameManager");
  CDATA_SCHOOLLOGIC *managementData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(gameManager, COMP_SCHOOLLOGIC);

  if (managementData->minGpa <= (float)0.2)
    managementData->minGpa = (float)0.2;
  else
    managementData->minGpa -= (float)0.2;
}

void decreaseGPA_onExit(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  sprite->color.a = 1.0f;

}

/******* Increase Tuition *******/
void increaseTuition_onEntered(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  sprite->color.a = 0.8f;
  sound_playSound(&self->owner->space->game->systems.sound, "hover");
}

void increaseTuition_onPressed(COMPONENT *self) {
  SPACE *simSpace = game_getSpace(self->owner->space->game, "sim");
  ENTITY *gameManager = space_getEntity(simSpace, "gameManager");
  CDATA_SCHOOLLOGIC *managementData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(gameManager, COMP_SCHOOLLOGIC);

  managementData->tuition += 500;
}

void increaseTuition_onExit(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  sprite->color.a = 1.0f;
}

/******* Decrease Tuition *******/
void decreaseTuition_onEntered(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  sprite->color.a = 0.8f;
  sound_playSound(&self->owner->space->game->systems.sound, "hover");
}

void decreaseTuition_onPressed(COMPONENT *self) {
  SPACE *simSpace = game_getSpace(self->owner->space->game, "sim");
  ENTITY *gameManager = space_getEntity(simSpace, "gameManager");
  CDATA_SCHOOLLOGIC *managementData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(gameManager, COMP_SCHOOLLOGIC);

  if (managementData->tuition <= 0)   
    managementData->tuition = 500;      
  else     
    managementData->tuition -= 500;
}

void decreaseTuition_onExit(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  sprite->color.a = 1.0f;
}
