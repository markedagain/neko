/******************************************************************************
Filename: main.c

Project Name: Game School Simulator 2015

Author: Adam Rezich

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include <Windows.h>
#include "../NekoEngine/game.h"
#include "../NekoEngine/space.h"
#include "../NekoEngine/neko.h"
#include "gameinitialize.h"

#pragma comment (lib, "../lib/neko.lib")

#if _CHECK_LEAKS
#pragma comment (lib, "C:\\Program Files (x86)\\Visual Leak Detector\\lib\\Win32\\vld.lib")
#include <vld.h>
#endif

int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR commandLine, int show) {
  GAME *game;
  
  game = game_create(instanceH, show);

  // create all spaces except main menu
  createSpaces(game);
  initializeEssentialSpaces(game);
  startNewGame(game);

  game_start(game);

  return 1;
}