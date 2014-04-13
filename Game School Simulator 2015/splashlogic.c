/******************************************************************************
Filename: splashlogic.c

Project Name: Game School Simulator 2015

Author: Adam Rezich

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "splashlogic.h"
#include "sound.h"
#include "generictext.h"
#include "input.h"
#include "gameinitialize.h"

#define DIGIPEN_TIME 3.0
#define NEKOMEANSCAT_TIME 3.0

void comp_splashLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_SPLASHLOGIC *data = (CDATA_SPLASHLOGIC *)self->data;
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  ENTITY *bg = space_getEntity(self->owner->space, "splash_bg");
  INPUT_CONTAINER *input = &self->owner->space->game->input;

  // OH easter egg
  if(input->keyboard.keys[KEY_O] == ISTATE_DOWN && input->keyboard.keys[KEY_H] == ISTATE_DOWN)
      data->ohSound = true;

  data->timer -= (float)updateEvent->dt;
  if (bg && data->fadeBackground) {
    CDATA_SPRITE *bgSprite = (CDATA_SPRITE *)entity_getComponentData(bg, COMP_SPRITE);
    bgSprite->color.a -= 0.01f;
    if (bgSprite->color.a <= 0.75 && !data->secondLogo) {
      sprite->source = "splash";
      data->secondLogo = true;
      data->timer = (float)NEKOMEANSCAT_TIME;
      if(!data->ohSound)
        sound_playSound(&self->owner->space->game->systems.sound, "logo");
      else
        sound_playSound(&self->owner->space->game->systems.sound, "logo_oh");
    }
    if (bgSprite->color.a <= 0.0f) {
      data->fadeBackground = false;
      entity_destroy(bg);
    }
  }
  if (data->secondLogo) {
    if (data->timer <= 0.0f) {
      sprite->color.a -= 0.05f;
      if (sprite->color.a <= 0) {

        VEC3 position = { 0.0f , 0.0f, 0.0f };
        //VEC4 color = { 0.0f, 0.0f, 0.0f, 1.0f };
        SPACE *simSpace = game_getSpace(self->owner->space->game, "sim");
        //genericText_create(game_getSpace(self->owner->space->game, "ui"), &position, "title", "fonts/gothic/28", "Game School Simulator 2015", &color, TEXTALIGN_CENTER, TEXTALIGN_TOP);
        //vec3_set(&position, 0.0f, 180.0f - 4.0f - 28.0f, 0.0f);
        //genericText_create(game_getSpace(self->owner->space->game, "ui"), &position, "subtitle", "fonts/gothic/16", "Alpha presentation", &color, TEXTALIGN_CENTER, TEXTALIGN_TOP);
        //simSpace->systems.time.scale = 0.0166666666666667f;
        sound_playSongLooped(&self->owner->space->game->systems.sound, "01_loop");

        //////////////////////////////////////////
        sprite->color.a = 0;
        entity_destroy(self->owner);
        createMainMenu(self->owner->space->game);
      }
    }
    else {
      sprite->color.a += 0.026f;
      if (sprite->color.a >= 1.0f) {
        sprite->color.a = 1.0f;
      }
    }
  }
  else {
    if (data->timer <= 0.0f) {
      sprite->color.a -= 0.05f;
      if (sprite->color.a <= 0) {
        sprite->color.a = 0;
        data->fadeBackground = true;
      }
    }
    else {
      sprite->color.a += 0.026f;
      if (sprite->color.a >= 1.0f) {
        sprite->color.a = 1.0f;
      }
    }
  }
}

void comp_splashLogic(COMPONENT *self) {
  CDATA_SPLASHLOGIC data = { 0 };
  data.secondLogo = false;
  data.fadeBackground = false;
  data.ohSound = false;
  data.timer = (float)DIGIPEN_TIME;
  COMPONENT_INIT(self, COMP_SPLASHLOGIC, data);
  component_depend(self, COMP_TRANSFORM);
  component_depend(self, COMP_SPRITE);
  self->events.logicUpdate = comp_splashLogic_logicUpdate;
}