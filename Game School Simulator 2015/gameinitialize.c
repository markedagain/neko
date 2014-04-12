/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "gameinitialize.h"
#include "tutorial.h"
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
#include "menuscreen.h"
#include "namescreen.h"
#include "colors.h"
#include "custombutton.h"
#include "moneyinfo.h"
#include "playerlogic.h"
#include "creditsscreen.h"
#include "mousebox.h"

void startGame(GAME *game) {
  ENTITY *player;
  CDATA_PLAYERLOGIC *playerData;
  (game_getSpace(game, "sim"))->active = true;
  (game_getSpace(game, "bg"))->active = true;
  (game_getSpace(game, "mg"))->active = true;
  (game_getSpace(game, "fg"))->active = true;
  sound_playSong(&game->systems.sound, "03");

  if (game->config.tutorial)
    createFirstTutorial(game_getSpace(game, "ui"));

  player = space_getEntity(game_getSpace(game,"ui"), "player");
  playerData = (CDATA_PLAYERLOGIC *)entity_getComponentData(player, COMP_PLAYERLOGIC);
  playerData->currentMode = GM_PLAY;
}

void createSpaces(GAME *game) {
  SPACE *simSpace = game_addSpace(game, "sim");
  game_addSpace(game, "bg");
  game_addSpace(game, "mg");
  game_addSpace(game, "fg");
  game_addSpace(game, "ui");
  
  if (game->config.tutorial)
    game_addSpace(game, "tutorial");

  game_addSpace(game, "menu");
  game_addSpace(game, "splash");
  game_addSpace(game, "cursor");

  simSpace->visible = false;
}

void initializeEssentialSpaces(GAME *game) {
  SPACE *uiSpace = game_getSpace(game, "ui");
  SPACE *splashSpace = game_getSpace(game, "splash");
  SPACE *cursorSpace = game_getSpace(game, "cursor");
  SPACE *menu = game_getSpace(game, "menu");
  VEC3 position = { 0 };
  VEC4 color = { 0 };
  VEC2 dimensions = { 0 };

  /**************** UI SPACE *****************/
  // add player
  space_addEntity(uiSpace, arch_player, "player");

  // add cursor
  space_addEntity(uiSpace, arch_cursor, "cursor");

  /*************** MENU SPACE ****************/
  vec2_set(&dimensions, 640.0f, 360.0f);
  genericSprite_createBlank(menu, &position, &dimensions, &colors[C_NAVY_LIGHT], NULL);

  /************** SPLASH SPACE ***************/
  // add splash screen
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
  ENTITY *copyright, *pressStart;

  space_addEntityAtPosition(menu, arch_menuScreen, "menuScreen", &position);
  
  genericSprite_create(menu, &position, "logo", "logo");
  
  position.y = -180.0f;
  copyright = genericText_create(menu, &position, "copyright", "fonts/gothic/12", "Copyright (C) 2014 DigiPen (USA) Corporation. All rights reserved.", &colors[C_WHITE_DARK], TEXTALIGN_CENTER, TEXTALIGN_BOTTOM);
  multiSprite_setAlpha(entity_getComponent(copyright, COMP_MULTISPRITE), 0.0f);
  
  position.y = -48.0f;
  pressStart = genericText_create(menu, &position, "pressStart", "fonts/gothic/12", "Click anywhere or press any key to begin", &colors[C_WHITE_LIGHT], TEXTALIGN_CENTER, TEXTALIGN_TOP);
  multiSprite_setAlpha(entity_getComponent(pressStart, COMP_MULTISPRITE), 0.0f);
  
  position.y = 0.0f;
  genericSprite_createBlank(menu, &position, &dimensions, &colors[C_NAVY_LIGHT], "fader");
}

void startNewGame(GAME *game) {
  SPACE *simSpace = game_getSpace(game, "sim");
  SPACE *bgSpace = game_getSpace(game, "bg");
  SPACE *mgSpace = game_getSpace(game, "mg");
  SPACE *fgSpace = game_getSpace(game, "fg");
  SPACE *uiSpace = game_getSpace(game, "ui");

  VEC3 position;
  VEC4 color = { 1, 1, 1, 1 };
  VEC4 color2 = { 0 };
  VEC2 dimensions = { 40.0f, 20.0f };
  ENTITY *inspectBox;
  ENTITY *ent1;

  simSpace->active = false;
  bgSpace->active = false;
  mgSpace->active = false;
  fgSpace->active = false;
  //uiSpace->active = false;
  
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
  space_addEntity(uiSpace, arch_moneyInfo, "moneyInfo");

  
  // UI Bar
  vec3_set(&position, 0, 166, 0);
  vec2_set(&dimensions, 640, 29);
  genericSprite_createBlank(uiSpace, &position, &dimensions, &colors[C_TURQUOISE_LIGHT], "uiBar");
  
  // Menu Button
  vec3_set(&position, -306, 166, 0);
  createCustomButton(NULL, NULL, NULL, NULL, NULL, uiSpace, &position, "menuButton", 1, 1, true, "ui/menu_alt", NULL, &color, false, NULL, NULL, NULL, TEXTALIGN_CENTER, TEXTALIGN_CENTER);

  // Build Button
  vec3_set(&position, -271, 166, 0);
  ent1 = space_addEntityAtPosition(uiSpace, arch_uibuild, "build_button", &position);
  ((CDATA_UI_BUTTON *)entity_getComponentData(ent1, COMP_UI_BUTTON))->type = BUTTON_BUILD;
  ((CDATA_SPRITE *)entity_getComponentData(ent1, COMP_SPRITE))->source = "ui/build";

  // Management Button
  vec3_set(&position, -242, 166, 0);
  ent1 = space_addEntityAtPosition(uiSpace, arch_uimanage, "manage_button", &position);

  // Pause Button
  vec3_set(&position, -209, 166, 0);
  ent1 = space_addEntityAtPosition(uiSpace, arch_uibuild, "pauseButton", &position);
  ((CDATA_UI_BUTTON *)entity_getComponentData(ent1, COMP_UI_BUTTON))->type = BUTTON_PAUSE;
  ((CDATA_SPRITE *)entity_getComponentData(ent1, COMP_SPRITE))->source = "ui/play";

  // Speed Button
  vec3_set(&position, -180, 166, 0);
  ent1 = space_addEntityAtPosition(uiSpace, arch_uibuild, "speedButton", &position);
  ((CDATA_UI_BUTTON *)entity_getComponentData(ent1, COMP_UI_BUTTON))->type = BUTTON_SPEED;
  ((CDATA_SPRITE *)entity_getComponentData(ent1, COMP_SPRITE))->source = "ui/speed_slow";
  
  // create inspection screen
  vec3_set(&position, -267, 65, 0);
  vec2_set(&dimensions, 106, 195);
  inspectBox = space_addEntityAtPosition(uiSpace, arch_inspectionScreen, "inspection_screen", &position);
}
