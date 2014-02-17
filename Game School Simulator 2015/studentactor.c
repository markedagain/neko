/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "studentactor.h"
#include "transform.h"
#include "multisprite.h"
#include "studentactorlogic.h"

void arch_studentActor(ENTITY *entity) {
  //CDATA_SPRITE *sprite;
  entity->id = ARCH_STUDENTACTOR;

  entity_connect(entity, comp_transform);
  entity_connect(entity, comp_multiSprite);
  //sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  entity_connect(entity, comp_studentActorLogic);

  //sprite->source = "student/male/hair/01";
}