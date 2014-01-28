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
#include "../NekoEngine/spritetext.h"

#pragma comment (lib, "../lib/neko.lib")

int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR commandLine, int show) {
  GAME *game;
  SPACE *simSpace;
  SPACE *bgSpace;
  SPACE *mgSpace;
  SPACE *fgSpace;
  SPACE *uiSpace;
  VEC3 position;
  VEC4 color = { 1, 0, 0, 1 };

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
  genericSprite_create(mgSpace, &position, NULL, "rooms/template2");

  vec3_set(&position, -120, 40, 0);
  genericSprite_create(mgSpace, &position, NULL, "rooms/template");

  vec3_set(&position, -120, 120, 0);
  genericSprite_create(mgSpace, &position, NULL, "rooms/template");

  vec3_set(&position, 0, 120, 0);
  genericSprite_create(mgSpace, &position, NULL, "rooms/template2");

  // fg - foreground, students
  fgSpace = game_addSpace(game, "fg");

  // ui - user interface
  uiSpace = game_addSpace(game, "ui");

  vec3_set(&position, -318, 180, 0);
  genericText_create(uiSpace, &position, NULL, "fonts/gothic/28", "MS GOTHIC 28", &color);
  vec3_set(&position, -318, 150, 0);
  genericText_create(uiSpace, &position, NULL, "fonts/gothic/20", "MS GOTHIC 20", &color);
  vec3_set(&position, -318, 130, 0);
  genericText_create(uiSpace, &position, NULL, "fonts/gothic/16", "MS GOTHIC 16", &color);
  vec3_set(&position, -318, 112, 0);
  genericText_create(uiSpace, &position, NULL, "fonts/gothic/12", "MS GOTHIC 12", &color);
  vec3_set(&position, -318, 98, 0);
  genericText_create(uiSpace, &position, NULL, "fonts/c64/8", "COMMODORE 64 8x8", &color);
  vec3_set(&position, -318, 88, 0);
  genericText_create(uiSpace, &position, NULL, "fonts/terminal/6", "TERMINAL 6\n\n(SUPER SUPER TINY FONT FOR LIKE\nIDK STUDENTS' THOUGHTS AND STUFF\nOR SOMETHING) HOLY SHIT NEWLINES\nTOTES WORK", &color);
  space_addEntity(uiSpace, arch_player, "player");
  space_addEntity(uiSpace, arch_cursor, "cursor");

  game_start(game);

  return 1;
}
