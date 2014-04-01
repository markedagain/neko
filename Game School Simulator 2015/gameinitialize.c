/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "gameinitialize.h"
#include "tutorial.h"

void startGame(GAME *game) {
  (game_getSpace(game, "sim"))->active = true;
  (game_getSpace(game, "bg"))->active = true;
  (game_getSpace(game, "mg"))->active = true;
  (game_getSpace(game, "fg"))->active = true;
  sound_playSong(&game->systems.sound, "03");
#if TUTORIAL
  createFirstTutorial(game_getSpace(game, "ui"));
#endif
}
