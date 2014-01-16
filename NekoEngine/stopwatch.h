/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __STOPWATCH_H__
#define __STOPWATCH_H__

#include <Windows.h>

typedef struct stopwatch_t {
  LARGE_INTEGER start;
  LARGE_INTEGER stop;
} STOPWATCH;

void stopwatch_start(STOPWATCH *);
void stopwatch_stop(STOPWATCH *);
double stopwatch_delta(STOPWATCH *);

#endif