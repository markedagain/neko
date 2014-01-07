/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdio.h>
#include <stdlib.h>
#include "../neko/game.h"
#include "../neko/space.h"
#include "../neko/entity.h"
#include "../neko/linkedlist.h"
#include "../neko/vector.h"
#include "archetypes/player.h"
#include "../neko/components/transform.h"
#include "../neko/components/sprite.h"
#include "../neko/hash.h"
#include "../neko/event.h"

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
  printf("COMP_TRANSFORM's id: %u\n", COMP_TRANSFORM);
  printf("COMP_SPRITE:'s id %u\n", COMP_SPRITE);
  printf("Entity ID: %u\n", player->id);
  printf("Number of spaces in game: %i\n", game->spaces->count);
  printf("Number of entities: %i\n", space->entities->count);
  printf("%s's parent: %s\n", weapon->name, weapon->parent->name);
  printf("%s's x-position: %f\n", player->name, ((CDATA_TRANSFORM *)entity_getComponentData(player, COMP_TRANSFORM))->translation.x);
  printf("%s's sprite source: %s\n", player->name, ((CDATA_SPRITE *)entity_getComponentData(player, COMP_SPRITE))->source);
  game_update(game);
  return 0;
}
