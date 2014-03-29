/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "studentactor.h"
#include "transform.h"
#include "multisprite.h"
#include "studentactorlogic.h"
#include "mousebox.h"

void arch_studentActor(ENTITY *entity) {
  CDATA_SPRITE *sprite;
  CDATA_MOUSEBOX *mbox;
  entity->id = ARCH_STUDENTACTOR;

  entity_connect(entity, comp_transform);
  entity_connect(entity, comp_multiSprite);
  entity_connect(entity, comp_studentActorLogic);
  mbox = (CDATA_MOUSEBOX *)entity_connect(entity, comp_mouseBox);
  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  sprite->source = "student/studentBox";
  sprite->visible = false;
  mbox->manual = false;
  mbox->active = true;

}