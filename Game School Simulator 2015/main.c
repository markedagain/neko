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
#include "../NekoEngine/generictext.h"
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
  VEC3 position;
  VEC4 color = { 1, 1, 1, 1 };

  game = game_create(instanceH, show);

  // sim - where the simulation occurs
  simSpace = game_addSpace(game, "sim");
  simSpace->visible = false;
  simSpace->systems.time.scale = 0.0166666666666667f;

  space_addEntity(simSpace, arch_gameManager, "gameManager");

  // bg - background, sky, clouds, etc.
  bgSpace = game_addSpace(game, "bg");
  vec3_set(&position, 0, 360 - 24, 0);
  genericSprite_create(bgSpace, &position, "backdrop", "backgrounds/basic");

  // mg - midground, rooms
  mgSpace = game_addSpace(game, "mg");

  vec3_set(&position, 0, 40, 0);
  genericSprite_create(mgSpace, &position, NULL, "rooms/frontdoor");

  vec3_set(&position, -120, 40, 0);
  genericSprite_create(mgSpace, &position, NULL, "rooms/exterior");

  vec3_set(&position, -120, 120, 0);
  genericSprite_create(mgSpace, &position, NULL, "rooms/exterior");

  vec3_set(&position, 0, 120, 0);
  genericSprite_create(mgSpace, &position, NULL, "rooms/exterior2");

  vec3_set(&position, 0, 0, 0);
  //genericSprite_create(mgSpace, &position, NULL, "test");

  // fg - foreground, students
  fgSpace = game_addSpace(game, "fg");

  // ui - user interface
  uiSpace = game_addSpace(game, "ui");

  vec3_set(&position, 0, 0, 0);
  //genericText_create(uiSpace, &position, NULL, "font/8x8", "HEY HI HELLO", &color);
  space_addEntity(uiSpace, arch_player, "player");
  space_addEntity(uiSpace, arch_cursor, "cursor");

  game_start(game);

  return 1;
}
