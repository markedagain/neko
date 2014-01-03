/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdio.h>
#include <stdlib.h>
#include "../neko/game.h"
#include "../neko/space.h"
#include "../neko/entity.h"
#include "../neko/vector.h"
#include "../neko/linkedlist.h"
#include "archetypes/player.h"

int main(int argc, char *argv[]) {
  GAME *game;
  ENTITY *player;
  ENTITY *weapon;
  SPACE *space;
  game = game_create();
  space = game_addSpace(game, "main");
  printf("Number of entities: %i\n", space->entities->count);
  player = entity_create(space, arch_player, "player");
  weapon = entity_create(space, arch_player, "weapon");
  entity_attach(weapon, player);
  printf("Entity ID: %i\n", player->id);
  printf("Number of spaces in game: %i\n", game->spaces->count);
  printf("Number of entities: %i\n", space->entities->count);
  printf("%s's parent: %s\n", weapon->name, weapon->parent->name);
  return 0;
}
