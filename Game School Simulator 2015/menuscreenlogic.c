/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "menuscreenlogic.h"
#include "genericsprite.h"
#include "generictext.h"
#include "UI_button.h"
#include "UI_build.h"
#include "buttonfunctions.h"
#include "custombutton.h"

void comp_menuScreenLogic_logicUpdate(COMPONENT *self, void *event) {
}

void comp_menuScreenLogic(COMPONENT *self) {
  COMPONENT_INIT_NULL(self, COMP_MENUSCREENLOGIC);
  self->events.logicUpdate = comp_menuScreenLogic_logicUpdate;
  self->events.initialize = comp_menuScreenLogic_initialize;
}

void comp_menuScreenLogic_initialize(COMPONENT *self, void *event) {
  VEC3 position = { 0 };
  VEC4 color = { 1.0f, 1.0f, 1.0f, 1.0f, };

  ENTITY *created = genericSprite_create(self->owner->space, &position, "menubox", "blank");
  CDATA_SPRITE *spriteData = (CDATA_SPRITE *)entity_getComponentData(created, COMP_SPRITE);
  
  spriteData->size.x = 500.0f;
  spriteData->size.y = 500.0f;

  // create the new game button
  position.y = 80.0f;
  createCustomButton(newGame_onEntered, NULL, newGame_onPressed, newGame_onExit, NULL,
                           self->owner->space, &position, "newGameButton",
                           1.0f, 1.0f,
                           true, "newgame", NULL,
                           false, NULL, NULL, 
                           NULL, TEXTALIGN_CENTER, TEXTALIGN_CENTER);

  // create the options button
  position.y = -80.0f;
  position.x = -125.0f;
  createCustomButton(options_onEntered, NULL, options_onPressed, options_onExit, NULL,
                           self->owner->space, &position, "optionsButton",
                           1.0f, 1.0f,
                           true, "options", NULL,
                           false, NULL, NULL, 
                           NULL, TEXTALIGN_CENTER, TEXTALIGN_CENTER);

  // create the exit button
  position.x = 125.0f;
  createCustomButton(exit_onEntered, NULL, exit_onPressed, exit_onExit, NULL,
                           self->owner->space, &position, "exitButton",
                           1.0f, 1.0f,
                           true, "exit", NULL,
                           false, NULL, NULL, 
                           NULL, TEXTALIGN_CENTER, TEXTALIGN_CENTER);
}
