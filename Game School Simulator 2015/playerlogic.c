/******************************************************************************
Filename: playerlogic.c

Project Name: Game School Simulator 2015

Author: Eduardo Gorinstein

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "playerLogic.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/entity.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/game.h"
#include "../NekoEngine/sound.h"
#include "room.h"
#include "roomlogic.h"
#include "schoollogic.h"
#include "gamemanager.h"
#include "studentdata.h"
#include "generictext.h"
#include <math.h>
#include <stdio.h>
#include "timemanager.h"
#include "tutorial.h"
#include "UI_button.h"
#include "pausescreen.h"
#include "pausescreenlogic.h"
#include "sound.h"
#include "random.h"
#include "management.h"
#include "gameinitialize.h"

#define GROUND_HEIGHT 24
#define BUILDENDPOS 136.0f
#define STUDENT_VOLUME_MAX 100

void comp_playerLogic_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  
}

void pan(COMPONENT *self, float x, float y, POINT *outPoint) {
  SPACE *bg = game_getSpace(self->owner->space->game, "bg");
  SPACE *mg = game_getSpace(self->owner->space->game, "mg");
  SPACE *fg = game_getSpace(self->owner->space->game, "fg");
  float zoom = bg->systems.camera.transform.scale.x;
  float oldX = bg->systems.camera.transform.translation.x;
  float oldY = bg->systems.camera.transform.translation.y;
  float newX = bg->systems.camera.transform.translation.x + x;
  float newY = bg->systems.camera.transform.translation.y + y;
  newX = (float)min(max(newX, -80.0f * 4.0f * zoom), 80.0f * 4.0f * zoom);
  bg->systems.camera.transform.translation.x = newX;
  bg->systems.camera.transform.translation.y = newY;
  mg->systems.camera.transform.translation.x = newX;
  mg->systems.camera.transform.translation.y = newY;
  fg->systems.camera.transform.translation.x = newX;
  fg->systems.camera.transform.translation.y = newY;
  if (outPoint != NULL) {
    outPoint->x = (int)floor(newX - oldX);
    outPoint->y = (int)floor(newY - oldY);
  }
}
void pan_reset(COMPONENT *self) {
  SPACE *bg = game_getSpace(self->owner->space->game, "bg");
  SPACE *mg = game_getSpace(self->owner->space->game, "mg");
  SPACE *fg = game_getSpace(self->owner->space->game, "fg");
  bg->systems.camera.transform.translation.x = 0.0f;
  bg->systems.camera.transform.translation.y = 180.0f - 24.0f;
  mg->systems.camera.transform.translation.x = 0.0f;
  mg->systems.camera.transform.translation.y = 180.0f - 24.0f;
  fg->systems.camera.transform.translation.x = 0.0f;
  fg->systems.camera.transform.translation.y = 180.0f - 24.0f;
}


void zoom(COMPONENT *self, float zoom) {
  CDATA_PLAYERLOGIC *data = (CDATA_PLAYERLOGIC *)self->data;
  SPACE *simSpace = game_getSpace(self->owner->space->game,"sim");
  CDATA_SCHOOLLOGIC *schoolData = (CDATA_SCHOOLLOGIC *)entity_getComponentData((ENTITY *)space_getEntity(simSpace, "gameManager"), COMP_SCHOOLLOGIC);
  SPACE *bg = game_getSpace(self->owner->space->game, "bg");
  SPACE *mg = game_getSpace(self->owner->space->game, "mg");
  SPACE *fg = game_getSpace(self->owner->space->game, "fg");
  float newZoom = bg->systems.camera.transform.scale.x + zoom;
  float gameHeight = (float)self->owner->space->game->dimensions.height;
  float zoomScale;
  float schoolScale;
  newZoom = (float)max((float)min(newZoom, 1.0f), 0.5f);
  zoomScale = (newZoom - 0.5f) * 2;
  schoolScale = min((schoolData->currentStudents / (float)STUDENT_VOLUME_MAX), 1.0f);
  sound_setVolume_ambient(&self->owner->space->game->systems.sound, 1.0f, (1.0f - zoomScale) * 0.6f, zoomScale * schoolScale);
    
  bg->systems.camera.transform.scale.x = newZoom;
  bg->systems.camera.transform.scale.y = newZoom;
  mg->systems.camera.transform.scale.x = newZoom;
  mg->systems.camera.transform.scale.y = newZoom;
  fg->systems.camera.transform.scale.x = newZoom;
  fg->systems.camera.transform.scale.y = newZoom;
  if (!data->yPan) {
    bg->systems.camera.transform.translation.y = (0.5f * ((1.0f / newZoom) * gameHeight)) - (0.5f * gameHeight) + 180.0f - 24.0f;
    mg->systems.camera.transform.translation.y = (0.5f * ((1.0f / newZoom) * gameHeight)) - (0.5f * gameHeight) + 180.0f - 24.0f;
    fg->systems.camera.transform.translation.y = (0.5f * ((1.0f / newZoom) * gameHeight)) - (0.5f * gameHeight) + 180.0f - 24.0f;
  }
  pan(self, 0.0f, 0.0f, NULL);
}
void zoom_reset(COMPONENT *self) {
  SPACE *bg = game_getSpace(self->owner->space->game, "bg");
  SPACE *mg = game_getSpace(self->owner->space->game, "mg");
  SPACE *fg = game_getSpace(self->owner->space->game, "fg");
  bg->systems.camera.transform.scale.x = 1.0f;
  bg->systems.camera.transform.scale.y = 1.0f;
  mg->systems.camera.transform.scale.x = 1.0f;
  mg->systems.camera.transform.scale.y = 1.0f;
  fg->systems.camera.transform.scale.x = 1.0f;
  fg->systems.camera.transform.scale.y = 1.0f;
}

void comp_playerLogic_initialize(COMPONENT *self, void *event) {
  CDATA_PLAYERLOGIC *data = (CDATA_PLAYERLOGIC *)self->data;
  pan_reset(self);
  zoom_reset(self);
  data->yPan = false;
}

void comp_playerLogic_frameUpdate(COMPONENT *self, void *event) {
  CDATA_PLAYERLOGIC *data = (CDATA_PLAYERLOGIC *)self->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  SPACE *simSpace = game_getSpace(self->owner->space->game,"sim");
  CDATA_SCHOOLLOGIC *schoolData = (CDATA_SCHOOLLOGIC *)entity_getComponentData((ENTITY *)space_getEntity(simSpace, "gameManager"), COMP_SCHOOLLOGIC);
  COMPONENT *schoolLogic = (COMPONENT *)entity_getComponent((ENTITY *)space_getEntity(simSpace, "gameManager"), COMP_SCHOOLLOGIC);
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  POINT mousePos;
  double elapsedTime = self->owner->space->game->systems.time.elapsed;
  
  space_mouseToWorld(self->owner->space, &input->mouse.position, &mousePos);

  // win state
  if (data->currentMode == GM_WIN) {
    if (input->keyboard.keys[KEY_ENTER] == ISTATE_PRESSED) {
      LIST *winScreen = list_create();
      LIST_NODE *node;
      space_getAllEntities(self->owner->space, "winScreen", winScreen);
      node = winScreen->first;
      while (node) {
        entity_destroy((ENTITY *)node->data);
        node = node->next;
      }
      list_destroy(winScreen);
      comp_timeManager_pause(self);
      data->currentMode = GM_PLAY;
    }
  }

  // lose state
  else if (data->currentMode == GM_LOSE) {
    if (input->keyboard.keys[KEY_ENTER] == ISTATE_PRESSED) {
      self->owner->space->game->resetFunction = makeAllNewGame;
    }
  }


  else if (data->currentMode == GM_PLAY && self->owner->space->game->systems.time.scale != 0) {

    if (data->lastSong != 0) {
      data->nextSongTime -= (float)self->owner->space->game->systems.time.dtFrame;
      if (data->nextSongTime <= 0.0f) {
        int nextSong = randomIntRange(0, 1);
        if (data->lastSong == 1) {
          data->lastSong = (nextSong ? 2 : 3);
          sound_playSong(&self->owner->space->game->systems.sound, (nextSong ? "02" : "03"));
          data->nextSongTime = 60.0f * (nextSong ? 1.5f : 2.25f);
        }
        else if (data->lastSong == 2) {
          data->lastSong = (nextSong ? 1 : 3);
          sound_playSong(&self->owner->space->game->systems.sound, (nextSong ? "01" : "03"));
          data->nextSongTime = 60.0f * (nextSong ? 3.0f : 2.25f);
        }
        else {
          data->lastSong = (nextSong ? 2 : 1);
          sound_playSong(&self->owner->space->game->systems.sound, (nextSong ? "02" : "01"));
          data->nextSongTime = 60.0f * (nextSong ? 3.0f : 1.5f);
        }
      }
    }

    // MANAGE INPUT
    if (input->keyboard.keys[KEY_LEFT] == ISTATE_DOWN) {
      pan(self, -4.0f, 0.0f, NULL);
    }
    if (input->keyboard.keys[KEY_RIGHT] == ISTATE_DOWN) {
      pan(self, 4.0f, 0.0f, NULL);
    }
    if (input->keyboard.keys[KEY_UP] == ISTATE_DOWN) {
      zoom(self, 0.01f);
    }
    if (input->keyboard.keys[KEY_DOWN] == ISTATE_DOWN) {
      zoom(self, -0.01f);
    }
    if (input->keyboard.keys[KEY_ESCAPE] == ISTATE_PRESSED) {
      SPACE *tutorial = game_getSpace(self->owner->space->game, "tutorial");
      if (!space_getEntity(tutorial, "pauseScreen")) {
        space_addEntity(tutorial, arch_pauseScreen, "pauseScreen");
        data->lastMode = data->currentMode;
      }
    }

    if (input->keyboard.keys[KEY_F2] == ISTATE_PRESSED) {
      CDATA_SCHOOLLOGIC *schoolData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(space_getEntity(simSpace, "gameManager"), COMP_SCHOOLLOGIC);
      schoolData->reputation += 5;
    }

    if (input->keyboard.keys[KEY_4] == ISTATE_DOWN && input->keyboard.keys[KEY_SHIFT] == ISTATE_DOWN && input->keyboard.keys[KEY_CONTROL] == ISTATE_DOWN) {
      comp_schoolLogic_millionaire(self);
    }
    
    if (input->keyboard.keys[KEY_SPACE] == ISTATE_PRESSED) {
      COMPONENT *buildButton = (COMPONENT *)entity_getComponent(space_getEntity(self->owner->space, "build_button"), COMP_UI_BUTTON);
      comp_UI_button_toggleBuildMode(buildButton);
    }

    if(!data->yPan) {
      if (input->mouse.wheel.delta != 0) {
        if ((data->zoomVelocity > 0 && input->mouse.wheel.delta > 0) || (data->zoomVelocity < 0 && input->mouse.wheel.delta < 0))
          data->zoomVelocity += 0.004f * (float)input->mouse.wheel.delta;
        else
          data->zoomVelocity = 0.012f * (float)input->mouse.wheel.delta;
      }
      zoom(self, data->zoomVelocity);
      if (data->zoomVelocity != 0.0f) {
        if (data->zoomVelocity > 0) {
          data->zoomVelocity -= 0.0008f;
          if (data->zoomVelocity < 0.0005f)
            data->zoomVelocity = 0.0f;
        }
        if (data->zoomVelocity < 0) {
          data->zoomVelocity += 0.0008f;
          if (data->zoomVelocity > -0.0005f)
            data->zoomVelocity = 0.0f;
        }
      }
    }

    if (input->mouse.left == ISTATE_RELEASED && data->dragging) {
      data->dragging = false;
      input_unlockMouse(input);
    }
    if (data->dragging) {
      POINT panned;
      float xdiff = (float)data->dragOrigin.x - (float)input->mouse.position.x;
      xdiff /= (float)(self->owner->space->game->innerWindow.width / self->owner->space->game->dimensions.width);
      pan(self, xdiff, 0.0f, &panned);
      if (panned.x != 0)
        data->dragOrigin.x = input->mouse.position.x;
      input_setMousePos(input, data->dragOrigin.x, data->dragOrigin.y);
    }

    // M - Brings up management screen
    if(input->keyboard.keys[KEY_M] == ISTATE_PRESSED) {
      ENTITY *manageButton = space_getEntity(self->owner->space, "manage_button");
      COMPONENT *management = entity_getComponent(manageButton, COMP_MANAGEMENT);
      comp_managementDisplay(management);
    }
  }
}

void comp_playerLogic(COMPONENT *self) {
  CDATA_PLAYERLOGIC data = { 0 };
  data.yLock = 180.0f - 24.0f;
  COMPONENT_INIT(self, COMP_PLAYERLOGIC, data);
  component_depend(self, COMP_TRANSFORM);
  self->events.initialize = comp_playerLogic_initialize;
  self->events.logicUpdate = comp_playerLogic_logicUpdate;
  self->events.frameUpdate = comp_playerLogic_frameUpdate;
}

void playerLogic_zoom(COMPONENT *playerLogic, float zoomAmt) {
  zoom(playerLogic, zoomAmt);
}

void playerLogic_pan(COMPONENT *playerLogic, float x, float y, POINT *outPoint) {
  pan(playerLogic, x, y, outPoint);
}

void playerLogic_setZoom(COMPONENT *playerLogic, float newZoom) {
  CDATA_PLAYERLOGIC *data = (CDATA_PLAYERLOGIC *)playerLogic->data;
  SPACE *bg = game_getSpace(playerLogic->owner->space->game, "bg");
  SPACE *mg = game_getSpace(playerLogic->owner->space->game, "mg");
  SPACE *fg = game_getSpace(playerLogic->owner->space->game, "fg");
  float gameHeight = (float)playerLogic->owner->space->game->dimensions.height;

  bg->systems.camera.transform.scale.x = newZoom;
  bg->systems.camera.transform.scale.y = newZoom;
  mg->systems.camera.transform.scale.x = newZoom;
  mg->systems.camera.transform.scale.y = newZoom;
  fg->systems.camera.transform.scale.x = newZoom;
  fg->systems.camera.transform.scale.y = newZoom;
  if (!data->yPan) {
    bg->systems.camera.transform.translation.y = (0.5f * ((1.0f / newZoom) * gameHeight)) - (0.5f * gameHeight) + 180 - 24;
    mg->systems.camera.transform.translation.y = (0.5f * ((1.0f / newZoom) * gameHeight)) - (0.5f * gameHeight) + 180 - 24;
    fg->systems.camera.transform.translation.y = (0.5f * ((1.0f / newZoom) * gameHeight)) - (0.5f * gameHeight) + 180 - 24;
  }
}

void playerLogic_setCamVerticalPos(COMPONENT *playerLogic, float newY) {
  SPACE *bg = game_getSpace(playerLogic->owner->space->game, "bg");
  SPACE *mg = game_getSpace(playerLogic->owner->space->game, "mg");
  SPACE *fg = game_getSpace(playerLogic->owner->space->game, "fg");

  bg->systems.camera.transform.translation.y = newY;
  mg->systems.camera.transform.translation.y = newY;
  fg->systems.camera.transform.translation.y = newY;
}