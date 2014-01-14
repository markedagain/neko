/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <Windows.h>
#include "../NekoEngine/game.h"
#include "../NekoEngine/space.h"
#include "test.h"
#include "../NekoEngine/neko.h"

#pragma comment (lib, "../lib/neko.lib")

int gGameRunning = 1;
int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR commandLine, int show) {
  GAME *game;
  SPACE *space;

  game = game_create(instanceH, show);
  space = game_addSpace(game, "main");
  space_addEntity(space, arch_test, "player");

  game_start(game);

  return 1;
}
