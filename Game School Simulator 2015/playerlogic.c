/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

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

#define GROUND_HEIGHT 24

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
  SPACE *bg = game_getSpace(self->owner->space->game, "bg");
  SPACE *mg = game_getSpace(self->owner->space->game, "mg");
  SPACE *fg = game_getSpace(self->owner->space->game, "fg");
  float newZoom = bg->systems.camera.transform.scale.x + zoom;
  float gameHeight = (float)self->owner->space->game->dimensions.height;
  newZoom = (float)max((float)min(newZoom, 1.0f), 0.5f);
    
  bg->systems.camera.transform.scale.x = newZoom;
  bg->systems.camera.transform.scale.y = newZoom;
  bg->systems.camera.transform.translation.y = (0.5f * ((1.0f / newZoom) * gameHeight)) - (0.5f * gameHeight) + 180 - 24;
  mg->systems.camera.transform.scale.x = newZoom;
  mg->systems.camera.transform.scale.y = newZoom;
  mg->systems.camera.transform.translation.y = (0.5f * ((1.0f / newZoom) * gameHeight)) - (0.5f * gameHeight) + 180 - 24;
  fg->systems.camera.transform.scale.x = newZoom;
  fg->systems.camera.transform.scale.y = newZoom;
  fg->systems.camera.transform.translation.y = (0.5f * ((1.0f / newZoom) * gameHeight)) - (0.5f * gameHeight) + 180 - 24;
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
  pan_reset(self);
  zoom_reset(self);
  //sound_playSong(&self->owner->space->game->systems.sound, "01");
}

void comp_playerLogic_frameUpdate(COMPONENT *self, void *event) {
  CDATA_PLAYERLOGIC *data = (CDATA_PLAYERLOGIC *)self->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  SPACE *simSpace = game_getSpace(self->owner->space->game,"sim");
  CDATA_SCHOOLLOGIC *schoolData = (CDATA_SCHOOLLOGIC *)entity_getComponentData((ENTITY *)space_getEntity(simSpace, "gameManager"), COMP_SCHOOLLOGIC);
  COMPONENT *schoolLogic = (COMPONENT *)entity_getComponent((ENTITY *)space_getEntity(simSpace, "gameManager"), COMP_SCHOOLLOGIC);
  POINT mousePos;

  space_mouseToWorld(self->owner->space, &input->mouse.position, &mousePos);

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
  if (input->keyboard.keys[KEY_P] == ISTATE_DOWN) {
    zoom_reset(self);
    pan_reset(self);
  }
  if (input->keyboard.keys[KEY_F1] == ISTATE_PRESSED) {
    ENTITY *ent = space_getEntity(self->owner->space, "subtitle");
    genericText_setText(ent, "Engine Proof Demonstration");
  }
  if (input->keyboard.keys[KEY_F2] == ISTATE_PRESSED) {
    ENTITY *ent = space_getEntity(self->owner->space, "subtitle");
    genericText_setText(ent, "Alpha Presentation");
  }
  /* if (input->keyboard.keys[KEY_B] == ISTATE_PRESSED) {
    self->owner->space->systems.camera.transform.scale.x += 1.0f;
    self->owner->space->systems.camera.transform.scale.y += 1.0f;
  } */
  if (input->keyboard.keys[KEY_N] == ISTATE_PRESSED) {
    data->gameMode = DEFAULT;
  }
  /*
  if (input->keyboard.keys[KEY_1] == ISTATE_DOWN) {
    ENTITY *ent = space_getEntity(self->owner->space, "TEST1");
    CDATA_TRANSFORM *trans = entity_getComponentData(ent, COMP_TRANSFORM);
    trans->rotation += 0.2f;
  }
  if (input->keyboard.keys[KEY_2] == ISTATE_DOWN) {
    ENTITY *ent = space_getEntity(self->owner->space, "TEST1");
    CDATA_TRANSFORM *trans = entity_getComponentData(ent, COMP_TRANSFORM);
    trans->scale.x -= 0.1f;
  }*/
  /*if (input->keyboard.keys[KEY_Q] == ISTATE_PRESSED) {
    game_resize(self->owner->space->game, 1280, 720);
  }*/

  /*if (input->mouse.wheel.direction == -1)
    zoom(self, -0.1f);
  if (input->mouse.wheel.direction == 1)
    zoom(self, 0.1f);*/


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
  if (input->mouse.handled[MBUTTON_LEFT] == 0) {
    if (input->mouse.left == ISTATE_PRESSED) {
      //input->mouse.handled[MBUTTON_LEFT] = true;
      data->dragging = true;
      input_lockMouse(input);
      data->dragOrigin.x = input->mouse.position.x;
      data->dragOrigin.y = input->mouse.position.y;
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
  }
  else {
    data->dragging = false;
    input_unlockMouse(input);
  }



  //Change Tuition
  if(input->keyboard.keys[KEY_LEFTBRACKET] == ISTATE_PRESSED)
    schoolData->tuition -= 1000;
  if(input->keyboard.keys[KEY_RIGHTBRACKET] == ISTATE_PRESSED)
    schoolData->tuition += 1000;

  //Create Lobby room if "L" is pressed
  if(input->keyboard.keys[KEY_L] == ISTATE_PRESSED) {
    comp_schoolLogic_constructRoom(self, ROOMTYPE_LOBBY, 2, 2, 7);
  }
  /* Create Class room if "K" is pressed
  if(input->keyboard.keys[KEY_K] == ISTATE_PRESSED) {
    comp_schoolLogic_findBuildSpots(schoolLogic, schoolData, ROOMTYPE_CLASS);
  }
  // Create Library room if "J" is pressed
  if(input->keyboard.keys[KEY_J] == ISTATE_PRESSED) {
    comp_schoolLogic_findBuildSpots(schoolLogic, schoolData, ROOMTYPE_LIBRARY);
  }
  // Create TeamSpace room if "H" is pressed
  if(input->keyboard.keys[KEY_H] == ISTATE_PRESSED) {
    comp_schoolLogic_findBuildSpots(schoolLogic, schoolData, ROOMTYPE_TEAMSPACE);
  }

  // List all rooms constructed
  if(input->keyboard.keys[KEY_PERIOD] == ISTATE_PRESSED) {
    comp_schoolLogic_listRooms(schoolLogic, schoolData);
  }*/

  // List all enrolled students
  if(input->keyboard.keys[KEY_COMMA] == ISTATE_PRESSED) {
    comp_schoolLogic_listStudents(schoolLogic, schoolData);
  }

  // List all alumni
  if(input->keyboard.keys[KEY_M] == ISTATE_PRESSED) {
    comp_schoolLogic_listAlumni(schoolLogic, schoolData);
  }
}

void comp_playerLogic(COMPONENT *self) {
  CDATA_PLAYERLOGIC data = { 0 };
  COMPONENT_INIT(self, COMP_PLAYERLOGIC, data);
  component_depend(self, COMP_TRANSFORM);
  self->events.initialize = comp_playerLogic_initialize;
  self->events.logicUpdate = comp_playerLogic_logicUpdate;
  self->events.frameUpdate = comp_playerLogic_frameUpdate;
}
