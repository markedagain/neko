/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdlib.h>
#include <string.h>
#include "space.h"
#include "game.h"
#include "linkedlist.h"

SPACE *space_create(GAME *game, char *name) {
  SPACE *space = malloc(sizeof(SPACE));
  space->entities = list_create();
  space->game = game;
  strcpy(space->name, name);
  space->active = 1;
  space->visible = 1;
  space->destroying = 0;
  return space;
}