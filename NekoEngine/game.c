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

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 360

GAME *game_create(HINSTANCE instanceH, int show) {
  AESysInitInfo sysInitInfo;
  RECT windowRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };

  GAME *game = (GAME *)malloc(sizeof(GAME));
  AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME, FALSE);
  sysInitInfo.mAppInstance    = instanceH;
  sysInitInfo.mShow        = show;
  sysInitInfo.mWinWidth      = WINDOW_WIDTH;
  sysInitInfo.mWinHeight      = WINDOW_HEIGHT;
  sysInitInfo.mCreateConsole    = 1;
  sysInitInfo.mMaxFrameRate    = 0;
  sysInitInfo.mpWinCallBack    = __game_processWindow;
  sysInitInfo.mClassStyle      = CS_HREDRAW | CS_VREDRAW;
  sysInitInfo.mWindowStyle    = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
  game->spaces = list_create();
  dataContainer_init(&game->data);
  game->destroyingEntities = list_create();
  game->destroyingSpaces = list_create();
  game->destroying = 0;


  game->window.width = windowRect.right - windowRect.left;
  game->window.height = windowRect.bottom - windowRect.top;
  game->innerWindow.width = WINDOW_WIDTH;
  game->innerWindow.height = WINDOW_HEIGHT;

  game->dimensions.width = NEKO_DEFAULT_GAMEWIDTH;
  game->dimensions.height = NEKO_DEFAULT_GAMEHEIGHT;

  game->systems.time.framesPerSecond = NEKO_DEFAULT_FPS;
  game->systems.time.frameRate = 0;
  game->systems.time.dt = 0;
  game->systems.time.currentFramesPerSecond = 0;
  game->systems.time.elapsedFrames = 0;
  game->initialized = true;
  input_initialize(&game->input);

  AESysInit(&sysInitInfo);
  AESysSetWindowTitle(NEKO_GAMETITLE);
  game_resize(game, WINDOW_WIDTH, WINDOW_HEIGHT);
  
  AllocConsole();
  freopen("CONOUT$", "w", stdout);
  printf("Neko Engine loaded more or less successfully!\n");

  AESysReset();
  srand((unsigned int)time(NULL));

  data_loadAll(&game->data);

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
  SetCursor(NULL);
  game->systems.time.elapsedFrames++;
  stopwatch_stop(&game->systems.time.secondsStopwatch);
  if (stopwatch_delta(&game->systems.time.secondsStopwatch) >= 1) {
    game->systems.time.currentFramesPerSecond = game->systems.time.elapsedFrames;
    game->systems.time.elapsedFrames = 0;
    stopwatch_start(&game->systems.time.secondsStopwatch);
  }
  /*if (AESysGetWindowHandle() != GetActiveWindow())
    printf("AAAAA\n");*/

  stopwatch_stop(&game->systems.time.stopwatch);
  game->systems.time.dt = stopwatch_delta(&game->systems.time.stopwatch);
  if (game->systems.time.dt >= game->systems.time.frameRate) {
    stopwatch_start(&game->systems.time.stopwatch);
    if (AESysGetWindowHandle() == GetActiveWindow())
      game_getInput(game);
     if (game->input.keyboard.keys[KEY_ESCAPE] == ISTATE_PRESSED)
      return false;
    game_tick(game);
    //AEGfxStart();
    AESysFrameStart();
    game_invokeEvent(game, EV_DRAW, NULL);
    AESysFrameEnd();
    //AEGfxEnd();
  }

  return true;
}

void game_destroy(GAME *game) {
  // TODO
}

void game_resize(GAME *game, unsigned int width, unsigned int height) {
  HWND hWnd = AESysGetWindowHandle();
  RECT windowRect = { 0, 0, width, height };
  AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, FALSE);

  game->window.width = windowRect.right - windowRect.left;
  game->window.height = windowRect.bottom - windowRect.top;
  game->innerWindow.width = width;
  game->innerWindow.height = height;
  SetWindowPos(hWnd, HWND_TOP, (GetSystemMetrics(SM_CXSCREEN) - game->window.width) / 2, (GetSystemMetrics(SM_CYSCREEN) - game->window.height) / 2, game->window.width, game->window.height, SWP_NOZORDER);
  if (game->initialized)
    AEGfxExit();
  AEGfxInit(game->innerWindow.width, game->innerWindow.height);
}

LRESULT CALLBACK __game_processWindow(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
  //HDC dc; // device context
  //PAINTSTRUCT ps;
  //RECT rect;
  
  switch (msg) {

  case WM_CREATE:
    break;

  case WM_LBUTTONDOWN:
    break;

  case WM_MOUSEMOVE:
    break;

  /*case WM_PAINT:
    dc = BeginPaint(hwnd, &ps);
    EndPaint(hwnd, &ps);
    break;*/

  case WM_DESTROY:
    PostQuitMessage(0);
    break;

  case WM_KEYDOWN:
    break;

  case WM_MOVE:
    InvalidateRect(hwnd, NULL, FALSE);
    break;

  default:
    return DefWindowProc(hwnd, msg, wparam, lparam);
  }

  return 0;
}