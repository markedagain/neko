/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "buttonfunctions.h"
#include "namescreen.h"

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
  sound_playSound(&self->owner->space->game->systems.sound, "hover");

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
  sound_playSound(&self->owner->space->game->systems.sound, "hover");

}

/********** Exit **********/
void exit_onEntered(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  sprite->color.a = 0.8f;
  sound_playSound(&self->owner->space->game->systems.sound, "hover");
}

void exit_onPressed(COMPONENT *self) {
  SPACE *menu = game_getSpace(self->owner->space->game, "menu");
  VEC3 position = { 0 };
  space_addEntityAtPosition(menu, arch_nameScreen, "nameScreen", &position);
}

void exit_onExit(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  sprite->color.a = 1.0f;
  sound_playSound(&self->owner->space->game->systems.sound, "hover");

}