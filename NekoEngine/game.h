/******************************************************************************
Filename: game.h

Project Name: Game School Simulator 2015

Author: Adam Rezich

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __GAME_H__
#define __GAME_H__

#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include "neko.h"
#include "linkedlist.h"
#include "util.h"
#include "event.h"
#include "input.h"
#include "../AlphaEngine/AEEngine.h"
#include "data.h"
#include "stopwatch.h"
#include "sound.h"

typedef struct space_t SPACE;
typedef struct component_t COMPONENT;

typedef struct game_t {
  LIST *spaces;
  DATACONTAINER data;
  LIST *destroyingEntities;
  LIST *destroyingSpaces;
  struct {
    float aspectRatio;
    unsigned int width;
    unsigned int height;
  } dimensions;
  struct {
    unsigned int width;
    unsigned int height;
  } window;
  struct {
    unsigned int width;
    unsigned int height;
  } innerWindow;
  struct {
    struct {
      STOPWATCH stopwatch;
      STOPWATCH secondsStopwatch;
      STOPWATCH logicStopwatch;
      unsigned char framesPerSecond;
      unsigned short elapsedFrames;
      unsigned short currentFramesPerSecond;
      double frameRate;
      double dt;
      double dtFrame;
      double elapsed;
      double scale;
    } time;
    SOUNDSYSTEM sound;
  } systems;
  struct {
    struct {
      unsigned int width;
      unsigned int height;
      bool full;
    } screen;
    bool tutorial;
  } config;
  bool initialized;
  bool resized;
  bool fullscreen;
  INPUT_CONTAINER input;
  void (*resetFunction)(struct game_t *);
  unsigned char destroying;
} GAME;

NEKO_API GAME *game_create(HINSTANCE, int);
NEKO_API void game_destroy(GAME *);
NEKO_API SPACE *game_addSpace(GAME *, char *);
NEKO_API SPACE *game_getSpace(GAME *, char *);
void game_invokeEvent(GAME *, EVENT_TYPE, void *);
void game_tick(GAME *, bool logicUpdate);
void game_cleanup(GAME *);
NEKO_API void game_start(GAME *);
bool game_loop(GAME *);
void game_configLoad(GAME *);
NEKO_API void game_configSave(GAME *);
void game_configDefaults(GAME *);
NEKO_API void game_resize(GAME *, unsigned int, unsigned int, bool fullscreen);
LRESULT CALLBACK __game_processWindow(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
void __game_resize(GAME *game);

extern GAME *__game;

#endif
