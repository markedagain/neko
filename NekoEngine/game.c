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
#define FULLSCREEN false

GAME *__game = NULL; // UGHHHHHHH
WINDOWPLACEMENT g_wpPrev = { sizeof(g_wpPrev) }; // UGHHHHHHHHHHHHHHhhhhhhh

GAME *game_create(HINSTANCE instanceH, int show) {
  AESysInitInfo sysInitInfo;
  RECT windowRect = { 0 };

  GAME *game = (GAME *)malloc(sizeof(GAME));

  game_configLoad(game);
  windowRect.right = game->config.screen.width;
  windowRect.bottom = game->config.screen.height;

  AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME, FALSE);
  sysInitInfo.mAppInstance    = instanceH;
  sysInitInfo.mShow        = show;
  sysInitInfo.mWinWidth      = game->config.screen.width;
  sysInitInfo.mWinHeight      = game->config.screen.height;
#ifdef _DEBUG
  sysInitInfo.mCreateConsole    = 1;
#endif
#ifndef _DEBUG
  sysInitInfo.mCreateConsole = 0;
#endif
  sysInitInfo.mMaxFrameRate    = NEKO_DEFAULT_FPS - 1; // -1 to make Alpha not be dumb (?)
  sysInitInfo.mpWinCallBack    = __game_processWindow;
  sysInitInfo.mClassStyle      = CS_HREDRAW | CS_VREDRAW;
  sysInitInfo.mWindowStyle    = WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME;
  game->spaces = list_create();
  dataContainer_init(&game->data);
  game->destroyingEntities = list_create();
  game->destroyingSpaces = list_create();
  game->destroying = 0;
  game->resized = false;
  game->fullscreen = false;


  game->window.width = windowRect.right - windowRect.left;
  game->window.height = windowRect.bottom - windowRect.top;
  game->innerWindow.width = game->config.screen.width;
  game->innerWindow.height = game->config.screen.height;

  game->dimensions.width = NEKO_DEFAULT_GAMEWIDTH;
  game->dimensions.height = NEKO_DEFAULT_GAMEHEIGHT;
  game->dimensions.aspectRatio = (float)game->dimensions.width / (float)game->dimensions.height;

  game->systems.time.framesPerSecond = NEKO_DEFAULT_FPS;
  game->systems.time.frameRate = 0;
  game->systems.time.dt = 0;
  game->systems.time.currentFramesPerSecond = 0;
  game->systems.time.elapsedFrames = 0;
  game->systems.time.elapsed = 0;
  game->systems.time.scale = 1.0;
  game->initialized = true;
  input_initialize(&game->input);
  sound_initialize(&game->systems.sound, &game->data.sounds);

  AESysInit(&sysInitInfo);
  AESysSetWindowTitle(NEKO_GAMETITLE);
  game_resize(game, game->config.screen.width, game->config.screen.height, game->config.screen.full);
  
#ifdef _DEBUG
  AllocConsole();
  freopen("CONOUT$", "w", stdout);
  printf("Neko Engine loaded more or less successfully!\n");
#endif

  AESysReset();
  srand((unsigned int)time(NULL));

  data_loadAll(&game->data, &game->systems.sound);


  __game = game;
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
    if (/*space->entities->count == 0 || */!space->active || space->destroying || (!space->visible && event == EV_DRAW)) {
      spaceNode = spaceNode->next;
      continue;
    }
    space_invokeEvent(space, event, data);
    spaceNode = spaceNode->next;
  }
  while (spaceNode != NULL);
}

void game_tick(GAME *game, bool logicUpdate) {
  EDATA_UPDATE frameUpdateEvent = { 0 };
  EDATA_UPDATE logicUpdateEvent = { 0 };
  LIST_NODE *spaceNode;

  frameUpdateEvent.dt = stopwatch_delta(&game->systems.time.stopwatch);
  logicUpdateEvent.dt = game->systems.time.dt;

  if (game->spaces->count == 0)
    return;

  spaceNode = game->spaces->last;
  while (spaceNode != NULL) {
    SPACE *space = (SPACE*)spaceNode->data;
    if (!space->active || space->destroying) {
      spaceNode = spaceNode->prev;
      continue;
    }
    space_tick(space, &frameUpdateEvent, &logicUpdateEvent, logicUpdate);
    spaceNode = spaceNode->prev;
  }
  game_cleanup(game);

  input_reset_frame(&game->input);
  //if (logicUpdate || game->systems.time.scale == 0)
  input_reset_logic(&game->input);
}

void game_cleanup(GAME *game) {
  while (game->destroyingEntities->first) {
    ENTITY *entity = (ENTITY *)(game->destroyingEntities->last->data);
    __entity_destroy(entity);
    list_remove(game->destroyingEntities, game->destroyingEntities->last);
  }
  while (game->destroyingSpaces->first) {
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
  stopwatch_startAt(&game->systems.time.secondsStopwatch, &game->systems.time.stopwatch.start);
  stopwatch_startAt(&game->systems.time.logicStopwatch, &game->systems.time.stopwatch.start);

  while(gameRunning) {
    gameRunning = game_loop(game);
  }

  game_destroy(game);
}

bool game_loop(GAME *game) {
  RECT clientRect;
  POINT cursorPos;
  bool logicUpdate;
  double deltaTime;

  stopwatch_stop(&game->systems.time.stopwatch);

  GetClientRect(AESysGetWindowHandle(), &clientRect);
  GetCursorPos(&cursorPos);
  ScreenToClient(AESysGetWindowHandle(), &cursorPos);
  if (cursorPos.x >= 0 && cursorPos.x <= clientRect.right && cursorPos.y >= 0 && cursorPos.y <= clientRect.bottom) {
    SetCursor(NULL);
    ShowCursor(FALSE);
  }
  /*else
    ShowCursor(TRUE);*/
  game->systems.time.elapsedFrames++;
  stopwatch_stop(&game->systems.time.secondsStopwatch);
  if (stopwatch_delta(&game->systems.time.secondsStopwatch) >= 1) {
    game->systems.time.currentFramesPerSecond = game->systems.time.elapsedFrames;
    game->systems.time.elapsedFrames = 0;
    stopwatch_start(&game->systems.time.secondsStopwatch);
  }
  /*if (AESysGetWindowHandle() != GetActiveWindow())
    printf("AAAAA\n");*/

  deltaTime = stopwatch_delta(&game->systems.time.stopwatch);
  if (deltaTime >= game->systems.time.frameRate) {
    game->systems.time.elapsed += deltaTime;
    stopwatch_lap(&game->systems.time.stopwatch);
    if (AESysGetWindowHandle() == GetActiveWindow()) {
      input_update(&game->input, NULL);
    }
    else
      input_unlockMouse(&game->input);
    if (game->input.keyboard.keys[KEY_ESCAPE] == ISTATE_PRESSED)
      return false;
    sound_update(&game->systems.sound);
    stopwatch_stopAt(&game->systems.time.logicStopwatch, &game->systems.time.stopwatch.start);
    game->systems.time.dt = stopwatch_delta(&game->systems.time.logicStopwatch);
    logicUpdate = game->systems.time.scale != 0 && game->systems.time.dt >= game->systems.time.frameRate / game->systems.time.scale;
    if (logicUpdate)
      stopwatch_lap(&game->systems.time.logicStopwatch);
    game_tick(game, logicUpdate);
    AESysFrameStart();
    game_invokeEvent(game, EV_DRAW, NULL);
    AESysFrameEnd();
    if (game->resized) {
      game->resized = false;
      __game_resize(game);
    }
  }

  return !game->destroying;
}

void game_destroy(GAME *game) {
  LIST_NODE *node;
  //int i;
  // TODO

  node = game->spaces->first;
  while (node) {
    SPACE *space = (SPACE *)node->data;
    space_destroy(space);
    node = node->next;
  }

  game_cleanup(game);


  list_destroy(game->spaces);
  list_destroy(game->destroyingEntities);
  list_destroy(game->destroyingSpaces);

  data_destroy(&game->data);

  sound_destroy(&game->systems.sound);
  free(game);
  AESysExit();
}

void game_resize(GAME *game, unsigned int width, unsigned int height, bool fullscreen) {
  HWND hWnd = AESysGetWindowHandle();
  RECT windowRect = { 0, 0, width, height };
  DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

  if (fullscreen) {
    if (dwStyle & WS_OVERLAPPEDWINDOW) {
      MONITORINFO mi = { sizeof(mi) };
      if (GetWindowPlacement(hWnd, &g_wpPrev) &&
        GetMonitorInfo(MonitorFromWindow(hWnd, MONITOR_DEFAULTTOPRIMARY), &mi)) {
          SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
          SetWindowPos(hWnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top,
            mi.rcMonitor.right - mi.rcMonitor.left,
            mi.rcMonitor.bottom - mi.rcMonitor.top,
            SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
          game->innerWindow.width = mi.rcMonitor.right - mi.rcMonitor.left;
          game->innerWindow.height = mi.rcMonitor.bottom - mi.rcMonitor.top;
          game->window.width = game->innerWindow.width;
          game->window.height = game->innerWindow.height;
          game->fullscreen = true;
      }
    }
  }
  else {
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME, FALSE);

    game->window.width = windowRect.right - windowRect.left;
    game->window.height = windowRect.bottom - windowRect.top;
    game->innerWindow.width = width;
    game->innerWindow.height = height;
    SetWindowPos(hWnd, HWND_TOP, (GetSystemMetrics(SM_CXSCREEN) - game->window.width) / 2, (GetSystemMetrics(SM_CYSCREEN) - game->window.height) / 2, game->window.width, game->window.height, SWP_NOZORDER);
    game->fullscreen = false;
  }
  if (game->initialized)
    AEGfxExit(); // TODO: Replace with better?
  AEGfxInit(game->innerWindow.width, game->innerWindow.height);
}

void game_configLoad(GAME *game) {
  VECTOR lines;
  char filename[128] = { 0 };
  vector_init(&lines);
  file_getCurrentDirectory(filename);
  strcat(filename, "\\user.config");
  file_readText(&lines, filename);
  if (!vector_size(&lines)) {
    game_configDefaults(game);
    game_configSave(game);
  }
  else {
    game->config.screen.width = atoi((char *)vector_get(&lines, 0));
    game->config.screen.height = atoi((char *)vector_get(&lines, 1));
    game->config.screen.full = atoi((char *)vector_get(&lines, 2));
    game->config.tutorial = atoi((char *)vector_get(&lines, 3));
  }
  vector_destroy(&lines);
}
void game_configSave(GAME *game) {
  char filename[128] = { 0 };
  FILE *fp;
  file_getCurrentDirectory(filename);
  strcat(filename, "\\user.config");
  fp = fopen(filename, "wb");
  if (fp) {
    fprintf(fp, "%i\n", (int)game->config.screen.width);
    fprintf(fp, "%i\n", (int)game->config.screen.height);
    fprintf(fp, "%i\n", (int)game->config.screen.full);
    fprintf(fp, "%i\n", (int)game->config.tutorial);
    fclose(fp);
  }
}

void game_configDefaults(GAME *game) {
  game->config.screen.width = 640;
  game->config.screen.height = 360;
  game->config.screen.full = true;
  game->config.tutorial = true;
}

void __game_resize(GAME *game) {
  RECT windowRect = { 0, 0 };
  RECT clientRect = { 0, 0 };
  GetWindowRect(AESysGetWindowHandle(), &windowRect);
  GetClientRect(AESysGetWindowHandle(), &clientRect);
  game->window.width = windowRect.right - windowRect.left;
  game->window.height = windowRect.bottom - windowRect.top;
  //game->innerWindow.width = clientRect.right - clientRect.left;
  //game->innerWindow.height = clientRect.bottom - clientRect.top;

  if (game->initialized)
    AEGfxExit(); // TODO: Replace with better?
  AEGfxInit(game->innerWindow.width, game->innerWindow.height);
}

LRESULT CALLBACK __game_processWindow(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
  //HDC dc; // device context
  //PAINTSTRUCT ps;
  //RECT rect;
  int i;
  
  switch (msg) {

  case WM_CREATE:
    break;
#define INPUT_FRAMEBUFFER 1
  case WM_LBUTTONDOWN:
    __game->input.mouse.buffer[MBUTTON_LEFT] = INPUT_FRAMEBUFFER;
    break;

  case WM_LBUTTONUP:
    __game->input.mouse.buffer[MBUTTON_LEFT] = -INPUT_FRAMEBUFFER;
    break;

  case WM_RBUTTONDOWN:
    __game->input.mouse.buffer[MBUTTON_RIGHT] = INPUT_FRAMEBUFFER;
    break;

  case WM_RBUTTONUP:
    __game->input.mouse.buffer[MBUTTON_RIGHT] = -INPUT_FRAMEBUFFER;
    break;

  case WM_MBUTTONDOWN:
    __game->input.mouse.buffer[MBUTTON_MIDDLE] = INPUT_FRAMEBUFFER;
    break;

  case WM_MBUTTONUP:
    __game->input.mouse.buffer[MBUTTON_MIDDLE] = -INPUT_FRAMEBUFFER;
    break;

  case WM_MOUSEMOVE:
    break;

  case WM_CHAR:
    if ((int)wparam < 32 && (int)wparam >= 127)
      break;
    i = 0;
    while (__game->input.keyboard.ascii[i] != 0 && i < INPUT_MAX_ASCII_KEYS_PER_FRAME)
      ++i;
    if (i >= INPUT_MAX_ASCII_KEYS_PER_FRAME)
      break;
    __game->input.keyboard.ascii[i] = (char)wparam;
    break;

  /*case WM_PAINT:
    dc = BeginPaint(hwnd, &ps);
    EndPaint(hwnd, &ps);
    break;*/

  case WM_DESTROY:
    __game->destroying = true;
    PostQuitMessage(0);
    break;

  case WM_KEYDOWN:
    __game->input.keyboard.anyKey = true;
    break;

  case WM_MOVE:
    //InvalidateRect(hwnd, NULL, FALSE);
    break;

  case WM_SIZE:
    if (__game != NULL)
      //__game_resize(__game);
      __game->resized = true;
    break;

  case WM_MOUSEWHEEL:
    if (__game != NULL)
      if (AESysGetWindowHandle() == GetActiveWindow())
        __game->input.mouse.wheel.delta += GET_WHEEL_DELTA_WPARAM(wparam) / WHEEL_DELTA;
    break;

  default:
    return DefWindowProc(hwnd, msg, wparam, lparam);
  }

  return 0;
}