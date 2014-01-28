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

  vec3_set(&position, -256, 160, 0);
  genericText_create(uiSpace, &position, NULL, "fonts/gothic/20", "NEKO MEANS CAT PRESENTS", &color);
  vec3_set(&position, -256, 128, 0);
  genericText_create(uiSpace, &position, NULL, "fonts/gothic/16", "GAME SCHOOL SIMULATOR 2015\nENGINE PROOF", &color);
  vec3_set(&position, -256, 80, 0);
  genericText_create(uiSpace, &position, NULL, "fonts/gothic/12", "NOW WITH TOTALLY BANGIN'\nSPRITETEXT", &color);
  vec3_set(&position, -256, 48, 0);
  genericText_create(uiSpace, &position, NULL, "fonts/c64/8", "AND LIKE SIX DIFFERENT FONTS", &color);
  vec3_set(&position, -256, 36, 0);
  genericText_create(uiSpace, &position, NULL, "fonts/terminal/6", "OKAY ONLY FOUR; MS GOTHIC 4 LYFE (THIS ONE IS TERMINAL THO)", &color);
  vec3_set(&position, -256, 28, 0);
  genericText_create(uiSpace, &position, NULL, "fonts/gothic/28", "JUST KIDDING, NOW THERE'S SIX", &color);
  space_addEntity(uiSpace, arch_player, "player");
  space_addEntity(uiSpace, arch_cursor, "cursor");

  game_start(game);

  return 1;
}
