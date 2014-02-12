/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "cursorlogic.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/sprite.h"
#include "../NekoEngine/entity.h"
#include "../NekoEngine/sound.h"
#include <math.h>
#include "ghostroomlogic.h"
#include "ghostroom.h"

#define GROUND_HEIGHT 24

void comp_cursorLogic_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  CDATA_CURSORLOGIC *data = (CDATA_CURSORLOGIC *)entity_getComponentData(self->owner, COMP_CURSORLOGIC);
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  POINT mousePos;
  SPACE *mgSpace = game_getSpace(self->owner->space->game, "mg");
  SPACE *uiSpace = game_getSpace(self->owner->space->game, "ui");
  ENTITY *player = space_getEntity(uiSpace, "player");
  CDATA_PLAYERLOGIC *playerData = (CDATA_PLAYERLOGIC *)entity_getComponentData(player, COMP_PLAYERLOGIC);
  int roomSize;
  ROOM_TYPE toBuild;
  LIST *buildSpaces;
  CDATA_TRANSFORM *cursorSpriteTransform = (CDATA_TRANSFORM *)entity_getComponentData(space_getEntity(game_getSpace(self->owner->space->game, "cursor"), "cursorSprite"), COMP_TRANSFORM);

  space_mouseToWorld(self->owner->space, &input->mouse.position, &mousePos);
  trans->translation.x = (float)mousePos.x;
  trans->translation.y = (float)mousePos.y;
  cursorSpriteTransform->translation.x = trans->translation.x;
  cursorSpriteTransform->translation.y = trans->translation.y;


  if (playerData->gameMode == BUILD) {
    if (data->gameMode != BUILD) {
      toBuild = playerData->roomType;
      roomSize = comp_schoolLogic_getRoomSize(toBuild);
      buildSpaces = comp_schoolLogic_findBuildSpots(self, toBuild, roomSize);
      if (buildSpaces == NULL) {
        playerData->gameMode = DEFAULT;
        data->gameMode = DEFAULT;
      }
      else {
        createGhostRooms(self, buildSpaces, roomSize, toBuild);
        data->gameMode = BUILD;
      }
    }
  }
}


void comp_cursorLogic(COMPONENT *self) {
  CDATA_CURSORLOGIC data = { 0 };
  COMPONENT_INIT(self, COMP_CURSORLOGIC, data);
  component_depend(self, COMP_TRANSFORM);
  component_depend(self, COMP_SPRITE);
  self->events.logicUpdate = comp_cursorLogic_logicUpdate;
}

// memory leaaaak please fix! remember to free eduardo's list
void createGhostRooms(COMPONENT *self, LIST *spots, int roomSize, ROOM_TYPE toBuild) {
  SPACE *mg = game_getSpace(self->owner->space->game, "mg");
  LIST_NODE *pNode = spots->first;
  float squareSize = 80.0f;

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
      sprite->source = "rooms/template2";
      break;
    case ROOMTYPE_CLASS:
      sprite->source = "rooms/template";
      break;
    case ROOMTYPE_LIBRARY:
      sprite->source = "rooms/template2";
      break;
    case ROOMTYPE_TEAMSPACE:
      sprite->source = "rooms/template3";
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
    //list_remove_free(spots, pNode);
    pNode = next;
  }
  list_destroy(spots);
}

