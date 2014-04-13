/******************************************************************************
Filename: gameinitialize.h

Project Name: Game School Simulator 2015

Author: Samuel Valdez

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __GAMEINITIALIZE_H__
#define __GAMEINITIALIZE_H__

#include "game.h"
#include "entity.h"

void startGame(GAME *game);
void createSpaces(GAME *game);
void createMainMenu(GAME *game);
void startNewGame(GAME *game);
void initializeEssentialSpaces(GAME *game);
void setInspectText(GAME *game);

#endif