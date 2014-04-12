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
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  POINT mousePos;
  CDATA_TRANSFORM *cursorSpriteTransform = (CDATA_TRANSFORM *)entity_getComponentData(space_getEntity(game_getSpace(self->owner->space->game, "cursor"), "cursorSprite"), COMP_TRANSFORM);

  space_mouseToWorld(self->owner->space, &input->mouse.position, &mousePos);
  trans->translation.x = (float)mousePos.x;
  trans->translation.y = (float)mousePos.y;
  cursorSpriteTransform->translation.x = trans->translation.x;
  cursorSpriteTransform->translation.y = trans->translation.y;
}


void comp_cursorLogic(COMPONENT *self) {
  COMPONENT_INIT_NULL(self, COMP_CURSORLOGIC);
  component_depend(self, COMP_TRANSFORM);
  component_depend(self, COMP_SPRITE);
  self->events.logicUpdate = comp_cursorLogic_logicUpdate;
}

void createGhostRooms(COMPONENT *self, LIST *spots, int roomSize, ROOM_TYPE toBuild) {
  SPACE *mg = game_getSpace(self->owner->space->game, "mg");
  LIST_NODE *pNode = spots->first;
  SPACE *simSpace = game_getSpace(self->owner->space->game, "sim");
  ENTITY *gameManager = space_getEntity(simSpace, "gameManager");
  CDATA_SCHOOLLOGIC *schoolLogic = (CDATA_SCHOOLLOGIC *)entity_getComponentData(gameManager, COMP_SCHOOLLOGIC);
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
        if(schoolLogic->rooms.coord[1][7] == NULL)
          sprite->source = "rooms/lobby1";
        else if(schoolLogic->rooms.coord[0][7] == NULL)
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

}

