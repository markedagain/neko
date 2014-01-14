/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "data.h"
#include "pak.h"

void *data_load(char *filename, int *filesize) {
  bool existsOutside, pakExists;
  // First check the data directory
  existsOutside = file_exists(filename);

  // If it's in the data directory, load it
  if (existsOutside) {
    file_load(filename);
  }

  // If it's not in the data directory, check to see if there's any pak files
  pakExists = file_exists("pak0.pak");

  // If there is a pak file present, look up the requested file in it and return it if it exists

  // If the file does exist, load it

  // If the file doesn't exist in the pak, we're out of options, return
  return NULL;

  // If there's no pak files present, return
  return NULL;
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