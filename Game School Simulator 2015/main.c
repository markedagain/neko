/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <Windows.h>
#include "../NekoEngine/game.h"
#include "../NekoEngine/space.h"
#include "../NekoEngine/neko.h"
#include "player.h"
#include "cursor.h"
#include "gamemanager.h"
#include "util.h"
#include "student.h"
#include "data.h"
#include "../NekoEngine/genericsprite.h"
#include "../NekoEngine/sprite.h"
#include "../NekoEngine/transform.h"

#pragma comment (lib, "../lib/neko.lib")

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPSTR command, int show) {
  GAME *game;
#if 0
  SPACE *simSpace;
  SPACE *bgSpace;
  SPACE *mgSpace;
  SPACE *fgSpace;
  SPACE *uiSpace;
  ENTITY *ent; // temporary entity
  VEC3 position;
#endif
  game = game_create(instance, previous, command, show);
#if 0
  // sim - where the simulation occurs
  simSpace = game_addSpace(game, "sim");
  simSpace->visible = false;
  simSpace->systems.time.scale = 0.0166666666666667f;
  space_addEntity(simSpace, arch_gameManager, "gameManager");

  // bg - background, sky, clouds, etc.
  bgSpace = game_addSpace(game, "bg");
  vec3_set(&position, 0, 360 - 24, 0);
  ent = space_addEntityAtPosition(bgSpace, arch_genericSprite, "backdrop", &position);
  ((CDATA_SPRITE *)entity_getComponentData(ent, COMP_SPRITE))->source = "backgrounds/basic";

  // mg - midground, rooms
  mgSpace = game_addSpace(game, "mg");

  vec3_set(&position, 0, 40, 0);
  ent = space_addEntityAtPosition(mgSpace, arch_genericSprite, NULL, &position);
  ((CDATA_SPRITE *)entity_getComponentData(ent, COMP_SPRITE))->source = "rooms/frontdoor";

  vec3_set(&position, -120, 40, 0);
  ent = space_addEntityAtPosition(mgSpace, arch_genericSprite, NULL, &position);
  ((CDATA_SPRITE *)entity_getComponentData(ent, COMP_SPRITE))->source = "rooms/exterior";

  vec3_set(&position, -120, 120, 0);
  ent = space_addEntityAtPosition(mgSpace, arch_genericSprite, NULL, &position);
  ((CDATA_SPRITE *)entity_getComponentData(ent, COMP_SPRITE))->source = "rooms/exterior";

  vec3_set(&position, 0, 120, 0);
  ent = space_addEntityAtPosition(mgSpace, arch_genericSprite, NULL, &position);
  ((CDATA_SPRITE *)entity_getComponentData(ent, COMP_SPRITE))->source = "rooms/exterior2";

  // fg - foreground, students
  fgSpace = game_addSpace(game, "fg");

  // ui - user interface
  uiSpace = game_addSpace(game, "ui");
  space_addEntity(uiSpace, arch_player, "player");
  space_addEntity(uiSpace, arch_cursor, "cursor");
#endif
  return game_start(game);
}
