/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "cursorlogic.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/sprite.h"
#include "../NekoEngine/entity.h"
#include "playerlogic.h"
#include <math.h>

#define GROUND_HEIGHT 24

void comp_cursorLogic_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  CDATA_CURSORLOGIC *data = (CDATA_CURSORLOGIC *)entity_getComponentData(self->owner, COMP_CURSORLOGIC);
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  POINT mousePos;
  SPACE *uiSpace = game_getSpace(self->owner->space->game, "ui");
  ENTITY *player = space_getEntity(uiSpace, "player");
  CDATA_PLAYERLOGIC *playerData = (CDATA_PLAYERLOGIC *)entity_getComponentData(player, COMP_PLAYERLOGIC);
  int roomSize;
  ROOM_TYPE toBuild;
  LIST *buildSpaces;

  space_mouseToWorld(self->owner->space, &input->mouse.position, &mousePos);
  trans->translation.x = (float)mousePos.x;
  trans->translation.y = (float)mousePos.y;

  if (playerData->gameMode == BUILD) {
    toBuild = playerData->roomType;
    roomSize = getRoomSize(toBuild);
    buildSpaces = findBuildSpot(toBuild, roomSize);
    findWorldBuildSpots(self, buildSpaces, roomSize);
    snap_sprite(self);
  }
  else {
    free_snaps(self);
  }
}

void findWorldBuildSpots(COMPONENT *self, LIST *buildSpaces, int roomSize) {
  CDATA_CURSORLOGIC *data = (CDATA_CURSORLOGIC *)self->data;
  LIST_NODE *pNode = buildSpaces->first;
  int x;
  int y;
  float left;
  float top;
  float right;
  float bot;
  VEC3 camScale;
  VEC3 screenScaleVec;
  float screenScale;
  MATRIX3 transform = { 0 };
  VEC3 sizeOfSquare = { 80.0f, 80.0f, 0 };
  VEC3 *simPoint;

  camScale.x = self->owner->space->systems.camera.transform.scale.x;
  camScale.y = self->owner->space->systems.camera.transform.scale.y;

  screenScale = (float)self->owner->space->game->innerWindow.width / self->owner->space->game->dimensions.width;
  screenScaleVec.x = screenScale;
  screenScaleVec.y = screenScale;

  matrix3_identity(&transform);
  matrix3_scale(&transform, &camScale);
  matrix3_scale(&transform, &screenScaleVec);

  matrix3_apply_to_vector(&sizeOfSquare, &transform);

  while(pNode) {
    simPoint = (VEC3 *)pNode->data;
    x = (int)simPoint->x;
    y = (int)simPoint->y;

    left = (x - 8) * sizeOfSquare.x;
    right = left + sizeOfSquare.x * roomSize;
    top = (3 - y) * sizeOfSquare.y + GROUND_HEIGHT * screenScale * camScale.y;
    bot = top - sizeOfSquare.y;

    add_snap(self, left, top, right, bot);

    pNode = pNode->next;
  }
}

void comp_cursorLogic(COMPONENT *self) {
  CDATA_CURSORLOGIC data = { 0 };
  data.snaps = list_create();
  COMPONENT_INIT(self, COMP_CURSORLOGIC, data);
  component_depend(self, COMP_TRANSFORM);
  component_depend(self, COMP_SPRITE);
  self->events.logicUpdate = comp_cursorLogic_logicUpdate;
  self->events.destroy = comp_cursorLogic_destroy;
}


// makes the sprite snap to all positions in an array of VEC3s (snaps)
// currently only snaps to items in the mg
void snap_sprite(COMPONENT *self) {
  CDATA_TRANSFORM *transformData = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  CDATA_CURSORLOGIC *data = (CDATA_CURSORLOGIC *)self->data;
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  VEC3 pos;
  LIST_NODE * currNode = data->snaps->first;
  POINT mousePos;
  SPACE *mg = game_getSpace(self->owner->space->game, "mg");

  space_mouseToWorld(mg, &input->mouse.position, &mousePos);

  pos.x = (float)mousePos.x;
  pos.y = (float)mousePos.y;

  while(currNode != NULL) {
    RECTANGLE *rect = (RECTANGLE *)currNode->data;
    VEC2 topLeft = rect->topLeft;
    VEC2 botRight = rect->botRight;
    float middleX = botRight.x - (0.5f * (botRight.x - topLeft.x));
    float middleY = topLeft.y - (0.5f * (topLeft.y - botRight.y));
    VEC3 camTranslate = { 0 };

    space_getCamTranslate(mg, &camTranslate);
    middleX -= camTranslate.x;
    middleY -= camTranslate.y;

    if ((pos.x >= topLeft.x && pos.x <= botRight.x) && (pos.y <= topLeft.y && pos.y >= botRight.y)) {
      transformData->world.translation.x = middleX;
      transformData->world.translation.y = middleY;
    }
    currNode = currNode->next;
  }

}

LIST_NODE *add_snap(COMPONENT *self, float left, float top, float right, float bot) {
  CDATA_CURSORLOGIC *data = (CDATA_CURSORLOGIC *)self->data;
  RECTANGLE rect = {{left, top}, {right, bot}};
  LIST_NODE *ret; 
  RECTANGLE *pRect = (RECTANGLE *)malloc(sizeof(RECTANGLE));
  *pRect = rect;
  
  ret = list_insert_end(data->snaps, (void *)pRect);

  return ret;
}

void remove_snap(COMPONENT *self, LIST_NODE *remove) {
  CDATA_CURSORLOGIC *data = (CDATA_CURSORLOGIC *)self->data;
  list_remove_free(data->snaps, remove);
}

void free_snaps(COMPONENT *self) {
  CDATA_CURSORLOGIC *data = (CDATA_CURSORLOGIC *)self->data;
  LIST_NODE * currNode = data->snaps->first;

  while(currNode != NULL) {
    LIST_NODE *nextNode = currNode->next;
    list_remove_free(data->snaps, currNode);
    currNode = nextNode;
  }
}

void comp_cursorLogic_destroy(COMPONENT *self, void *event) {
  CDATA_CURSORLOGIC *data = (CDATA_CURSORLOGIC *)self->data;
  LIST_NODE * currNode = data->snaps->first;

  while(currNode != NULL) {
    LIST_NODE *nextNode = currNode->next;
    list_remove_free(data->snaps, currNode);
    currNode = nextNode;
  }

  list_destroy(data->snaps);
}

int getRoomSize(ROOM_TYPE toBuild) {
  return 2;
}
LIST *findBuildSpot(ROOM_TYPE toBuild, int roomSize) {
  LIST *newList = list_create();
  VEC3 *data = (VEC3 *)malloc(sizeof(VEC3));
  data->x = 6;
  data->y = 2;
  list_insert_end(newList, (void *)data);

  return newList;
}