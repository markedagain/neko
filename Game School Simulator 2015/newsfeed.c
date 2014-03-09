/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "newsfeed.h"
#include "newsfeedlogic.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/transform.h"

void arch_newsFeed(ENTITY *entity) {
  entity->id = ARCH_NEWSFEED;

  //Connect components to the entity
  entity_connect(entity, comp_transform);
  entity_connect(entity, comp_newsfeedlogic);
}
