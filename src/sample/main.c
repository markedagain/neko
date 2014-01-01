/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdio.h>
#include <stdlib.h>
#include "../neko/game.h"
#include "../neko/space.h"

int main(int argc, char *argv[]) {
  GAME *game;
  game = game_create();
  game_addSpace(game, "main");
  printf("test\n");
  return 0;
}
