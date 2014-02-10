/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "cursorlogic.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/sprite.h"
#include "../NekoEngine/entity.h"
#include <math.h>
#include "ghostroomlogic.h"

#define GROUND_HEIGHT 24

// problems here with freeing the memory and resetting the "snapped" bool
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
  ENTITY *ghostroom;
  CDATA_GHOSTROOMLOGIC *gRoomData;
  int roomSize;
  ROOM_TYPE toBuild;
  LIST *buildSpaces;

  space_mouseToWorld(self->owner->space, &input->mouse.position, &mousePos);
  trans->translation.x = (float)mousePos.x;
  trans->translation.y = (float)mousePos.y;

  if (playerData->gameMode == BUILD) {
    if (data->gameMode != BUILD) {
      toBuild = playerData->roomType;
      roomSize = comp_schoolLogic_getRoomSize(toBuild);
      buildSpaces = comp_schoolLogic_findBuildSpots(self, toBuild, roomSize);
      //if (buildSpaces != NULL)
      findWorldBuildSpots(self, buildSpaces, roomSize);
      data->gameMode = BUILD;
    }
    else {
      snap_sprite(self);
    }
    if (data->snapped && input->mouse.left == ISTATE_PRESSED) {
      ghostroom = space_getEntity(mgSpace, "ghostroom");
      gRoomData = (CDATA_GHOSTROOMLOGIC *)entity_getComponentData(ghostroom, COMP_GHOSTROOMLOGIC);
      gRoomData->constructed = true;
      data->gameMode = DEFAULT;
    }
  }
  else {
    data->snapped = false;
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
  VEC3 sizeOfSquare = { 80.0f, 80.0f, 0 };
  POINT *simPoint;


  while(pNode) {
    simPoint = (POINT *)pNode->data;
    x = (int)simPoint->x;
    y = (int)simPoint->y;

    left = (x - 8) * sizeOfSquare.x;
    right = left + sizeOfSquare.x * roomSize;
    top = (3 - y) * sizeOfSquare.y; //+ GROUND_HEIGHT * screenScale * camScale.y;
    bot = top - sizeOfSquare.y;

    add_snap(self, left, top, right, bot);

    pNode = pNode->next;
  }
}

void adjust_snaps(COMPONENT *self, RECTANGLE *inRect, VEC3 *topLeft, VEC3 *botRight) {
  VEC3 camScale;
  //VEC3 screenScaleVec;
  //float screenScale;
  MATRIX3 transform = { 0 };
  SPACE *mgSpace = game_getSpace(self->owner->space->game, "mg");
  CDATA_CURSORLOGIC *data = (CDATA_CURSORLOGIC *)self->data;
  LIST_NODE *currNode = data->snaps->first;
  RECTANGLE *rect = inRect;

  topLeft->x = rect->topLeft.x;
  topLeft->y = rect->topLeft.y;
  botRight->x = rect->botRight.x;
  botRight->y = rect->botRight.y;

  camScale.x = mgSpace->systems.camera.transform.scale.x;
  camScale.y = mgSpace->systems.camera.transform.scale.y;

  //screenScale = (float)self->owner->space->game->innerWindow.width / self->owner->space->game->dimensions.width;
  //screenScaleVec.x = screenScale;
  //screenScaleVec.y = screenScale;

  matrix3_identity(&transform);
  matrix3_scale(&transform, &camScale);
  //matrix3_scale(&transform, &screenScaleVec);

  matrix3_apply_to_vector(topLeft, &transform);
  matrix3_apply_to_vector(botRight, &transform);

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
  LIST_NODE *currNode = data->snaps->first;
  POINT mousePos;
  SPACE *mg = game_getSpace(self->owner->space->game, "mg");

  space_mouseToWorld(mg, &input->mouse.position, &mousePos);

  pos.x = (float)mousePos.x;
  pos.y = (float)mousePos.y;

  while(currNode != NULL) {
    RECTANGLE *rect = (RECTANGLE *)currNode->data;
    VEC3 topLeft; 
    VEC3 botRight;
    float middleX;
    float middleY;
    VEC3 camTranslate = { 0 };
    VEC3 camScale = { 0 };
    MATRIX3 transform = { 0 };

    camScale.x = mg->systems.camera.transform.scale.x;
    camScale.y = mg->systems.camera.transform.scale.y;

    matrix3_identity(&transform);
    matrix3_scale(&transform, &camScale);

    topLeft.x = rect->topLeft.x;
    topLeft.y = rect->topLeft.y;
    botRight.x = rect->botRight.x;
    botRight.y = rect->botRight.y;

    adjust_snaps(self, rect, &topLeft, &botRight);

    middleX = botRight.x - (0.5f * (botRight.x - topLeft.x));
    middleY = topLeft.y - (0.5f * (topLeft.y - botRight.y));

    //space_getCamTranslate(mg, &camTranslate);

    camTranslate.x = mg->systems.camera.transform.translation.x;
    camTranslate.y = mg->systems.camera.transform.translation.y;

    matrix3_apply_to_vector(&camTranslate, &transform);

    middleX -= camTranslate.x;
    middleY -= camTranslate.y;

    printf("=========================%f==================================\n", pos.x);

    if ((pos.x >= topLeft.x && pos.x <= botRight.x) && (pos.y <= topLeft.y && pos.y >= botRight.y)) {
      transformData->translation.x = middleX;
      transformData->translation.y = middleY;
      data->snapped = true;
      return;
    }
    currNode = currNode->next;
  }
  data->snapped = false;

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

/*
int getRoomSize(ROOM_TYPE toBuild) {
  return 2;
}
LIST *findBuildSpot(ROOM_TYPE toBuild, int roomSize) {
  LIST *newList = list_create();
  VEC3 *data = (VEC3 *)malloc(sizeof(VEC3));
  data->x = 5;
  data->y = 2;
  list_insert_end(newList, (void *)data);

  return newList;
}*/