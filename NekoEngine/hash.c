/******************************************************************************
Filename: hash.c

Project Name: Game School Simulator 2015

Author: Adam Rezich

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "hash.h"

unsigned int hash_string(const char *string) {
  unsigned int hash;
  int length;
  int i;

  length = strlen(string);
  for (hash = 0, i = 0; i < length; ++i) {
    hash += (unsigned)string[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return hash;

  /*
  for (hash = 0; *string != '\0'; ++string)
    hash = *string + 31 * hash;
  return hash;
  */
}