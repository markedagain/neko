/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

// Include any component headers you need here, plus the header of this archetype,
// plus component.h and entity.h
#include "test.h"
#include "../NekoEngine/entity.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/sprite.h"
#include "playerlogic.h"

void arch_test(ENTITY *entity) {
  // You only need to declare data structures for components that need them. Or, like, you don't
  // have to do all this if you just want to pass the default data to the component. If you don't
  // care where an archetype's default position is, just entity_connect() the components!
  CDATA_TRANSFORM *transform;
  CDATA_SPRITE *sprite;

  // This line is important! This makes this entity's id set to its archetype, so we can always do
  // entity->id to get its archetype (sort of).
  entity->id = ARCH_TEST;

  // This is what it looks like to connect a transform component and set its values! Remember, you
  // don't have to do all this work if you don't want to actually change the default values, just
  // do an entity_connect()
  transform = (CDATA_TRANSFORM *)entity_connect(entity, comp_transform);
  transform->translation.x = 0.0f;
  transform->translation.y = 0.0f;

  // And here's the sprite component. Yeah, it kind of sucks for now.
  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  sprite->source = "data/spr/PlanetTexture.png";

  // This is what it looks like to connect a component to an entity without setting any data or
  // anything! Super easy, right?
  entity_connect(entity, comp_playerLogic);
}
