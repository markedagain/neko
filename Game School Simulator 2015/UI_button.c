/******************************************************************************
Filename: UI_button.c

Project Name: Game School Simulator 2015

Author: Samuel Valdez

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "UI_button.h"
#include "mousebox.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/generictext.h"
#include "../Nekoengine/spritetext.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/entity.h"
#include "../NekoEngine/sprite.h"
#include "multisprite.h"
#include "management.h"
#include "ghostroom.h"
#include "playerlogic.h"
#include "roomlogic.h"
#include "UI_build.h"
#include "schoollogic.h"
#include "managescreen.h"
#include "ghostroomlogic.h"
#include "inspectionscreenlogic.h"
#include "gameinitialize.h"
#include "timemanager.h"
#include "namescreen.h"
#include "tutorial.h"
#include "colors.h"
#include "pausescreenlogic.h"

#define BUILDENDPOS 100.0f
#define VOLUME_STEP 0.05f

// all the pause menu stuff goes here
void comp_UI_buttonFrameUpdate(COMPONENT *self, void *event) {
  CDATA_UI_BUTTON *data = (CDATA_UI_BUTTON *)self->data;
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  ENTITY *pauseScreen = space_getEntity(self->owner->space, "pauseScreen");
  CDATA_PAUSESCREEN *pauseData;
  if (pauseScreen)
    pauseData = (CDATA_PAUSESCREEN *)entity_getComponentData(pauseScreen, COMP_PAUSESCREENLOGIC);

  switch (data->type) {
  case BUTTON_MASTER_VOL_UP:
  case BUTTON_MASTER_VOL_DOWN:
  case BUTTON_MUSIC_VOL_UP:
  case BUTTON_MUSIC_VOL_DOWN:
  case BUTTON_SOUND_VOL_UP:
  case BUTTON_SOUND_VOL_DOWN:
  case BUTTON_AMBIENT_VOL_UP:
  case BUTTON_AMBIENT_VOL_DOWN:
  case BUTTON_MAIN_MENU:
  case BUTTON_CLOSE_OPTIONS:
    if (mbox->entered) {
      CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
      sound_playSound(&self->owner->space->game->systems.sound, "hover");
      sprite->color.a = 0.8f;
    }
    else if (mbox->exited) {
      CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
      sprite->color.a = 1.0f;
    }
  }



  if (mbox->left.pressed) {
    switch(data->type) {
    case BUTTON_MASTER_VOL_UP:
      sound_setVolume_master(&self->owner->space->game->systems.sound, self->owner->space->game->systems.sound.volume.master + VOLUME_STEP);
      if (self->owner->space->game->systems.sound.volume.master > 1.0f)
        sound_setVolume_master(&self->owner->space->game->systems.sound, 1.0f);
      sprintf(pauseData->masterBuffer, "%d%%", (int)(ceil(self->owner->space->game->systems.sound.volume.master * 100)));
      genericText_setText(pauseData->masterText, pauseData->masterBuffer);
      break;

    case BUTTON_MASTER_VOL_DOWN:
      sound_setVolume_master(&self->owner->space->game->systems.sound, self->owner->space->game->systems.sound.volume.master - VOLUME_STEP);
      if (self->owner->space->game->systems.sound.volume.master < 0)
        sound_setVolume_master(&self->owner->space->game->systems.sound, 0);
      sprintf(pauseData->masterBuffer, "%d%%", (int)(ceil(self->owner->space->game->systems.sound.volume.master * 100)));
      genericText_setText(pauseData->masterText, pauseData->masterBuffer);
      break;

    case BUTTON_MUSIC_VOL_UP:
      sound_setVolume_music(&self->owner->space->game->systems.sound, self->owner->space->game->systems.sound.volume.music + VOLUME_STEP);
      if (self->owner->space->game->systems.sound.volume.music > 1.0f)
        sound_setVolume_music(&self->owner->space->game->systems.sound, 1.0f);
      sprintf(pauseData->musicBuffer, "%d%%", (int)(ceil(self->owner->space->game->systems.sound.volume.music * 100)));
      genericText_setText(pauseData->musicText, pauseData->musicBuffer);
      break;

    case BUTTON_MUSIC_VOL_DOWN:
      sound_setVolume_music(&self->owner->space->game->systems.sound, self->owner->space->game->systems.sound.volume.music - VOLUME_STEP);
      if (self->owner->space->game->systems.sound.volume.music < 0)
        sound_setVolume_music(&self->owner->space->game->systems.sound, 0);
      sprintf(pauseData->musicBuffer, "%d%%", (int)(ceil(self->owner->space->game->systems.sound.volume.music * 100)));
      genericText_setText(pauseData->musicText, pauseData->musicBuffer);
      break;

    case BUTTON_SOUND_VOL_UP:
      sound_setVolume_sound(&self->owner->space->game->systems.sound, self->owner->space->game->systems.sound.volume.sound + VOLUME_STEP);
      if (self->owner->space->game->systems.sound.volume.sound > 1.0f)
        sound_setVolume_sound(&self->owner->space->game->systems.sound, 1.0f);
      sprintf(pauseData->soundBuffer, "%d%%", (int)(ceil(self->owner->space->game->systems.sound.volume.sound * 100)));
      genericText_setText(pauseData->soundText, pauseData->soundBuffer);
      break;

    case BUTTON_SOUND_VOL_DOWN:
      sound_setVolume_sound(&self->owner->space->game->systems.sound, self->owner->space->game->systems.sound.volume.sound - VOLUME_STEP);
      if (self->owner->space->game->systems.sound.volume.sound < 0)
        sound_setVolume_sound(&self->owner->space->game->systems.sound, 0);
      sprintf(pauseData->soundBuffer, "%d%%", (int)(ceil(self->owner->space->game->systems.sound.volume.sound * 100)));
      genericText_setText(pauseData->soundText, pauseData->soundBuffer);
      break;

    case BUTTON_AMBIENT_VOL_UP:
      sound_setVolume_ambient(&self->owner->space->game->systems.sound, self->owner->space->game->systems.sound.volume.ambient + VOLUME_STEP,
        self->owner->space->game->systems.sound.volume.ambient1, self->owner->space->game->systems.sound.volume.ambient2);
      if (self->owner->space->game->systems.sound.volume.ambient > 1.0f)
        sound_setVolume_ambient(&self->owner->space->game->systems.sound, 1.0f, self->owner->space->game->systems.sound.volume.ambient1, self->owner->space->game->systems.sound.volume.ambient2);
      sprintf(pauseData->ambientBuffer, "%d%%", (int)(ceil(self->owner->space->game->systems.sound.volume.ambient * 100)));
      genericText_setText(pauseData->ambientText, pauseData->ambientBuffer);
      break;

    case BUTTON_AMBIENT_VOL_DOWN:
      sound_setVolume_ambient(&self->owner->space->game->systems.sound, self->owner->space->game->systems.sound.volume.ambient - VOLUME_STEP,
        self->owner->space->game->systems.sound.volume.ambient1, self->owner->space->game->systems.sound.volume.ambient2);
      if (self->owner->space->game->systems.sound.volume.ambient < 0)
        sound_setVolume_ambient(&self->owner->space->game->systems.sound, 0, self->owner->space->game->systems.sound.volume.ambient1, self->owner->space->game->systems.sound.volume.ambient2);
      sprintf(pauseData->ambientBuffer, "%d%%", (int)(ceil(self->owner->space->game->systems.sound.volume.ambient * 100)));
      genericText_setText(pauseData->ambientText, pauseData->ambientBuffer);
      break;

    case BUTTON_MAIN_MENU:
      self->owner->space->game->resetFunction = makeAllNewGame;
      break;

    case BUTTON_CLOSE_OPTIONS:
      {
        LIST *optionsList = list_create();
        LIST_NODE *node;
        SPACE *ui = game_getSpace(self->owner->space->game, "ui");
        CDATA_PLAYERLOGIC *playerData = (CDATA_PLAYERLOGIC *)entity_getComponentData(space_getEntity(ui, "player"), COMP_PLAYERLOGIC);
        entity_destroy(space_getEntity(self->owner->space, "pauseScreen"));
        space_getAllEntities(self->owner->space, "options", optionsList);
        node = optionsList->first;
        playerData->currentMode = playerData->lastMode;
        self->owner->space->game->systems.time.scale = 1;
        while (node) {
          entity_destroy((ENTITY *)node->data);
          node = node->next;
        }
        list_destroy(optionsList);
        
      }
    }
  }

}


void comp_UI_buttonUpdate(COMPONENT *self, void *event) {
  CDATA_UI_BUTTON *data = (CDATA_UI_BUTTON *)self->data;
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  CDATA_TRANSFORM *transform = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  VEC2 dimensions = { 40.0f, 20.0f };
  VEC3 position = { 10, 10, 0 };
  SPACE *ui = game_getSpace(self->owner->space->game, "ui");
  ENTITY *player = space_getEntity(ui, "player");
  CDATA_PLAYERLOGIC *playerData = (CDATA_PLAYERLOGIC *)entity_getComponentData(player, COMP_PLAYERLOGIC);
  CDATA_INSPECTIONSCREEN *inspectData = (CDATA_INSPECTIONSCREEN *)entity_getComponentData(space_getEntity(ui, "inspection_screen"), COMP_INSPECTIONSCREENLOGIC); 
  SPACE *simSpace = game_getSpace(self->owner->space->game, "sim");
  ENTITY *gameManager = space_getEntity(simSpace, "gameManager");

  CDATA_SCHOOLLOGIC *schoolData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(gameManager, COMP_SCHOOLLOGIC);
  char buffer[80];

  al_update(&data->actions, self->owner->space->game->systems.time.dt);

  if(mbox->entered) {
    if (data->text) {

      // if it's not unlocked, make it say locked
      if (!data->unlocked) {
        switch(data->type){
          
        
          case BUTTON_BUILDLOBBY:
            sprintf(buffer, "Allows\nconstruction!\nLocked");
            genericText_setText(data->text, buffer);
            break;

          case BUTTON_BUILDCLASS:
            sprintf(buffer, "Capacity +30\nAll stats +\nLocked");
            genericText_setText(data->text, buffer);
            break;

          case BUTTON_BUILDLIBRARY:
            sprintf(buffer, "All stats ++\nLocked");
            genericText_setText(data->text, buffer);
            break;

          case BUTTON_BUILDTEAMSPACE:
            sprintf(buffer, "Motivation +++\nLocked");
            genericText_setText(data->text, buffer);
            break;

          case BUTTON_BUILDCAFETERIA:
            sprintf(buffer, "Income + \nMotivation +\nLocked");
            genericText_setText(data->text, buffer);
            break;

          case BUTTON_BUILDSTORE:
            sprintf(buffer, "Generates income!\nLocked");
            genericText_setText(data->text, buffer);
            break;

          case BUTTON_BUILDOFFICES:
            sprintf(buffer, "All stats +\nLocked");
            genericText_setText(data->text, buffer);
            break;

          case BUTTON_BUILDAUDITORIUM:
            sprintf(buffer, "Motivation +++\nLocked");
            genericText_setText(data->text, buffer);
            break;

          case BUTTON_BUILDTUTORING:
            sprintf(buffer, "All stats +\nLocked");
            genericText_setText(data->text, buffer);
            break;

          case BUTTON_BUILDIT:
            sprintf(buffer, "Tech +++\nLocked");
            genericText_setText(data->text, buffer);
            break;

          case BUTTON_BUILDRECREATION:
            sprintf(buffer, "Design +++\nLocked");
            genericText_setText(data->text, buffer);
            break;

          case BUTTON_BUILDFIGURE:
            sprintf(buffer, "Art +++\nLocked");
            genericText_setText(data->text, buffer);
            break;

          default:
            sprintf(buffer, "");
            genericText_setText(data->text, buffer);
            break;
        }
      }

      // if it is unlocked, display price
      else {
        switch(data->type){

          case BUTTON_BUILDLOBBY:
            sprintf(buffer, "Allows\nconstruction!\n$250,000");
            genericText_setText(data->text, buffer);
            break;

          case BUTTON_BUILDCLASS:
            sprintf(buffer, "Capacity +30\nAll stats +\n$100,000");
            genericText_setText(data->text, buffer);
            break;

          case BUTTON_BUILDLIBRARY:
            sprintf(buffer, "All stats ++\n$200,000");
            genericText_setText(data->text, buffer);
            break;

          case BUTTON_BUILDTEAMSPACE:
            sprintf(buffer, "Motivation +++\n$300,000");
            genericText_setText(data->text, buffer);
            break;

          case BUTTON_BUILDCAFETERIA:
            sprintf(buffer, "Income + \nMotivation +\n$350,000");
            genericText_setText(data->text, buffer);
            break;

          case BUTTON_BUILDSTORE:
            sprintf(buffer, "Generates income!\n$250,000");
            genericText_setText(data->text, buffer);
            break;

          case BUTTON_BUILDOFFICES:
            sprintf(buffer, "All stats +\n$100,000");
            genericText_setText(data->text, buffer);
            break;

          case BUTTON_BUILDAUDITORIUM:
            sprintf(buffer, "Motivation +++\n$500,000");
            genericText_setText(data->text, buffer);
            break;

          case BUTTON_BUILDTUTORING:
            sprintf(buffer, "All stats +\n$80,000");
            genericText_setText(data->text, buffer);
            break;

          case BUTTON_BUILDIT:
            sprintf(buffer, "Tech +++\n$150,000");
            genericText_setText(data->text, buffer);
            break;

          case BUTTON_BUILDRECREATION:
            sprintf(buffer, "Design +++\n$150,000");
            genericText_setText(data->text, buffer);
            break;

          case BUTTON_BUILDFIGURE:
            sprintf(buffer, "Art +++\n$150,000");
            genericText_setText(data->text, buffer);
            break;

          case BUTTON_ROOM_UPGRADE:
            sprintf(buffer, "$%i", comp_roomLogic_getRoomUpgradeCost(data->type));
            genericText_setText(data->text, buffer);
            break;

          default:
            sprintf(buffer, "");
            genericText_setText(data->text, buffer);
            break;
        }
      }
    }
  }

  if (mbox->exited) {
    if (data->text) {
      switch(data->type){
        case BUTTON_BUILDLOBBY:
          sprintf(buffer, "Lobby");
          genericText_setText(data->text, buffer);
          break;

        case BUTTON_BUILDCLASS:
          sprintf(buffer, "Classroom");
          genericText_setText(data->text, buffer);
          break;

        case BUTTON_BUILDLIBRARY:
          sprintf(buffer, "Library");
          genericText_setText(data->text, buffer);
          break;

        case BUTTON_BUILDTEAMSPACE:
          sprintf(buffer, "Teamspace");
          genericText_setText(data->text, buffer);
          break;

        case BUTTON_BUILDCAFETERIA:
          sprintf(buffer, "Cafeteria");
          genericText_setText(data->text, buffer);
          break;

        case BUTTON_BUILDSTORE:
          sprintf(buffer, "Store");
          genericText_setText(data->text, buffer);
          break;

        case BUTTON_BUILDOFFICES:
          sprintf(buffer, "Offices");
          genericText_setText(data->text, buffer);
          break;

        case BUTTON_BUILDAUDITORIUM:
          sprintf(buffer, "Auditorium");
          genericText_setText(data->text, buffer);
          break;

        case BUTTON_BUILDTUTORING:
          sprintf(buffer, "Tutoring");
          genericText_setText(data->text, buffer);
          break;

        case BUTTON_BUILDIT:
          sprintf(buffer, "IT");
          genericText_setText(data->text, buffer);
          break;

        case BUTTON_BUILDRECREATION:
          sprintf(buffer, "Recreation");
          genericText_setText(data->text, buffer);
          break;

        case BUTTON_BUILDFIGURE:
          sprintf(buffer, "Figure Drawing");
          genericText_setText(data->text, buffer);
          break;

        case BUTTON_ROOM_UPGRADE:
          sprintf(buffer, "Upgrade!");
          genericText_setText(data->text, buffer);
          break;

        default:
          sprintf(buffer, "");
          genericText_setText(data->text, buffer);
          break;
      }
    }
  }

  if (data->clickable) {
    if (mbox->entered) {
      sound_playSound(&self->owner->space->game->systems.sound, "hover");
      sprite->color.a = 0.8f;
    
      // hover text for top UI buttons
      switch (data->type) {
        case BUTTON_BUILD: {
          if (!data->hoverText) {
            vec3_set(&position, -271, 151, 0);
            data->hoverText = genericText_create(ui, &position, NULL, "fonts/gothic/12", "Build!", &colors[C_NAVY_DARK], TEXTALIGN_CENTER, TEXTALIGN_TOP);
          }
          else
            genericText_setText(data->hoverText, "Build!");
          break;
        }

        case BUTTON_SPEED: {
          if (!data->hoverText) {
            vec3_set(&position, -180, 151, 0);
            data->hoverText = genericText_create(ui, &position, NULL, "fonts/gothic/12", "Change Speed!", &colors[C_NAVY_DARK], TEXTALIGN_CENTER, TEXTALIGN_TOP);
          }
          else
            genericText_setText(data->hoverText, "Change Speed!");
          break;
        }

        case BUTTON_PAUSE: {
          if (!data->hoverText) {
            vec3_set(&position, -209, 151, 0);
            data->hoverText = genericText_create(ui, &position, NULL, "fonts/gothic/12", "Pause!", &colors[C_NAVY_DARK], TEXTALIGN_CENTER, TEXTALIGN_TOP);
          }
          else
            genericText_setText(data->hoverText, "Pause!");
          break;
       }
      }
    }
    if (mbox->exited) {
      sprite->color.a = 1.0f;
      if (data->hoverText) {
        entity_destroy(data->hoverText);
        data->hoverText = NULL;
      }
    }


    // if clicked on
    if (mbox->left.pressed) {
      // execute different things based on button type
      switch (data->type) {

      // build button
      case BUTTON_BUILD:
      {
        comp_UI_button_enterBuildMode(self);
        if (self->owner->space->game->config.tutorial) {
          if (!data->firstBuildClick) {
            createFirstTutorialPartTwo(self->owner->space);
            data->firstBuildClick = true;
          }
        }
        break;
      }

      // cancel button 
      case BUTTON_CANCEL:
        comp_UI_button_cancelBuildMode(self);
        break;

      case BUTTON_BUILDLOBBY:
        UI_button_createGhostRooms(self, ROOMTYPE_LOBBY);

        if (self->owner->space->game->config.tutorial) {
          if (!playerData->lobbyClicked) {
            createSecondTutorial(self->owner->space);
            playerData->lobbyClicked = true;
          }
        }

        break;

      case BUTTON_BUILDCLASS:
        UI_button_createGhostRooms(self, ROOMTYPE_CLASS);
        break;

      case BUTTON_BUILDLIBRARY:
        UI_button_createGhostRooms(self, ROOMTYPE_LIBRARY);
        break;

      case BUTTON_BUILDTEAMSPACE:
        UI_button_createGhostRooms(self, ROOMTYPE_TEAMSPACE);
        break;

      case BUTTON_BUILDCAFETERIA:
        UI_button_createGhostRooms(self, ROOMTYPE_CAFETERIA);
        break;

      case BUTTON_BUILDSTORE:
        UI_button_createGhostRooms(self, ROOMTYPE_STORE);
        break;

      case BUTTON_BUILDOFFICES:
        UI_button_createGhostRooms(self, ROOMTYPE_OFFICES);
        break;

      case BUTTON_BUILDAUDITORIUM:
        UI_button_createGhostRooms(self, ROOMTYPE_AUDITORIUM);
        break;

      case BUTTON_BUILDTUTORING:
        UI_button_createGhostRooms(self, ROOMTYPE_TUTORING);
        break;

      case BUTTON_BUILDIT:
        UI_button_createGhostRooms(self, ROOMTYPE_IT);
        break;

      case BUTTON_BUILDRECREATION:
        UI_button_createGhostRooms(self, ROOMTYPE_RECREATION);
        break;

      case BUTTON_BUILDFIGURE:
        UI_button_createGhostRooms(self, ROOMTYPE_FIGURE);
        break;

      case BUTTON_DEFAULT:
        break;

      case BUTTON_GPA_INCREMENT:
        if (schoolData->minGpa >= (float)4.0)
          schoolData->minGpa = (float)4.0;
        else
          schoolData->minGpa += (float)0.2;
        break;

      case BUTTON_GPA_DECREMENT:
        if (schoolData->minGpa <= (float)0.2)
          schoolData->minGpa = (float)0.2;
        else
          schoolData->minGpa -= (float)0.2;
        break;

      case BUTTON_TUITION_INCREMENT:
        schoolData->tuition += 500;
        break;

      case BUTTON_TUITION_DECREMENT:
        if (schoolData->tuition <= 0)
          schoolData->tuition = 500;
        else
         schoolData->tuition -= 500;
        break;

      case BUTTON_ROOM_UPGRADE:
        comp_roomLogic_upgradeRoom(self);
        inspectData->triggered = true;
        break;

      case BUTTON_PAUSE:
        comp_timeManager_pause(self);
        break;

      case BUTTON_SPEED:
        comp_timeManager_changeSpeed(self);
        break;
        
      default:
        break;
      }
    }
  }
}


// this is derping out the FIRST time build mode is activated for some weird reason
static void panDown_update(ACTION *action, double dt) {
  COMPONENT *self = (COMPONENT *)(action->data);
  CDATA_UI_BUTTON *data = (CDATA_UI_BUTTON *)self->data;
  SPACE *mg = game_getSpace(self->owner->space->game, "mg");
  SPACE *ui = game_getSpace(self->owner->space->game, "ui");
  COMPONENT *playerLogic = entity_getComponent(space_getEntity(ui, "player"), COMP_PLAYERLOGIC);

  playerLogic_setCamVerticalPos(playerLogic, data->startY + action_getEase(action, EASING_CIRCULAR_OUT) * (BUILDENDPOS - data->startY ));
}

static void zoomOut_update(ACTION *action, double dt) {
  COMPONENT *self = (COMPONENT *)(action->data);
  CDATA_UI_BUTTON *data = (CDATA_UI_BUTTON *)self->data;
  SPACE *mg = game_getSpace(self->owner->space->game, "mg");
  SPACE *ui = game_getSpace(self->owner->space->game, "ui");
  COMPONENT *playerLogic = entity_getComponent(space_getEntity(ui, "player"), COMP_PLAYERLOGIC);

  playerLogic_setZoom(playerLogic, data->startZoom + action_getEase(action, EASING_CIRCULAR_OUT) * (0.75f - data->startZoom));
}

void comp_UI_button_panDown(COMPONENT *self) {
  SPACE *ui = game_getSpace(self->owner->space->game, "ui");
  SPACE *mg = game_getSpace(self->owner->space->game, "mg");
  ENTITY *player = space_getEntity(ui, "player");
  CDATA_PLAYERLOGIC *playerData = (CDATA_PLAYERLOGIC *)entity_getComponentData(player, COMP_PLAYERLOGIC);
  CDATA_UI_BUTTON *data = (CDATA_UI_BUTTON *)self->data;
  COMPONENT *playerLogic = entity_getComponent(space_getEntity(ui, "player"), COMP_PLAYERLOGIC);

  al_clear(&data->actions);

  data->startZoom = mg->systems.camera.transform.scale.x;
  data->startY = mg->systems.camera.transform.translation.y;
  playerData->yPan = true;

  
  al_pushBack(&data->actions, (ACTION *)action_create(self, panDown_update, NULL, NULL, false, 0.4f));
  al_pushBack(&data->actions, (ACTION *)action_create(self, zoomOut_update, NULL, NULL, true, 0.4f));
}


static void panUp_update(ACTION *action, double dt) {
  COMPONENT *self = (COMPONENT *)(action->data);
  CDATA_UI_BUTTON *data = (CDATA_UI_BUTTON *)self->data;
  SPACE *mg = game_getSpace(self->owner->space->game, "mg");
  SPACE *ui = game_getSpace(self->owner->space->game, "ui");
  COMPONENT *playerLogic = entity_getComponent(space_getEntity(ui, "player"), COMP_PLAYERLOGIC);
  float gameHeight = (float)self->owner->space->game->dimensions.height;
  float zoom = mg->systems.camera.transform.scale.x;
  float origin = (0.5f * ((1.0f / zoom) * gameHeight)) - (0.5f * gameHeight) + 180 - 24;

  playerLogic_setCamVerticalPos(playerLogic, data->startY + action_getEase(action, EASING_CIRCULAR_OUT) * (origin - data->startY));
}


static void panUp_onEnd(ACTION *action) {
  COMPONENT *self = (COMPONENT *)(action->data);
  SPACE *ui = game_getSpace(self->owner->space->game, "ui");
  ENTITY *player = space_getEntity(ui, "player");
  CDATA_PLAYERLOGIC *playerData = (CDATA_PLAYERLOGIC *)entity_getComponentData(player, COMP_PLAYERLOGIC);

  playerData->yPan = false;
}

void comp_UI_button_panUp(COMPONENT *self) {
  SPACE *ui = game_getSpace(self->owner->space->game, "ui");
  SPACE *mg = game_getSpace(self->owner->space->game, "mg");
  ENTITY *player = space_getEntity(ui, "player");
  CDATA_PLAYERLOGIC *playerData = (CDATA_PLAYERLOGIC *)entity_getComponentData(player, COMP_PLAYERLOGIC);
  CDATA_UI_BUTTON *data = (CDATA_UI_BUTTON *)self->data;
  COMPONENT *playerLogic = entity_getComponent(space_getEntity(ui, "player"), COMP_PLAYERLOGIC);

  data->startY = mg->systems.camera.transform.translation.y;
  al_clear(&data->actions);
  al_pushBack(&data->actions, action_create(self, panUp_update, NULL, panUp_onEnd, true, 0.4f));
}

void comp_UI_button(COMPONENT *self) {
  CDATA_UI_BUTTON data = { 0 };
  data.type = BUTTON_DEFAULT;
  data.clickable = true;
  al_init(&data.actions);
  COMPONENT_INIT(self, COMP_UI_BUTTON, data);
  component_depend(self, COMP_MOUSEBOX);
  self->events.logicUpdate = comp_UI_buttonUpdate;
  self->events.frameUpdate = comp_UI_buttonFrameUpdate;
  self->events.destroy = comp_UI_destroy;
}

void comp_UI_destroy(COMPONENT *self, void *event) {
  CDATA_UI_BUTTON *data = (CDATA_UI_BUTTON *)self->data;

  al_destroy(&data->actions);
}


void UI_button_createGhostRooms(COMPONENT *self, ROOM_TYPE toBuild) {
  LIST *buildSpaces = list_create();
  int roomSize = comp_schoolLogic_getRoomSize(toBuild);
  SPACE *mg = game_getSpace(self->owner->space->game, "mg");
  LIST_NODE *pNode;
  SPACE *simSpace = game_getSpace(self->owner->space->game, "sim");
  ENTITY *gameManager = space_getEntity(simSpace, "gameManager");
  CDATA_SCHOOLLOGIC *schoolLogic = (CDATA_SCHOOLLOGIC *)entity_getComponentData(gameManager, COMP_SCHOOLLOGIC);
  float squareSize = 80.0f;

  UI_button_destroyGhostRooms(self);
  comp_schoolLogic_findBuildSpots(self, toBuild, roomSize, buildSpaces);
  pNode = buildSpaces->first;
  sound_playSound(&self->owner->space->game->systems.sound, "confirm");

  while (pNode) {
    ENTITY *created;
    LIST_NODE *next;
    CDATA_GHOSTROOMLOGIC *gData;
    CDATA_SPRITE *sprite;
    POINT *data = (POINT *)pNode->data;
    LONG x = data->x;
    LONG y = data->y;
    float top = (3 - y) * squareSize;
    float left = (x - 8) * squareSize;
    VEC3 middle;
    middle.y = top - squareSize / 2.0f;
    middle.z = 0;
      
    switch (roomSize) {
    case (1):
      middle.x = left + squareSize / 2.0f;
      break;
    case (2):
      middle.x = left + squareSize;
      break;
    case (3):
      middle.x = left + squareSize * 1.5f;
      break;
    }

    created = space_addEntityAtPosition(mg, arch_ghostRoom, "ghostRoom", &middle);
    gData = (CDATA_GHOSTROOMLOGIC *)entity_getComponentData(created, COMP_GHOSTROOMLOGIC);
    sprite = (CDATA_SPRITE *)entity_getComponentData(created, COMP_SPRITE);
    switch (toBuild) {
      case ROOMTYPE_LOBBY:
        if(schoolLogic->rooms.coord[2][7] == NULL)
          sprite->source = "rooms/lobby1";
        else if(schoolLogic->rooms.coord[1][7] == NULL)
          sprite->source = "rooms/lobby2";
        else
          sprite->source = "rooms/lobby3";
        break;
    case ROOMTYPE_CLASS:
      sprite->source = "rooms/class";
      break;
    case ROOMTYPE_LIBRARY:
      sprite->source = "rooms/library";
      break;
    case ROOMTYPE_TEAMSPACE:
      sprite->source = "rooms/teamspace";
      break;
    case ROOMTYPE_CAFETERIA:
      sprite->source = "rooms/cafeteria";
      break;
    case ROOMTYPE_STORE:
      sprite->source = "rooms/store";
      break;
    case ROOMTYPE_OFFICES:
      sprite->source = "rooms/offices";
      break;
    case ROOMTYPE_AUDITORIUM:
      sprite->source = "rooms/auditorium";
      break;
    case ROOMTYPE_TUTORING:
      sprite->source = "rooms/tutoring";
      break;
    case ROOMTYPE_IT:
      sprite->source = "rooms/it";
      break;
    case ROOMTYPE_RECREATION:
      sprite->source = "rooms/recreation";
      break;
    case ROOMTYPE_FIGURE:
      sprite->source = "rooms/figure";
      break;
    case ROOMTYPE_POTTERY:
      sprite->source = "rooms/library";
      break;

    default:
      break;
    }
    gData->point.x = x;
    gData->point.y = y;
    gData->roomSize = roomSize;
    gData->roomType = toBuild;
    sprite->color.a = 0.75f;
    next = pNode->next;
    pNode = next;
  }
  UI_button_deleteList(buildSpaces);
}

void __UI_button_cancelBuildMode(COMPONENT *self) {
  LIST_NODE *node;
  LIST *buttons = list_create();
  SPACE *ui = game_getSpace(self->owner->space->game, "ui");
  ENTITY *player = space_getEntity(ui, "player");
  CDATA_PLAYERLOGIC *playerData = (CDATA_PLAYERLOGIC *)entity_getComponentData(player, COMP_PLAYERLOGIC);
  CDATA_UI_BUTTON *data = (CDATA_UI_BUTTON *)self->data;


  // destroying all room buttons
  space_getAllEntities(self->owner->space, "buildButton", buttons);
  node = buttons->first;
  while (node) {
    entity_destroy((ENTITY *)node->data);
    node = node->next;
  }
  list_destroy(buttons);
}

void UI_button_destroyGhostRooms(COMPONENT *self) {
  LIST *ghostrooms = list_create();
  SPACE *mg = game_getSpace(self->owner->space->game, "mg");
  LIST_NODE *node;

  // detroying all ghostrooms
  space_getAllEntities(mg, "ghostRoom", ghostrooms);
  node = ghostrooms->first;
  while (node) {
    entity_destroy((ENTITY *)node->data);
    node = node->next;
  }
  list_destroy(ghostrooms);
}

void UI_button_deleteList(LIST *buildSpaces) {
  LIST_NODE *pNode = buildSpaces->first;
  while (pNode) {
    free(pNode->data);
    pNode = pNode->next;
  }
  list_destroy(buildSpaces);
}

void UI_button_createRoomButton(COMPONENT *self, BUTTON_TYPE type, VEC3 *position, VEC4 *color, char *name) {
  ENTITY *newButton = 0;
  CDATA_UI_BUTTON *buttonData;
  VEC3 textPos;
  SPACE *sim = game_getSpace(self->owner->space->game, "sim");
  CDATA_SCHOOLLOGIC *schoolData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(space_getEntity(sim, "gameManager"), COMP_SCHOOLLOGIC);
  CDATA_SPRITE *sprite;

  newButton = space_addEntityAtPosition(self->owner->space, arch_uibuild, "buildButton", position);
  buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(newButton, COMP_UI_BUTTON);
  vec3_set(&textPos, 0.0f, 0.0f, 0.0f);
  buttonData->text = genericText_create(self->owner->space, &textPos, NULL, "fonts/gothic/12", name, color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
  entity_attach(buttonData->text, newButton);
  buttonData->type = type;
  sprite = (CDATA_SPRITE *)entity_getComponentData(newButton, COMP_SPRITE);

  UI_button_updateBuildButtons(self->owner->space);

}

void UI_button_createManagementButton(COMPONENT *self, BUTTON_TYPE type, VEC3 *position, VEC4 *color, char *name) {
  ENTITY *newButton = 0;
  CDATA_UI_BUTTON *buttonData;
  ENTITY *text;
  VEC3 textPos;

  newButton = space_addEntityAtPosition(self->owner->space, arch_uibuild, "managementButton", position);
  buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(newButton, COMP_UI_BUTTON);
  vec3_set(&textPos, 0.0f, 0.0f, 0.0f);
  text = genericText_create(self->owner->space, &textPos, NULL, "fonts/gothic/12", name, color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
  entity_attach(text, newButton);
  buttonData->type = type;
}

void UI_button_createUpgradeButton(COMPONENT *self, BUTTON_TYPE type, VEC3 *position, VEC4 *color, char *name) {
  ENTITY *newButton = 0;
  CDATA_UI_BUTTON *buttonData;
  ENTITY *text;
  VEC3 textPos;
  CDATA_SPRITE *sprite;

  newButton = space_addEntityAtPosition(self->owner->space, arch_uibuild, "upgradeButton", position);
  sprite = entity_getComponentData(newButton, COMP_SPRITE);
  sprite->source = "ui/upgrade";
  buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(newButton, COMP_UI_BUTTON);
  vec3_set(&textPos, 0.0f, 0.0f, 0.0f);
  text = genericText_create(self->owner->space, &textPos, NULL, "fonts/gothic/12", name, color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
  entity_attach(text, newButton);
  buttonData->type = type;
}

void UI_button_updateBuildButtons(SPACE *ui) {
  SPACE *sim = game_getSpace(ui->game, "sim");
  CDATA_SCHOOLLOGIC *schoolData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(space_getEntity(sim, "gameManager"), COMP_SCHOOLLOGIC);
  LIST *buildButtons = list_create();
  LIST_NODE *node;
  CDATA_UI_BUTTON *buttonData;

  // loop through all build buttons and update their active or non active ness
  space_getAllEntities(ui, "buildButton", buildButtons);
  node = buildButtons->first;

  while (node) {
    buttonData = (CDATA_UI_BUTTON *)entity_getComponentData((ENTITY *)node->data, COMP_UI_BUTTON);
    // if still locked
    if (schoolData->roomFlag[buttonData->type] == 0) {
      CDATA_MOUSEBOX *buttonBox = (CDATA_MOUSEBOX *)entity_getComponentData((ENTITY *)node->data, COMP_MOUSEBOX);
      CDATA_SPRITE *buttonSprite = (CDATA_SPRITE *)entity_getComponentData((ENTITY *)node->data, COMP_SPRITE);
      buttonData->clickable = false;
      buttonSprite->color.r = 0.2f;
      buttonSprite->color.g = 0.2f;
      buttonSprite->color.b = 0.2f;
    }
    
    // if not enough money
    else if (schoolData->money < (ROOM_TYPE)comp_roomLogic_getRoomCost(buttonData->type)) {
      CDATA_MOUSEBOX *buttonBox = (CDATA_MOUSEBOX *)entity_getComponentData((ENTITY *)node->data, COMP_MOUSEBOX);
      CDATA_SPRITE *buttonSprite = (CDATA_SPRITE *)entity_getComponentData((ENTITY *)node->data, COMP_SPRITE);
      buttonData->clickable = false;
      buttonData->unlocked = true;
      buttonSprite->color.r = 0.5f;
      buttonSprite->color.g = 0.5f;
      buttonSprite->color.b = 0.5f;
    }
    
    else {
      CDATA_MOUSEBOX *buttonBox = (CDATA_MOUSEBOX *)entity_getComponentData(node->data, COMP_MOUSEBOX);
      CDATA_SPRITE *buttonSprite = (CDATA_SPRITE *)entity_getComponentData((ENTITY *)node->data, COMP_SPRITE);
      buttonData->clickable = true;
      buttonData->unlocked = true;
      buttonSprite->color.r = 1.0f;
      buttonSprite->color.g = 1.0f;
      buttonSprite->color.b = 1.0f;
    }

    node = node->next;
  }
  list_destroy(buildButtons);
}

void UI_button_updateUpgradeButton(SPACE *ui) {
  /*SPACE *sim = game_getSpace(ui->game, "sim");
  ENTITY *inspectionScreen = space_getEntity(ui, "inspection_screen");
  CDATA_INSPECTIONSCREEN *inspectData = (CDATA_INSPECTIONSCREEN *)entity_getComponentData(space_getEntity(ui, "inspection_screen"), COMP_INSPECTIONSCREENLOGIC); 
  CDATA_SCHOOLLOGIC *schoolData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(space_getEntity(sim, "gameManager"), COMP_SCHOOLLOGIC);
  CDATA_ROOMLOGIC *roomData = (CDATA_ROOMLOGIC *)entity_getComponentData(schoolData->rooms.coord[inspectData->posY][inspectData->posX], COMP_ROOMLOGIC);

  if(schoolData->money < comp_roomLogic_getRoomUpgradeCost(roomData->type)) {
    CDATA_MOUSEBOX *buttonBox = (CDATA_MOUSEBOX *)entity_getComponentData(space_getEntity(ui, "upgradeButton"), COMP_MOUSEBOX);
    CDATA_SPRITE *buttonSprite = (CDATA_SPRITE *)entity_getComponentData(space_getEntity(ui, "upgradeButton"), COMP_SPRITE);
    buttonBox->active = false;
    buttonSprite->color.r = 0.4f;
    buttonSprite->color.g = 0.4f;
    buttonSprite->color.b = 0.4f;
  }
  else {
    CDATA_MOUSEBOX *buttonBox = (CDATA_MOUSEBOX *)entity_getComponentData(space_getEntity(ui, "upgradeButton"), COMP_MOUSEBOX);
    buttonBox->active = true;
  }*/
}

void comp_UI_button_enterBuildMode(COMPONENT *buildButton) {
  VEC3 position;
  CDATA_UI_BUTTON *data = (CDATA_UI_BUTTON *)buildButton->data;
  comp_UI_button_panDown(buildButton);
  sound_playSound(&buildButton->owner->space->game->systems.sound, "confirm");

  // CREATE LOBBY BUTTON
  vec3_set(&position, -261, -116, 0);
  UI_button_createRoomButton(buildButton, BUTTON_BUILDLOBBY, &position, &colors[C_WHITE_LIGHT], "Lobby");

  // CREATE CLASS BUTTON
  vec3_set(&position, -157, -116, 0);
  UI_button_createRoomButton(buildButton, BUTTON_BUILDCLASS, &position, &colors[C_WHITE_LIGHT], "Classroom");

  // CREATE LIBRARY BUTTON
  vec3_set(&position, -53, -116, 0);
  UI_button_createRoomButton(buildButton, BUTTON_BUILDLIBRARY, &position, &colors[C_WHITE_LIGHT], "Library");
 
  // CREATE TEAMSPACE BUTTON
  vec3_set(&position, 51, -116, 0);
  UI_button_createRoomButton(buildButton, BUTTON_BUILDTEAMSPACE, &position, &colors[C_WHITE_LIGHT], "Teammspace");

  // CREATE OFFICES BUTTON
  vec3_set(&position, 155, -116, 0);
  UI_button_createRoomButton(buildButton, BUTTON_BUILDOFFICES, &position, &colors[C_WHITE_LIGHT], "Offices");

  // CREATE CAFETERIA BUTTON
  vec3_set(&position, 259, -116, 0);
  UI_button_createRoomButton(buildButton, BUTTON_BUILDCAFETERIA, &position, &colors[C_WHITE_LIGHT], "Cafeteria");

  // CREATE STORE BUTTON
  vec3_set(&position, -261, -158, 0);
  UI_button_createRoomButton(buildButton, BUTTON_BUILDSTORE, &position, &colors[C_WHITE_LIGHT], "Store");

  // CREATE AUDITORIUM BUTTON
  vec3_set(&position, -157, -158, 0);
  UI_button_createRoomButton(buildButton, BUTTON_BUILDAUDITORIUM, &position, &colors[C_WHITE_LIGHT], "Auditorium");

  // CREATE TUTORING BUTTON
  vec3_set(&position, -53, -158, 0);
  UI_button_createRoomButton(buildButton, BUTTON_BUILDTUTORING, &position, &colors[C_WHITE_LIGHT], "Tutoring");

  // CREATE WIFI BUTTON
  vec3_set(&position, 51, -158, 0);
  UI_button_createRoomButton(buildButton, BUTTON_BUILDIT, &position, &colors[C_WHITE_LIGHT], "IT");

  // CREATE CAFETERIA BUTTON
  vec3_set(&position, 155, -158, 0);
  UI_button_createRoomButton(buildButton, BUTTON_BUILDRECREATION, &position, &colors[C_WHITE_LIGHT], "Recreation");

  // CREATE Figure BUTTON
  vec3_set(&position, 259, -158, 0);
  UI_button_createRoomButton(buildButton, BUTTON_BUILDFIGURE, &position, &colors[C_WHITE_LIGHT], "Figure Drawing");

  data->type = BUTTON_CANCEL;
}

void comp_UI_button_cancelBuildMode(COMPONENT *buildButton) {
  CDATA_UI_BUTTON *data = (CDATA_UI_BUTTON *)buildButton->data;
  if (data->type == BUTTON_CANCEL) {
    data->type = BUTTON_BUILD;
    comp_UI_button_panUp(buildButton);
    __UI_button_cancelBuildMode(buildButton);
    UI_button_destroyGhostRooms(buildButton);
    sound_playSound(&buildButton->owner->space->game->systems.sound, "negative");
  }
}

void comp_UI_button_toggleBuildMode(COMPONENT *buildButton) {
  CDATA_UI_BUTTON *data = (CDATA_UI_BUTTON *)buildButton->data;

  if (data->type == BUTTON_CANCEL) {
    comp_UI_button_cancelBuildMode(buildButton);
  }

  else if (data->type == BUTTON_BUILD) {
    comp_UI_button_enterBuildMode(buildButton);
  }

}
