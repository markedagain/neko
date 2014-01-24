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

int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR commandLine, int show) {
  GAME *game;
  SPACE *simSpace;
  SPACE *bgSpace;
  SPACE *mgSpace;
  SPACE *fgSpace;
  SPACE *uiSpace;
  ENTITY *backdrop;

  game = game_create(instanceH, show);

  // sim - where the simulation occurs
  simSpace = game_addSpace(game, "sim");
  simSpace->visible = false;
  simSpace->systems.time.scale = 0.0166666666666667f;
  space_addEntity(simSpace, arch_gameManager, "gameManager");

  // bg - background, sky, clouds, etc.
  bgSpace = game_addSpace(game, "bg");
  backdrop = space_addEntity(bgSpace, arch_genericsprite, "backdrop");
  ((CDATA_SPRITE *)entity_getComponentData(backdrop, COMP_SPRITE))->source = "backgrounds/basic";
  ((CDATA_TRANSFORM *)entity_getComponentData(backdrop, COMP_TRANSFORM))->translation.y = -24;

  // mg - midground, rooms
  mgSpace = game_addSpace(game, "mg");

  // fg - foreground, students
  fgSpace = game_addSpace(game, "fg");

  // ui - user interface
  uiSpace = game_addSpace(game, "ui");
  space_addEntity(uiSpace, arch_player, "player");
  space_addEntity(uiSpace, arch_cursor, "cursor");

  game_start(game);

  return 1;
}
