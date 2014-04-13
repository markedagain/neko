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
  ENTITY *created;
  
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
  else {
  // create a box
  genericSprite_createBlank(menu, &position, &dimensions, &colors[C_NAVY_LIGHT], "options");

  // create the fullscreen word
  vec3_set(&position, -120.0f, 50.0f, 0);
  created = genericSprite_create(menu, &position, "options", "options/fullscreen");

  // create the true false button
  // if currently full screen
  if (self->owner->space->game->config.screen.full) {
    vec3_set(&position, 50.0f, 50.0f, 0);
    createCustomButton(fullScreen_onEntered, NULL, fullScreen_onPressed, fullScreen_onExit, NULL,
                           self->owner->space, &position, "options",
                           1.0f, 1.0f,
                           true, "options/on", "options/off", NULL,
                           false, NULL, NULL, 
                           NULL, TEXTALIGN_CENTER, TEXTALIGN_CENTER);
  }

  // if currently not full screen
  else {
    CDATA_CUSTOMBUTTON *data;
    CDATA_SPRITE *spriteData; 
    vec3_set(&position, 50.0f, 50.0f, 0);
    created = createCustomButton(fullScreen_onEntered, NULL, fullScreen_onPressed, fullScreen_onExit, NULL,
                           self->owner->space, &position, "options",
                           1.0f, 1.0f,
                           true, "options/on", "options/off", NULL,
                           false, NULL, NULL, 
                           NULL, TEXTALIGN_CENTER, TEXTALIGN_CENTER);
    data = (CDATA_CUSTOMBUTTON *)entity_getComponentData(created, COMP_CUSTOMBUTTONLOGIC);
    data->sprite.altSprite = true;
    spriteData = (CDATA_SPRITE *)entity_getComponentData(created, COMP_SPRITE);
    spriteData->source = data->sprite.altSource;
  }


  // create the newsfeed word
  vec3_set(&position, -120.0f, -50.0f, 0);
  created = genericSprite_create(menu, &position, "options", "options/newsfeed");

  // create the true false button
  vec3_set(&position, 50.0f, -50.0f, 0);
  createCustomButton(newsFeed_onEntered, NULL, newsFeed_onPressed, newsFeed_onExit, NULL,
                         self->owner->space, &position, "options",
                         1.0f, 1.0f,
                         true, "options/on", "options/off", NULL,
                         false, NULL, NULL, 
                         NULL, TEXTALIGN_CENTER, TEXTALIGN_CENTER);
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
    CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(credits, COMP_MOUSEBOX);

    mbox->active = true;
  }
}

void credits_onPressed(COMPONENT *self) {
  ENTITY *credits = space_getEntity(self->owner->space, "credits");
  CDATA_CUSTOMBUTTON *data = (CDATA_CUSTOMBUTTON *)self->data;

  // if options are open, don't do anything
  if (space_getEntity(self->owner->space, "options"))
    return;

  al_pushBack(&data->actions, action_create(self->owner, fadeIn_update, NULL, fadeIn_onEnd, false, 0.75f));
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

/**** ON/OFF newsfeed ****/
void newsFeed_onEntered(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  sprite->color.a = 0.8f;
  sound_playSound(&self->owner->space->game->systems.sound, "hover");
}

void newsFeed_onPressed(COMPONENT *self) {
  CDATA_CUSTOMBUTTON *data = (CDATA_CUSTOMBUTTON *)self->data;
  SPACE *ui = game_getSpace(self->owner->space->game, "ui");
  COMPONENT *sprite = (COMPONENT *)entity_getComponent(self->owner, COMP_SPRITE);
  CDATA_SPRITE *spriteData = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  CDATA_NEWSFEEDLOGIC *newsFeedData = (CDATA_NEWSFEEDLOGIC *)entity_getComponentData(space_getEntity(ui, "newsFeed"), COMP_NEWSFEEDLOGIC);

  if (!data->sprite.altSprite) {
    comp_sprite_clearMesh(sprite);
    spriteData->source = data->sprite.altSource;
    data->sprite.altSprite = true;
    newsFeedData->locked = false;
  }
  else {
    comp_sprite_clearMesh(sprite);
    spriteData->source = data->sprite.source;
    data->sprite.altSprite = false;
    newsFeedData->locked = true;
  }
}

void newsFeed_onExit(COMPONENT *self) {
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

  sprite->color.a = 0.8f;
  sound_playSound(&self->owner->space->game->systems.sound, "hover");
}

void pause_onPressed(COMPONENT *self) {
  CDATA_PLAYERLOGIC *playerData = entity_getComponentData(space_getEntity(self->owner->space, "player"), COMP_PLAYERLOGIC);
  SPACE *tutorial = game_getSpace(self->owner->space->game, "tutorial");
  if (!space_getEntity(tutorial, "pauseScreen")) {
    CDATA_PAUSESCREEN *pauseData = (CDATA_PAUSESCREEN *)entity_getComponentData(space_addEntity(tutorial, arch_pauseScreen, "pauseScreen"), COMP_PAUSESCREENLOGIC);
    pauseData->lastMode = playerData->currentMode;
    pause_onExit(self);
  }
}

void pause_onExit(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);

  sprite->color.a = 1.0f;

}
