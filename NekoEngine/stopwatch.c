/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "stopwatch.h"

void stopwatch_start(STOPWATCH *sw) {
  QueryPerformanceCounter(&sw->start);
}
void stopwatch_stop(STOPWATCH *sw) {
  QueryPerformanceCounter(&sw->stop);
}
double stopwatch_delta(STOPWATCH *sw) {
  LARGE_INTEGER time, frequency;
  time.QuadPart = sw->stop.QuadPart - sw->start.QuadPart;
  QueryPerformanceFrequency(&frequency);
  return ((double)time.QuadPart / (double)frequency.QuadPart);
}