/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdlib.h>
#include "game.h"
#include "linkedlist.h"
#include "space.h"

GAME *game_create(void) {
  GAME *game = malloc(sizeof(GAME));
  game->spaces = list_create();
  game->destroying = 0;
  return game;
}

SPACE *game_addSpace(GAME *game, char *name) {
  return (SPACE *)(list_insert_beginning(game->spaces, space_create(game, name)));
}
