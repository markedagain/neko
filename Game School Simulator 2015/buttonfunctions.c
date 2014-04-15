/******************************************************************************
Filename: buttonfunctions.c

Project Name: Game School Simulator 2015

Author: Tai Der Hui

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "buttonfunctions.h"
#include "namescreen.h"
#include "schoollogic.h"
#include "colors.h"
#include "custombutton.h"
#include "genericsprite.h"
#include "custombuttonlogic.h"
#include "newsfeedlogic.h"
#include "UI_button.h"
#include "mousebox.h"
#include "pausescreenlogic.h"
#include "pausescreen.h"
#include "creditsscreenlogic.h"
#include "management.h"
#include "menuscreen.h"

/********** New Game **********/
void newGame_onEntered(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  // if options are open, don't do anything
  if (space_getEntity(self->owner->space, "options"))
    return;

  sprite->color.a = 0.8f;
  sound_playSound(&self->owner->space->game->systems.sound, "hover");

}

void newGame_onPressed(COMPONENT *self) {
  SPACE *menu = game_getSpace(self->owner->space->game, "menu");
  VEC3 position = { 0 };

  // if options are open, don't do anything
  if (space_getEntity(self->owner->space, "options"))
    return;

  space_addEntityAtPosition(menu, arch_nameScreen, "nameScreen", &position);
}

void newGame_onExit(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  // if options are open, don't do anything
  if (space_getEntity(self->owner->space, "options"))
    return;

  sprite->color.a = 1.0f;

}

/********** Options **********/
void options_onEntered(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  sprite->color.a = 0.8f;
  sound_playSound(&self->owner->space->game->systems.sound, "hover");

}

void options_onPressed(COMPONENT *self) {
  SPACE *menu = game_getSpace(self->owner->space->game, "menu");
  VEC2 dimensions = { 400.0f, 200.0f };
  VEC3 position = { 0 };
  
  if (space_getEntity(menu, "options")) {
    LIST *optionsList = list_create();
    LIST_NODE *node;
    space_getAllEntities(menu, "options", optionsList);
    node = optionsList->first;
    while (node) {
      entity_destroy((ENTITY *)node->data);
      node = node->next;
    }
    list_destroy(optionsList);
    entity_destroy(space_getEntity(menu, "pauseScreen"));
  }
  else {
    space_addEntity(self->owner->space, arch_pauseScreen, "pauseScreen");
  }
}

void options_onExit(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  sprite->color.a = 1.0f;

}


/********* CREDITS ***********/

void credits_onEntered(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  // if options are open, don't do anything
  if (space_getEntity(self->owner->space, "options"))
    return;

  sprite->color.a = 0.8f;
  sound_playSound(&self->owner->space->game->systems.sound, "hover");

}

static void fadeIn_update(ACTION *action, double dt) {
  ENTITY *self = (ENTITY *)action->data;
  SPACE *menu = game_getSpace(self->space->game, "menu");
  ENTITY *credits = space_getEntity(menu, "credits");
  if (credits) {
    CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(credits, COMP_SPRITE);
    sprite->color.a = action_getEase(action, EASING_QUAD_OUT);
  }
}

static void fadeIn_onEnd(ACTION *action) {
  ENTITY *credits = space_getEntity(((ENTITY *)action->data)->space, "credits");
  
  if (credits) {
    CDATA_CREDITS *creditsData = (CDATA_CREDITS *)entity_getComponentData(credits, COMP_CREDITSSCREENLOGIC);
    creditsData->finishedFading = true;
  }
}


static void fadeIn_onStart(ACTION *action) {
  ENTITY *credits = space_getEntity(((ENTITY *)action->data)->space, "credits");
  
  if (credits) {
    CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(credits, COMP_MOUSEBOX);
    CDATA_CREDITS *creditsData = (CDATA_CREDITS *)entity_getComponentData(credits, COMP_CREDITSSCREENLOGIC);
    creditsData->finishedFading = false;
    mbox->active = true;
  }
}


void credits_onPressed(COMPONENT *self) {
  ENTITY *credits = space_getEntity(self->owner->space, "credits");
  CDATA_CUSTOMBUTTON *data = (CDATA_CUSTOMBUTTON *)self->data;

  // if options are open, don't do anything
  if (space_getEntity(self->owner->space, "options"))
    return;

  al_pushBack(&data->actions, action_create(self->owner, fadeIn_update, fadeIn_onStart, fadeIn_onEnd, false, 0.5f));
}

void credits_onExit(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  // if options are open, don't do anything
  if (space_getEntity(self->owner->space, "options"))
    return;

  sprite->color.a = 1.0f;

}


/**** ON/OFF Fullscreen ****/
void fullScreen_onEntered(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  sprite->color.a = 0.8f;
  sound_playSound(&self->owner->space->game->systems.sound, "hover");
}

void fullScreen_onPressed(COMPONENT *self) {
  CDATA_CUSTOMBUTTON *data = (CDATA_CUSTOMBUTTON *)self->data;
  COMPONENT *sprite = (COMPONENT *)entity_getComponent(self->owner, COMP_SPRITE);
  CDATA_SPRITE *spriteData = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);

  if (!data->sprite.altSprite) {
    comp_sprite_clearMesh(sprite);
    spriteData->source = data->sprite.altSource;
    data->sprite.altSprite = true;
    self->owner->space->game->config.screen.full = false;
    game_configSave(self->owner->space->game);
  }
  else {
    comp_sprite_clearMesh(sprite);
    spriteData->source = data->sprite.source;
    data->sprite.altSprite = false;
    self->owner->space->game->config.screen.full = true;
    game_configSave(self->owner->space->game);
  }
}

void fullScreen_onExit(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  sprite->color.a = 1.0f;
}

/**** ON/OFF tutorial ****/
void tutorial_onEntered(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  sprite->color.a = 0.8f;
  sound_playSound(&self->owner->space->game->systems.sound, "hover");
}

void tutorial_onPressed(COMPONENT *self) {
  CDATA_CUSTOMBUTTON *data = (CDATA_CUSTOMBUTTON *)self->data;
  SPACE *ui = game_getSpace(self->owner->space->game, "ui");
  COMPONENT *sprite = (COMPONENT *)entity_getComponent(self->owner, COMP_SPRITE);
  CDATA_SPRITE *spriteData = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);

  // press to off
  if (!data->sprite.altSprite) {
    comp_sprite_clearMesh(sprite);
    spriteData->source = data->sprite.altSource;
    data->sprite.altSprite = true;
    self->owner->space->game->config.tutorial = 0;
    game_configSave(self->owner->space->game);
  }

  // press to on
  else {
    comp_sprite_clearMesh(sprite);
    spriteData->source = data->sprite.source;
    data->sprite.altSprite = false;
    self->owner->space->game->config.tutorial = 1;
    game_configSave(self->owner->space->game);
  }
}

void tutorial_onExit(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  sprite->color.a = 1.0f;
}

/********** Exit **********/
void exit_onEntered(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  // if options are open, don't do anything
  if (space_getEntity(self->owner->space, "options"))
    return;

  sprite->color.a = 0.8f;
  sound_playSound(&self->owner->space->game->systems.sound, "hover");
}

void exit_onPressed(COMPONENT *self) {
  // if options are open, don't do anything
  if (space_getEntity(self->owner->space, "options"))
    return;

  self->owner->space->game->destroying = true;
}

void exit_onExit(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  // if options are open, don't do anything
  if (space_getEntity(self->owner->space, "options"))
    return;

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

/********* Pause *********/
void pause_onEntered(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  SPACE *ui = game_getSpace(self->owner->space->game, "ui");
  CDATA_UI_BUTTON *data = (CDATA_UI_BUTTON *)entity_getComponentData(space_getEntity(ui, "build_button"), COMP_UI_BUTTON);

  sprite->color.a = 0.8f;
  sound_playSound(&self->owner->space->game->systems.sound, "hover");
  if (!data->hoverText) {
    VEC3 position;
    vec3_set(&position, -301, 151, 0);
    data->hoverText = genericText_create(ui, &position, NULL, "fonts/gothic/12", "Menu!", &colors[C_NAVY_DARK], TEXTALIGN_CENTER, TEXTALIGN_TOP);
  }
}

void pause_onPressed(COMPONENT *self) {
  CDATA_PLAYERLOGIC *playerData = entity_getComponentData(space_getEntity(self->owner->space, "player"), COMP_PLAYERLOGIC);
  SPACE *tutorial = game_getSpace(self->owner->space->game, "tutorial");
  if (!space_getEntity(tutorial, "pauseScreen")) {
    CDATA_PAUSESCREEN *pauseData = (CDATA_PAUSESCREEN *)entity_getComponentData(space_addEntity(tutorial, arch_pauseScreen, "pauseScreen"), COMP_PAUSESCREENLOGIC);
    playerData->lastMode = playerData->currentMode;
    pause_onExit(self);
  }
}

void pause_onExit(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  SPACE *ui = game_getSpace(self->owner->space->game, "ui");
  CDATA_UI_BUTTON *data = (CDATA_UI_BUTTON *)entity_getComponentData(space_getEntity(ui, "build_button"), COMP_UI_BUTTON);


  sprite->color.a = 1.0f;
  if (data->hoverText) {
    entity_destroy(data->hoverText);
    data->hoverText = NULL;
  }
}

/******* Empty ********/
void empty_onPressed(COMPONENT *self) {
  SPACE *menu = game_getSpace(self->owner->space->game, "menu");
  
  if (space_getEntity(menu, "options")) {
    LIST *optionsList = list_create();
    LIST_NODE *node;
    space_getAllEntities(menu, "options", optionsList);
    node = optionsList->first;
    while (node) {
      entity_destroy((ENTITY *)node->data);
      node = node->next;
    }
    list_destroy(optionsList);
  } 
}

/********** Management Exit **********/
void mExit_onEntered(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);

  sprite->color.a = 0.8f;
  sound_playSound(&self->owner->space->game->systems.sound, "hover");

}

void mExit_onPressed(COMPONENT *self) {
  SPACE *ui = game_getSpace(self->owner->space->game, "ui");
  VEC3 position = { 0 };
  COMPONENT *management = entity_getComponent(space_getEntity(ui, "manage_button"), COMP_MANAGEMENT); 

  comp_managementRemove(management);
}

void mExit_onExit(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);

  sprite->color.a = 1.0f;

}