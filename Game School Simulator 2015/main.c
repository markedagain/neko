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
#include "roomactor.h"
#include "UI_base.h"
#include "UI_build.h"
#include "UI_manage.h"
#include "UI_student.h"
#include "UI_button.h"
#include "splash.h"
#include "blackbar.h"
#include "studentactor.h"
#include "studentmanager.h"
#include "background.h"
#include "main.h"
#include "menuscreen.h"

#pragma comment (lib, "../lib/neko.lib")

#if _CHECK_LEAKS
#pragma comment (lib, "C:\\Program Files (x86)\\Visual Leak Detector\\lib\\Win32\\vld.lib")
#include <vld.h>
#endif

int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR commandLine, int show) {
  GAME *game;
  SPACE *simSpace;
  SPACE *bgSpace;
  SPACE *mgSpace;
  SPACE *fgSpace;
  SPACE *uiSpace;
  SPACE *splashSpace;
  SPACE *cursorSpace;
  VEC3 position;
  VEC4 color = { 1, 0, 0, 1 };
  VEC2 dimensions = { 40.0f, 20.0f };
  ENTITY *ent1;
  /*ENTITY *ent2;
  ENTITY *ent3;*/

  game = game_create(instanceH, show);

  // sim - where the simulation occurs
  simSpace = game_addSpace(game, "sim");
  simSpace->visible = false;
  //simSpace->systems.time.scale = 0.0166666666666667f;
  //simSpace->systems.time.scale = 0.0f;

  space_addEntity(simSpace, arch_gameManager, "gameManager");

  // bg - background, sky, clouds, etc.
  bgSpace = game_addSpace(game, "bg");
  vec3_set(&position, 0, 360 - 24, 0);
  space_addEntityAtPosition(bgSpace, arch_background, "backdrop", &position);
  //genericSprite_create(bgSpace, &position, "backdrop", "backgrounds/basic");

  // mg - midground, rooms
  mgSpace = game_addSpace(game, "mg");

  //space_addEntity(mgSpace, arch_roomActor, "roomActor");
  //vec3_set(&position, 0, 40, 0);
  //genericSprite_create(mgSpace, &position, NULL, "rooms/template2");

  /*
  vec3_set(&position, -120, 40, 0);
  genericSprite_create(mgSpace, &position, NULL, "rooms/template");

  vec3_set(&position, -120, 120, 0);
  genericSprite_create(mgSpace, &position, NULL, "rooms/template");

  vec3_set(&position, 0, 120, 0);
  genericSprite_create(mgSpace, &position, NULL, "rooms/template2");*/

  // fg - foreground, students
  fgSpace = game_addSpace(game, "fg");
  space_addEntity(fgSpace, arch_studentManager, "studentManager");

  // ui - user interface
  uiSpace = game_addSpace(game, "ui");
  space_addEntity(uiSpace, arch_player, "player");

  // create the main menu
  createMainMenu(game);

  /*
  vec3_set(&position, 100.0f, 40.0f, 0);
  vec2_set(&dimensions, 100.0f, 40.0f);
  ent1 = genericSprite_createBlank(uiSpace, &position, &dimensions, &color, "TEST1");

  vec4_set(&color, 0.0f, 1.0f, 0.0f, 1.0f);
  vec3_set(&position, -20.0f, -10.0f, 0);
  vec2_set(&dimensions, 20.0f, 10.0f);
  ent2 = genericSprite_createBlank(uiSpace, &position, &dimensions, &color, "TEST2");
  entity_attach(ent2, ent1);

  vec3_set(&position, -20.0f, 0, 0);
  vec4_set(&color, 0.0f, 0.0f, 1.0f, 1.0f);
  ent3 = genericText_create(uiSpace, &position, NULL, "fonts/gothic/12", "CHILD!", &color);
  entity_attach(ent3, ent2);
  */

  vec3_set(&position, 0, -180, 0);
  ent1 = space_addEntityAtPosition(uiSpace, arch_uibuild, "build_button", &position);
  // sets the button type to build
  ((CDATA_UI_BUTTON *)entity_getComponentData(ent1, COMP_UI_BUTTON))->type = BUTTON_BUILD;
  vec3_set(&position, 0, 180, 0);
  space_addEntityAtPosition(uiSpace, arch_uimanage, "manage_button", &position);
  /*vec3_set(&position, -318, 180, 0);
  genericText_create(uiSpace, &position, NULL, "fonts/gothic/20", "Game School Simulator 2015", &color);
  vec3_set(&position, -318, 160, 0);
  genericText_create(uiSpace, &position, NULL, "fonts/gothic/12", "Engine Proof", &color);
  vec3_set(&position, -318, 112, 0);
  genericText_create(uiSpace, &position, NULL, "fonts/gothic/12", "Dynamic sprite-based text rendering\n - Draws each character manually\n - Support for different \"fonts\"\n - Supports newlines", &color);*/
  space_addEntity(uiSpace, arch_cursor, "cursor");
  splashSpace = game_addSpace(game, "splash");
  vec3_set(&position, 0.0f, 0.0f, 0.0f);
  vec4_set(&color, 1.0f, 1.0f, 1.0f, 1.0f);
  vec2_set(&dimensions, 640.0f, 360.0f);
  genericSprite_createBlank(splashSpace, &position, &dimensions, &color, "splash_bg");
  space_addEntity(splashSpace, arch_splash, "splash");

  cursorSpace = game_addSpace(game, "cursor");
  genericSprite_create(cursorSpace, &position, "cursorSprite", "cursor/default");
  space_addEntity(cursorSpace, arch_blackbar, "blackbar1");
  space_addEntity(cursorSpace, arch_blackbar, "blackbar2");

  game_start(game);

  return 1;
}


void createMainMenu(GAME *game) {
  SPACE *menu = game_addSpace(game, "menu");
  VEC3 position = { 0 };

  space_addEntityAtPosition(menu, arch_menuScreen, "menuscreen", &position);
}
