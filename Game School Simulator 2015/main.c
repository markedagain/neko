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
#include "inspectionscreen.h"
#include "background.h"
#include "newsfeed.h"
#include "main.h"
#include "menuscreen.h"

#pragma comment (lib, "../lib/neko.lib")

#if _CHECK_LEAKS
#pragma comment (lib, "C:\\Program Files (x86)\\Visual Leak Detector\\lib\\Win32\\vld.lib")
#include <vld.h>
#endif

int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR commandLine, int show) {
  GAME *game;
  
  game = game_create(instanceH, show);

  // create all spaces except main menu
  createSpaces(game);
  initializeEssentialSpaces(game);
  startNewGame(game);
  // create the main menu
  createMainMenu(game);
  game_start(game);

  return 1;
}

void createSpaces(GAME *game) {
  SPACE *simSpace = game_addSpace(game, "sim");
  SPACE *bgSpace = game_addSpace(game, "bg");
  SPACE *mgSpace = game_addSpace(game, "mg");
  SPACE *fgSpace = game_addSpace(game, "fg");
  SPACE *uiSpace = game_addSpace(game, "ui");
  SPACE *menu = game_addSpace(game, "menu");
  SPACE *splashSpace = game_addSpace(game, "splash");
  SPACE *cursorSpace = game_addSpace(game, "cursor");

  simSpace->visible = false;
}

void initializeEssentialSpaces(GAME *game) {
  SPACE *uiSpace = game_getSpace(game, "ui");
  SPACE *splashSpace = game_getSpace(game, "splash");
  SPACE *cursorSpace = game_getSpace(game, "cursor");
  VEC3 position = { 0 };
  VEC4 color = { 0 };
  VEC2 dimensions = { 0 };

  /**************** UI SPACE *****************/
  // add player
  space_addEntity(uiSpace, arch_player, "player");

  // add cursor
  space_addEntity(uiSpace, arch_cursor, "cursor");

  /************** SPLASH SPACE ***************/
  // add splash screen
  vec3_set(&position, 0.0f, 0.0f, 0.0f);
  vec4_set(&color, 1.0f, 1.0f, 1.0f, 1.0f);
  vec2_set(&dimensions, 640.0f, 360.0f);
  genericSprite_createBlank(splashSpace, &position, &dimensions, &color, "splash_bg");
  space_addEntity(splashSpace, arch_splash, "splash");

  /************** CURSOR SPACE **************/
  // add invisibile cursor
  genericSprite_create(cursorSpace, &position, "cursorSprite", "cursor/default");
  
  // add blackbars
  space_addEntity(cursorSpace, arch_blackbar, "blackbar1");
  space_addEntity(cursorSpace, arch_blackbar, "blackbar2");
}


void createMainMenu(GAME *game) {
  SPACE *menu = game_getSpace(game, "menu");
  VEC3 position = { 0 };
  VEC2 dimensions = { 640, 360 };
  genericSprite_createBlank(menu, &position, &dimensions, &colors[C_NAVY_LIGHT], NULL);
  space_addEntityAtPosition(menu, arch_menuScreen, "menuscreen", &position);
}

void startNewGame(GAME *game) {
  SPACE *simSpace = game_getSpace(game, "sim");
  SPACE *bgSpace = game_getSpace(game, "bg");
  SPACE *mgSpace = game_getSpace(game, "mg");
  SPACE *fgSpace = game_getSpace(game, "fg");
  SPACE *uiSpace = game_getSpace(game, "ui");

  VEC3 position;
  VEC4 color = { 1, 0, 0, 1 };
  VEC2 dimensions = { 40.0f, 20.0f };
  ENTITY *ent1;
  ENTITY *inspectBox;
  
  /**************** SIM SPACE ****************/
  space_addEntity(simSpace, arch_gameManager, "gameManager");

  /**************** BG SPACE *****************/
  // add backdrop
  vec3_set(&position, 0, 360 - 24, 0);
  space_addEntityAtPosition(bgSpace, arch_background, "backdrop", &position);

  /**************** MG SPACE *****************/

  /**************** FG SPACE *****************/
  // manager for student actors
  space_addEntity(fgSpace, arch_studentManager, "studentManager");

  /**************** UI SPACE *****************/
  // news feed
  space_addEntity(uiSpace, arch_newsFeed, "newsFeed");

  // create build button
  vec3_set(&position, 0, -180, 0);
  ent1 = space_addEntityAtPosition(uiSpace, arch_uibuild, "build_button", &position);
  // sets the button type to build
  ((CDATA_UI_BUTTON *)entity_getComponentData(ent1, COMP_UI_BUTTON))->type = BUTTON_BUILD;

  // create pause button
  vec3_set(&position, -240, 180, 0);
  ent1 = space_addEntityAtPosition(uiSpace, arch_uibuild, "pause_button", &position);
  // sets the button type to pause
  ((CDATA_UI_BUTTON *)entity_getComponentData(ent1, COMP_UI_BUTTON))->type = BUTTON_PAUSE;

  // create fastForward button
  vec3_set(&position, -180, 180, 0);
  ent1 = space_addEntityAtPosition(uiSpace, arch_uibuild, "slow_button", &position);
  // sets the button type to fastForward
  ((CDATA_UI_BUTTON *)entity_getComponentData(ent1, COMP_UI_BUTTON))->type = BUTTON_SLOWDOWN;

  // create slowDown button
  vec3_set(&position, -120, 180, 0);
  ent1 = space_addEntityAtPosition(uiSpace, arch_uibuild, "fast_button", &position);
  // sets the button type to slowDown
  ((CDATA_UI_BUTTON *)entity_getComponentData(ent1, COMP_UI_BUTTON))->type = BUTTON_FASTFORWARD;

  // create manage button
  vec3_set(&position, 0, 180, 0);
  space_addEntityAtPosition(uiSpace, arch_uimanage, "manage_button", &position);

  // create inspection screen
  vec3_set(&position, -2000, 150, 0);
  inspectBox = space_addEntityAtPosition(uiSpace, arch_inspectionScreen, "inspection_screen", &position);

}