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
  HWND hWnd;
  RECT rc;

  GAME *game = (GAME *)malloc(sizeof(GAME));
  sysInitInfo.mAppInstance    = instanceH;
  sysInitInfo.mShow        = show;
  sysInitInfo.mWinWidth      = 1280;
  sysInitInfo.mWinHeight      = 720;
  sysInitInfo.mCreateConsole    = 1;
  sysInitInfo.mMaxFrameRate    = 60;
  sysInitInfo.mpWinCallBack    = NULL;
  sysInitInfo.mClassStyle      = CS_HREDRAW | CS_VREDRAW;
  sysInitInfo.mWindowStyle    = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME;
  game->spaces = list_create();
  dict_init(&game->data.sprites);
  dict_init(&game->data.textures);
  dict_init(&game->data.sounds);
  game->destroyingEntities = list_create();
  game->destroyingSpaces = list_create();
  game->destroying = 0;
  game->window.width = 1280;
  game->window.height = 720;
  game->systems.time.framesPerSecond = DEFAULT_FPS;
  game->systems.time.frameRate = (double)1 / (double)DEFAULT_FPS;
  game->systems.time.dt = 0;
  input_initialize(&game->input);

  AESysInit(&sysInitInfo);
  hWnd = AESysGetWindowHandle();
  GetWindowRect(hWnd, &rc) ;
  SetWindowPos(hWnd, 0, (GetSystemMetrics(SM_CXSCREEN) - rc.right)/2, (GetSystemMetrics(SM_CYSCREEN) - rc.bottom)/2, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
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
    LIST_NODE *entityNode;

    if (space->entities->count == 0 || !space->active || space->destroying || (!space->visible && event == EV_DRAW)) {
      spaceNode = spaceNode->next;
      continue;
    }
    entityNode = space->entities->first;
    do {
      ENTITY *entity = (ENTITY *)(entityNode->data);
      unsigned int i = 0;
      unsigned int componentCount = vector_size(&entity->components);

      if (componentCount == 0 || entity->destroying) {
        entityNode = entityNode->next;
        continue;
      }
      do {
        COMPONENT *component = (COMPONENT *)vector_get(&entity->components, i);

        if (component->events.logicUpdate == NULL) {
          ++i;
          continue;
        }
        component_doEvent(component, event, data);
        ++i;
      }
      while (i < componentCount);
      entityNode = entityNode->next;
    }
    while (entityNode != NULL);
    spaceNode = spaceNode->next;
  }
  while (spaceNode != NULL);
}

void game_getInput(GAME *game) {
  input_update(&game->input, NULL);
}

void game_update(GAME *game) {
  EDATA_UPDATE updateEvent = { 0 };
  game_invokeEvent(game, EV_FRAMEUPDATE, &updateEvent);
  game_invokeEvent(game, EV_LOGICUPDATE, &updateEvent);
  game_cleanup(game);
}

void game_draw(GAME *game) {
  game_invokeEvent(game, EV_DRAW, NULL);
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
  while(gameRunning) {
    gameRunning = game_loop(game);
  }

  AESysExit();
  game_cleanup(game);
}

bool game_loop(GAME *game) {
  stopwatch_stop(&game->systems.time.stopwatch);
  game->systems.time.dt = stopwatch_delta(&game->systems.time.stopwatch);
  if (game->systems.time.dt <= game->systems.time.frameRate)
    return true;
  game_getInput(game);
  game_update(game);
  AEGfxStart();
  game_draw(game);
  AEGfxEnd();

  if (game->input.keyboard.keys[KEY_ESCAPE] == ISTATE_PRESSED)
    return false;
  return true;
}
