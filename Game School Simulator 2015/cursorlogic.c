/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "cursorlogic.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/sprite.h"
#include <math.h>


void comp_cursorLogic_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  CDATA_CURSORLOGIC *data = (CDATA_CURSORLOGIC *)entity_getComponentData(self->owner, COMP_CURSORLOGIC);
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  POINT mousePos;

  space_mouseToWorld(self->owner->space, &input->mouse.position, &mousePos);
  trans->translation.x = (float)mousePos.x + 4.0f;
  trans->translation.y = (float)mousePos.y - 8.0f;
  snap_sprite(self);
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
void snap_sprite(COMPONENT *self) {
  CDATA_TRANSFORM *transformData = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  CDATA_CURSORLOGIC *data = (CDATA_CURSORLOGIC *)self->data;
  VEC3 pos = transformData->translation;
  LIST_NODE * currNode = data->snaps->first;


  while(currNode != NULL) {
    RECTANGLE *rect = (RECTANGLE *)currNode->data;
    VEC2 topLeft = rect->topLeft;
    VEC2 botRight = rect->botRight;
    float middleX = botRight.x - (0.5f * (botRight.x - topLeft.x));
    float middleY = topLeft.y - (0.5f * (topLeft.y - botRight.y));

    if ((pos.x >= topLeft.x && pos.x <= botRight.x) && (pos.y <= topLeft.y && pos.y >= botRight.y)) {
      
      transformData->translation.x = middleX;
      transformData->translation.y = middleY;
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