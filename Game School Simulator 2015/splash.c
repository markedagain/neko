/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "splash.h"
#include "transform.h"
#include "sprite.h"
#include "splashlogic.h"

void arch_splash(ENTITY *entity) {
  CDATA_SPRITE *sprite;

  entity->id = ARCH_SPLASH;

  entity_connect(entity, comp_transform);

  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  sprite->source = "digipen";
  sprite->color.a = 0.0f;
  
  entity_connect(entity, comp_splashLogic);
}