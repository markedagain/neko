/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "UI_button.h"
#include "mousebox.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/generictext.h"
#include "../Nekoengine/spritetext.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/entity.h"
#include "../NekoEngine/sprite.h"
#include <math.h>
#include <stdio.h>
#include "ghostroom.h"
#include "playerlogic.h"
#include "roomlogic.h"
#include "UI_build.h"
#include "schoollogic.h"
#include "managescreen.h"
#include "ghostroomlogic.h"

void comp_UI_buttonUpdate(COMPONENT *self, void *event) {
  CDATA_UI_BUTTON *data = (CDATA_UI_BUTTON *)self->data;
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  VEC2 dimensions = { 40.0f, 20.0f };
  VEC3 position = { 10, 10, 0 };
  VEC4 color = { 0, 0, 1, 1 };
  SPACE *ui = game_getSpace(self->owner->space->game, "ui");
  ENTITY *player = space_getEntity(ui, "player");
  ENTITY *camera = 0;
  CDATA_PLAYERLOGIC *playerData = (CDATA_PLAYERLOGIC *)entity_getComponentData(player, COMP_PLAYERLOGIC);
  CDATA_UI_BUTTON *comData = (CDATA_UI_BUTTON *)self->data;

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
    VEC3 position;
    ENTITY *newButton;
    CDATA_UI_BUTTON *buttonData;
    ENTITY *text;
    VEC4 color;

    pan_reset(self);
    zoom_reset(self);
    playerData->yPan = true;
    pan(self, 0.0f, -40.0f, NULL);

    // execute different things based on button type
    switch (comData->type) {

    // build button
    case BUTTON_BUILD:
      // CREATE LOBBY BUTTON
      vec3_set(&position, -250, -160, 0);
      newButton = space_addEntityAtPosition(self->owner->space, arch_uibuild, "buildButton", &position);
      buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(newButton, COMP_UI_BUTTON);
      vec3_set(&position, 0.0f, 0.0f, 0.0f);
      text = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", "Lobby", &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
      entity_attach(text, newButton);
      buttonData->type = BUTTON_BUILDLOBBY;

      // CREATE CLASS BUTTON
      vec3_set(&position, -190, -160, 0);
      newButton = space_addEntityAtPosition(self->owner->space, arch_uibuild, "buildButton", &position);
      buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(newButton, COMP_UI_BUTTON);
      vec3_set(&position, 0.0f, 0.0f, 0.0f);
      text = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", "Class", &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
      entity_attach(text, newButton);
      buttonData->type = BUTTON_BUILDCLASS;

      // CREATE LIBRARY BUTTON
      vec3_set(&position, -130, -160, 0);
      newButton = space_addEntityAtPosition(self->owner->space, arch_uibuild, "buildButton", &position);
      buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(newButton, COMP_UI_BUTTON);
      vec3_set(&position, 0.0f, 0.0f, 0.0f);
      text = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", "Library", &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
      entity_attach(text, newButton);
      buttonData->type = BUTTON_BUILDLIBRARY;
 
      // CREATE TEAMSPACE BUTTON
      vec3_set(&position, -70, -160, 0);
      newButton = space_addEntityAtPosition(self->owner->space, arch_uibuild, "buildButton", &position);
      buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(newButton, COMP_UI_BUTTON);
      vec3_set(&position, 0.0f, 0.0f, 0.0f);
      text = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", "Team", &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
      entity_attach(text, newButton);
      buttonData->type = BUTTON_BUILDTEAMSPACE;

      comData->type = BUTTON_CANCEL;
      break;

    // cancel button 
    case BUTTON_CANCEL:
      /*{
      LIST_NODE *node;
      LIST *buttons = list_create();
      space_getAllEntities(self->owner->space, "buildButton", buttons);
      node = buttons->first;
      while (node) {
        entity_destroy((ENTITY *)node->data);
        node = node->next;
      }

      list_destroy(buttons);*/
      comData->type = BUTTON_BUILD;
      //playerData->yPan = false;
      comp_UI_button_cancelBuildMode(self);
      //}
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

    default:
      break;
    }
  }
 /*
  if (mbox->entered && data->ent3 == NULL) {
    vec3_set(&position, 0, -50, 0);
    data->ent3 = genericSprite_create(ui, &position, NULL, "cursor/build");
  }

  else if (mbox->exited && data->ent3) {
    entity_destroy(data->ent3);
    data->ent3 = NULL;
  }
  */
  /*
  if(mbox->left.pressed && data->ent2 == NULL) {
    vec3_set(&position, 100, 100, 0);
    data->ent2 = genericSprite_create(ui, &position, NULL, "backgrounds/i_love_you");
  }
  else if(mbox->left.pressed && data->ent2) {
    entity_destroy(data->ent2);
    data->ent2 = NULL;
  }
  */
}

void comp_UI_button(COMPONENT *self) {
  CDATA_UI_BUTTON data = { 0 };
  data.type = BUTTON_DEFAULT;
  COMPONENT_INIT(self, COMP_UI_BUTTON, data);
  component_depend(self, COMP_MOUSEBOX);
  self->events.logicUpdate = comp_UI_buttonUpdate;
}


// this doesn't work yet but please make it work
void comp_UI_button_cancelBuildMode(COMPONENT *self) {
  LIST_NODE *node;
  LIST *buttons = list_create();
  SPACE *ui = game_getSpace(self->owner->space->game, "ui");
  ENTITY *player = space_getEntity(ui, "player");
  CDATA_PLAYERLOGIC *playerData = (CDATA_PLAYERLOGIC *)entity_getComponentData(player, COMP_PLAYERLOGIC);
  CDATA_UI_BUTTON *comData = (CDATA_UI_BUTTON *)self->data;
  LIST *ghostrooms = list_create();
  SPACE *mg = game_getSpace(self->owner->space->game, "mg");

  // destroying all room buttons
  space_getAllEntities(self->owner->space, "buildButton", buttons);
  node = buttons->first;
  while (node) {
    entity_destroy((ENTITY *)node->data);
    node = node->next;
  }
  list_destroy(buttons);

  // detroying all ghostrooms
  space_getAllEntities(mg, "ghostRoom", ghostrooms);
  node = ghostrooms->first;
  while (node) {
    entity_destroy((ENTITY *)node->data);
    node = node->next;
  }
  list_destroy(ghostrooms);

  playerData->yPan = false;
}

// just changed this, please check for mem leaks
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

void UI_button_deleteList(LIST *buildSpaces) {
  LIST_NODE *pNode = buildSpaces->first;
  while (pNode) {
    free(pNode->data);
    pNode = pNode->next;
  }
  list_destroy(buildSpaces);
}
