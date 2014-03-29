/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "backgroundlogic.h"
#include "mousebox.h"
#include "playerlogic.h"
#include "poptext.h"
#include "sound.h"
#include "inspectionscreenlogic.h"
#include "cloud.h"

void comp_backgroundLogic_frameUpdate(COMPONENT *self, void *event) {
  //CDATA_BACKGROUNDLOGIC *comData = (CDATA_BACKGROUNDLOGIC *)self->data;
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  SPACE *ui = game_getSpace(self->owner->space->game, "ui");
  ENTITY *inspectionScreen = space_getEntity(ui, "inspection_screen");
  CDATA_INSPECTIONSCREEN *inspectData = (CDATA_INSPECTIONSCREEN *)entity_getComponentData(inspectionScreen, COMP_INSPECTIONSCREENLOGIC); 
  INPUT_CONTAINER *input = &self->owner->space->game->input;

  if (mbox->left.pressed) {
    VEC3 pos = { 0 };
    POINT mousePos;
    VEC4 col = { 0.0f, 0.0f, 0.0f, 1.0f };
    space_mouseToWorld(self->owner->space, &input->mouse.position, &mousePos);
    pos.x = (float)mousePos.x;
    pos.y = (float)mousePos.y;
    //popText_create(self->owner->space, &pos, NULL, "fonts/gothic/12", "oh", &col, POPTYPE_DEFAULT, 1.0f);
    //sound_playSound(&self->owner->space->game->systems.sound, "oh");
    
    if (inspectData->active == true)
      inspectData->active = false;
  }

  if (mbox->left.down) {
    ENTITY *player = space_getEntity(game_getSpace(self->owner->space->game, "ui"), "player");
    CDATA_PLAYERLOGIC *playerData = (CDATA_PLAYERLOGIC *)entity_getComponentData(player, COMP_PLAYERLOGIC);
    playerData->dragging = true;
    input_lockMouse(input);
    playerData->dragOrigin.x = input->mouse.position.x;
    playerData->dragOrigin.y = input->mouse.position.y;
    input->mouse.handled[MBUTTON_LEFT] = true;
  }

  // CLOUD MANAGER
  /*if(comData->clouds < comData->maxClouds) {
    space_addEntity(game_getSpace(self->owner->space->game, "bg"), arch_cloud, "cloud");
    ++comData->clouds;
  }*/
}

void comp_backgroundLogic(COMPONENT *self) {

  COMPONENT_INIT_NULL(self, COMP_BACKGROUNDLOGIC);
  component_depend(self, COMP_MOUSEBOX);
  self->events.frameUpdate = comp_backgroundLogic_frameUpdate;
}