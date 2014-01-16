/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <Windows.h>
#include "../NekoEngine/game.h"
#include "../NekoEngine/space.h"
#include "../NekoEngine/neko.h"
#include "test.h"
#include "cursor.h"
#include "gamemanager.h"
#include "util.h"

#pragma comment (lib, "../lib/neko.lib")

int gGameRunning = 1;
int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR commandLine, int show) {
  GAME *game;
  SPACE *mainSpace;
  SPACE *uiSpace;
  SPACE *simSpace;

  game = game_create(instanceH, show);
  mainSpace = game_addSpace(game, "main");
  space_addEntity(mainSpace, arch_test, "player");

  uiSpace = game_addSpace(game, "UI");
  space_addEntity(uiSpace, arch_cursor, "cursor");

  simSpace = game_addSpace(game, "simulation");
  simSpace->visible = false;
  space_addEntity(uiSpace, arch_gameManager, "gameManager");

  game_start(game);

  return 1;
}
