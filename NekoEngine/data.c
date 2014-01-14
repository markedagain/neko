/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "data.h"
#include "pak.h"

void *data_load(char *filename, int *filesize) {
}

bool file_exists(char *filename) {
  TCHAR *file = (TCHAR *)filename;
  WIN32_FIND_DATA FindFileData;
  HANDLE handle = FindFirstFile(file, &FindFileData);
  int found = handle != INVALID_HANDLE_VALUE;
  if (found) {
    //FindClose(&handle); this will crash
    FindClose(handle);
  }
  return found;
}

void *file_load(char *filename) {
  return NULL;
}