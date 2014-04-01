/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "ghostroomlogic.h"
#include "mousebox.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/transform.h"
#include "playerlogic.h"
#include "cursorlogic.h"
#include "tutorial.h"

// fix all mboxes to handle things
void comp_ghostRoomLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  CDATA_GHOSTROOMLOGIC *gData = (CDATA_GHOSTROOMLOGIC *)self->data;

  if (mbox->over) {
    sprite->color.a = 0.8f;
  }
  else
    sprite->color.a = 0.55f;

  if (mbox->left.pressed) {
    SPACE *ui = game_getSpace(self->owner->space->game, "ui");
    ENTITY *cursor = space_getEntity(ui, "cursor");
    ENTITY *player = space_getEntity(ui, "player");
    CDATA_PLAYERLOGIC *playerData = (CDATA_PLAYERLOGIC *)entity_getComponentData(player, COMP_PLAYERLOGIC);
    LIST *ghostrooms = list_create();
    LIST_NODE *pNode;

    comp_schoolLogic_constructRoom(self, gData->roomType, gData->roomSize, gData->point.y, gData->point.x);

#if TUTORIAL
    if (playerData->lobbyBuilt == false) {
      createThirdTutorial(ui);
      playerData->lobbyBuilt = true;
    }

    else if (playerData->classroomBuilt == false) {
      createFourthTutorial(ui);
      playerData->classroomBuilt = true;
    }
#endif

    space_getAllEntities(self->owner->space, "ghostRoom", ghostrooms);
    pNode = ghostrooms->first;
    while (pNode) {
      ENTITY *groom = (ENTITY *)pNode->data;
      entity_destroy(groom);
      pNode = pNode->next;
    }
    list_destroy(ghostrooms);
  }
}


void comp_ghostRoomLogic(COMPONENT *self) {
  CDATA_GHOSTROOMLOGIC data = { 0 };
  data.constructed = false;
  COMPONENT_INIT(self, COMP_GHOSTROOMLOGIC, data);
  self->events.logicUpdate = comp_ghostRoomLogic_logicUpdate;
}
