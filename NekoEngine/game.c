/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "game.h"
#include "linkedlist.h"
#include "space.h"
#include "entity.h"
#include "component.h"
#include "event.h"
#include "util.h"
#include "../AlphaEngine/AEEngine.h"

GAME *game_create(HINSTANCE instanceH, int show) {
  AESysInitInfo sysInitInfo;

  GAME *game = (GAME *)malloc(sizeof(GAME));
  sysInitInfo.mAppInstance    = instanceH;
  sysInitInfo.mShow        = show;
  sysInitInfo.mWinWidth      = 1280;
  sysInitInfo.mWinHeight      = 720;
  sysInitInfo.mCreateConsole    = 1;
  sysInitInfo.mMaxFrameRate    = NEKO_DEFAULT_FPS;
  sysInitInfo.mpWinCallBack    = NULL;
  sysInitInfo.mClassStyle      = CS_HREDRAW | CS_VREDRAW;
  sysInitInfo.mWindowStyle    = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME;
  game->spaces = list_create();
  dataContainer_init(&game->data);
  game->destroyingEntities = list_create();
  game->destroyingSpaces = list_create();
  game->destroying = 0;
  game->window.width = 1280;
  game->window.height = 720;
  game->systems.time.framesPerSecond = NEKO_DEFAULT_FPS;
  game->systems.time.frameRate = 0;
  game->systems.time.dt = 0;
  game->systems.time.currentFramesPerSecond = 0;
  game->systems.time.elapsedFrames = 0;
  game->initialized = true;
  input_initialize(&game->input);

  AESysInit(&sysInitInfo);
  game_resize(game, 640, 360);
  SetCursor(NULL);
  AllocConsole();
  freopen("CONOUT$", "w", stdout);
  printf("Neko Engine loaded more or less successfully!\n");
  
  AESysReset();
  srand((unsigned int)time(NULL));

  return game;
}

SPACE *game_addSpace(GAME *game, char *name) {
  SPACE *space = space_create(name);
  space->game = game;
  space->node = list_insert_end(game->spaces, space);
  return space;
}

SPACE *game_getSpace(GAME *game, char *name) {
  LIST_NODE *node;

  if (game->spaces->count == 0)
    return NULL;
  node = game->spaces->first;
  while (node != NULL) {
    SPACE *space;
    space = (SPACE *)node->data;
    if (strcmp(name, space->name) == 0)
      return space;
    node = node->next;
  }
  return NULL;
}

void game_invokeEvent(GAME * game, EVENT_TYPE event, void *data) {
  LIST_NODE *spaceNode;

  if (game->spaces->count == 0)
    return;
  spaceNode = game->spaces->first;
  do {
    SPACE *space = (SPACE *)(spaceNode->data);
    if (space->entities->count == 0 || !space->active || space->destroying || (!space->visible && event == EV_DRAW)) {
      spaceNode = spaceNode->next;
      continue;
    }
    space_invokeEvent(space, event, data);
    spaceNode = spaceNode->next;
  }
  while (spaceNode != NULL);
}

void game_getInput(GAME *game) {
  input_update(&game->input, NULL);
}

void game_tick(GAME *game) {
  EDATA_UPDATE updateEvent = { 0 };
  LIST_NODE *spaceNode;
  if (game->spaces->count == 0)
    return;
  spaceNode = game->spaces->first;
  do {
    SPACE *space = (SPACE*)spaceNode->data;
    if (space->entities->count == 0 || !space->active || space->destroying) {
      spaceNode = spaceNode->next;
      continue;
    }
    space_tick(space, &updateEvent);
    spaceNode = spaceNode->next;
  }
  while (spaceNode != NULL);
  game_cleanup(game);
}

void game_cleanup(GAME *game) {
  while (game->destroyingEntities->count > 0) {
    ENTITY *entity = (ENTITY *)(game->destroyingEntities->last->data);
    __entity_destroy(entity);
    list_remove(game->destroyingEntities, game->destroyingEntities->last);
  }
  while (game->destroyingSpaces->count > 0) {
    SPACE *space = (SPACE *)(game->destroyingSpaces->last->data);
    __space_destroy(space);
    list_remove(game->destroyingSpaces, game->destroyingSpaces->last);
  }
}

void game_start(GAME *game) {
  bool gameRunning = true;
  game->systems.time.frameRate = (double)1 / (double)game->systems.time.framesPerSecond;

  AEGfxSetBackgroundColor(0.5f, 0.5f, 0.5f);
  AEGfxSetBlendMode(AE_GFX_BM_BLEND);

  stopwatch_start(&game->systems.time.stopwatch);
  stopwatch_start(&game->systems.time.secondsStopwatch);
  while(gameRunning) {
    gameRunning = game_loop(game);
  }

  AESysExit();
  game_destroy(game);
}

bool game_loop(GAME *game) {
  game->systems.time.elapsedFrames++;
  stopwatch_stop(&game->systems.time.secondsStopwatch);
  if (stopwatch_delta(&game->systems.time.secondsStopwatch) >= 1) {
    game->systems.time.currentFramesPerSecond = game->systems.time.elapsedFrames;
    game->systems.time.elapsedFrames = 0;
    stopwatch_start(&game->systems.time.secondsStopwatch);
  }
  stopwatch_stop(&game->systems.time.stopwatch);
  game->systems.time.dt = stopwatch_delta(&game->systems.time.stopwatch);
  if (game->systems.time.dt >= game->systems.time.frameRate) {
    game_getInput(game);
    game_tick(game);
  }

  AEGfxStart();
  game_invokeEvent(game, EV_DRAW, NULL);
  AEGfxEnd();

  if (game->input.keyboard.keys[KEY_ESCAPE] == ISTATE_PRESSED)
    return false;
  return true;
}

void game_destroy(GAME *game) {
  // TODO
}

void game_resize(GAME *game, unsigned int width, unsigned int height) {
  HWND hWnd = AESysGetWindowHandle();
  game->window.width = width;
  game->window.height = height;
  SetWindowPos(hWnd, HWND_TOPMOST, (GetSystemMetrics(SM_CXSCREEN) - game->window.width) / 2, (GetSystemMetrics(SM_CYSCREEN) - game->window.height) / 2, game->window.width, game->window.height, 0);
  if (game->initialized)
    AEGfxExit();
  AEGfxInit(game->window.width, game->window.height);
}
