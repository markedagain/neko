/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdio.h>
#include <stdlib.h>
#include "../neko/game.h"
#include "../neko/space.h"
#include "../neko/entity.h"
#include "../neko/vector.h"
#include "../neko/linkedlist.h"

void ent_test(ENTITY *entity) {
  entity->id = 1337;
}

int main(int argc, char *argv[]) {
  GAME *game;
  ENTITY *player;
  SPACE *space;
  game = game_create();
  space = game_addSpace(game, "main");
  /*player = entity_create((SPACE *)(*(game->spaces->last)), ent_test, "test");
  */
  printf("Number of entities: %i\n", space->entities->count);
  player = entity_create(space, ent_test, "test");
  printf("Entity ID: %i\n", player->id);
  printf("Number of spaces in game: %i\n", game->spaces->count);
  printf("Number of entities: %i\n", space->entities->count);
  /*printf("Number of entities in current space: %i\n", (int)vector_size(&((SPACE *)(game->spaces->last))->entities));
  */return 0;
}
