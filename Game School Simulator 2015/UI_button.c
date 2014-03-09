/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "UI_button.h"
#include "mousebox.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/generictext.h"
#include "../Nekoengine/spritetext.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/entity.h"
#include "../NekoEngine/sprite.h"
#include "ghostroom.h"
#include "playerlogic.h"
#include "roomlogic.h"
#include "UI_build.h"
#include "schoollogic.h"
#include "managescreen.h"
#include "ghostroomlogic.h"
#include "inspectionscreenlogic.h"

#define BUILDENDPOS 120.0f

void comp_UI_buttonUpdate(COMPONENT *self, void *event) {
  CDATA_UI_BUTTON *data = (CDATA_UI_BUTTON *)self->data;
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  VEC2 dimensions = { 40.0f, 20.0f };
  VEC3 position = { 10, 10, 0 };
  VEC4 color = { 0, 0, 1, 1 };
  SPACE *simSpace = game_getSpace(self->owner->space->game, "sim");
  SPACE *ui = game_getSpace(self->owner->space->game, "ui");
  ENTITY *player = space_getEntity(ui, "player");
  ENTITY *schoolData = space_getEntity(simSpace, "gameManager");
  CDATA_SCHOOLLOGIC *managementData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(schoolData, COMP_SCHOOLLOGIC);
  CDATA_PLAYERLOGIC *playerData = (CDATA_PLAYERLOGIC *)entity_getComponentData(player, COMP_PLAYERLOGIC);
  CDATA_UI_BUTTON *comData = (CDATA_UI_BUTTON *)self->data;
  CDATA_INSPECTIONSCREEN *inspectData = (CDATA_INSPECTIONSCREEN *)entity_getComponentData(space_getEntity(ui, "inspection_screen"), COMP_INSPECTIONSCREENLOGIC); 
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;

  al_update(&data->actions, updateEvent->dt);

  if (mbox->active) {
    if (mbox->over) {
      sprite->color.r = min(sprite->color.r + 0.05f, 1);
      sprite->color.b = max(sprite->color.b - 0.05f, 1);
      sprite->color.g = max(sprite->color.g - 0.05f, 0);
    }
    else {
      sprite->color.r = max(sprite->color.r - 0.05f, 0);
      sprite->color.b = min(sprite->color.b + 0.05f, 1);
      sprite->color.g = min(sprite->color.g + 0.05f, 1);
    }

    // if clicked on
    if (mbox->left.pressed) {
      // execute different things based on button type
      switch (comData->type) {

      // build button
      case BUTTON_BUILD:
      {
        VEC3 position;
        VEC4 color;
        comp_UI_button_panDown(self);
      
        // CREATE LOBBY BUTTON
        vec3_set(&position, -300, -160, 0);
        UI_button_createRoomButton(self, BUTTON_BUILDLOBBY, &position, &color, "Lobby");

        // CREATE CLASS BUTTON
        vec3_set(&position, -249, -160, 0);
        UI_button_createRoomButton(self, BUTTON_BUILDCLASS, &position, &color, "Classroom");

        // CREATE LIBRARY BUTTON
        vec3_set(&position, -198, -160, 0);
        UI_button_createRoomButton(self, BUTTON_BUILDLIBRARY, &position, &color, "Library");
 
        // CREATE TEAMSPACE BUTTON
        vec3_set(&position, -147, -160, 0);
        UI_button_createRoomButton(self, BUTTON_BUILDTEAMSPACE, &position, &color, "Teammspace");

        // CREATE CAFETERIA BUTTON
        vec3_set(&position, -96, -160, 0);
        UI_button_createRoomButton(self, BUTTON_BUILDCAFETERIA, &position, &color, "Cafeteria");

        // CREATE STORE BUTTON
        vec3_set(&position, -45, -160, 0);
        UI_button_createRoomButton(self, BUTTON_BUILDSTORE, &position, &color, "Store");

        // CREATE OFFICES BUTTON
        vec3_set(&position, 45, -160, 0);
        UI_button_createRoomButton(self, BUTTON_BUILDOFFICES, &position, &color, "Offices");

        // CREATE AUDITORIUM BUTTON
        vec3_set(&position, 96, -160, 0);
        UI_button_createRoomButton(self, BUTTON_BUILDAUDITORIUM, &position, &color, "Auditorium");

        // CREATE TUTORING BUTTON
        vec3_set(&position, 147, -160, 0);
        UI_button_createRoomButton(self, BUTTON_BUILDTUTORING, &position, &color, "Tutoring");

        // CREATE WIFI BUTTON
        vec3_set(&position, 198, -160, 0);
        UI_button_createRoomButton(self, BUTTON_BUILDWIFI, &position, &color, "Wifi");

        // CREATE CAFETERIA BUTTON
        vec3_set(&position, 249, -160, 0);
        UI_button_createRoomButton(self, BUTTON_BUILDRECREATION, &position, &color, "Recreation");

        // CREATE Figure BUTTON
        vec3_set(&position, 300, -160, 0);
        UI_button_createRoomButton(self, BUTTON_BUILDFIGURE, &position, &color, "Figure");

        comData->type = BUTTON_CANCEL;
        break;
      }

      // cancel button 
      case BUTTON_CANCEL:
        comData->type = BUTTON_BUILD;
        //comp_UI_button_panUp(self);
        {
          SPACE *ui = game_getSpace(self->owner->space->game, "ui");
          SPACE *mg = game_getSpace(self->owner->space->game, "mg");
          ENTITY *player = space_getEntity(ui, "player");
          CDATA_PLAYERLOGIC *playerData = (CDATA_PLAYERLOGIC *)entity_getComponentData(player, COMP_PLAYERLOGIC);
      
          playerData->yPan = false;
        }
        comp_UI_button_cancelBuildMode(self);
        UI_button_destroyGhostRooms(self);
        break;

      case BUTTON_BUILDLOBBY:
        UI_button_createGhostRooms(self, ROOMTYPE_LOBBY);
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

      case BUTTON_BUILDWIFI:
        UI_button_createGhostRooms(self, ROOMTYPE_WIFI);
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
        if (managementData->minGpa >= (float)4.0)
          managementData->minGpa = (float)4.0;
        else
          managementData->minGpa += (float)0.2;
        break;

      case BUTTON_GPA_DECREMENT:
        if (managementData->minGpa <= (float)0.2)
          managementData->minGpa = (float)0.2;
        else
          managementData->minGpa -= (float)0.2;
        break;

      case BUTTON_TUITION_INCREMENT:
        managementData->tuition += 500;
        break;

      case BUTTON_TUITION_DECREMENT:
        if (managementData->tuition <= 0)
          managementData->tuition = 500;
        else
         managementData->tuition -= 500;
        break;

      case BUTTON_ROOM_UPGRADE:
        comp_roomLogic_upgradeRoom(self);
        inspectData->triggered = true;
        break;

      case BUTTON_NEWGAME:
        {
        SPACE *menu = game_getSpace(self->owner->space->game, "menu");
        space_destroy(menu);
        }
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

  data->startZoom = mg->systems.camera.transform.scale.x;
  data->startY = mg->systems.camera.transform.translation.y;
  playerData->yPan = true;

  al_pushFront(&data->actions, action_create(self, panDown_update, NULL, NULL, false, 0.4f));
  al_pushFront(&data->actions, action_create(self, zoomOut_update, NULL, NULL, false, 0.4f));
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

  al_pushFront(&data->actions, action_create(self, panUp_update, NULL, panUp_onEnd, false, 0.4f));
}

void comp_UI_button(COMPONENT *self) {
  CDATA_UI_BUTTON data = { 0 };
  data.type = BUTTON_DEFAULT;
  al_init(&data.actions);
  COMPONENT_INIT(self, COMP_UI_BUTTON, data);
  component_depend(self, COMP_MOUSEBOX);
  self->events.logicUpdate = comp_UI_buttonUpdate;
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
  float squareSize = 80.0f;

  comp_schoolLogic_findBuildSpots(self, toBuild, roomSize, buildSpaces);
  pNode = buildSpaces->first;

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
        sprite->source = "rooms/frontdoor";
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
    case ROOMTYPE_WIFI:
      sprite->source = "rooms/wifi";
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

void comp_UI_button_cancelBuildMode(COMPONENT *self) {
  LIST_NODE *node;
  LIST *buttons = list_create();
  SPACE *ui = game_getSpace(self->owner->space->game, "ui");
  ENTITY *player = space_getEntity(ui, "player");
  CDATA_PLAYERLOGIC *playerData = (CDATA_PLAYERLOGIC *)entity_getComponentData(player, COMP_PLAYERLOGIC);
  CDATA_UI_BUTTON *comData = (CDATA_UI_BUTTON *)self->data;

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
  ENTITY *text;
  VEC3 textPos;
  SPACE *sim = game_getSpace(self->owner->space->game, "sim");
  CDATA_SCHOOLLOGIC *schoolData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(space_getEntity(sim, "gameManager"), COMP_SCHOOLLOGIC);
  CDATA_SPRITE *sprite;

  newButton = space_addEntityAtPosition(self->owner->space, arch_uibuild, "buildButton", position);
  buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(newButton, COMP_UI_BUTTON);
  vec3_set(&textPos, 0.0f, 0.0f, 0.0f);
  text = genericText_create(self->owner->space, &textPos, NULL, "fonts/gothic/12", name, color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
  entity_attach(text, newButton);
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

  newButton = space_addEntityAtPosition(self->owner->space, arch_uibuild, "upgradeButton", position);
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
    buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(node->data, COMP_UI_BUTTON);
    if (schoolData->money < comp_roomLogic_getRoomCost(buttonData->type)) {
      CDATA_MOUSEBOX *buttonBox = entity_getComponentData(node->data, COMP_MOUSEBOX);
      CDATA_SPRITE *buttonSprite = entity_getComponentData(node->data, COMP_SPRITE);
      buttonBox->active = false;
      buttonSprite->color.r = 0.4f;
      buttonSprite->color.g = 0.4f;
      buttonSprite->color.b = 0.4f;
    }
    else {
      CDATA_MOUSEBOX *buttonBox = entity_getComponentData(node->data, COMP_MOUSEBOX);
      buttonBox->active = true;
    }

    node = node->next;
  }
  list_destroy(buildButtons);
}
