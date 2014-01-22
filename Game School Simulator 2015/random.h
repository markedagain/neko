/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include "../NekoEngine/data.h"

int randomIntRange(int a, int b) {
  int value, c;
  srand(time(NULL));
  
  if (a == 0) {
    value = rand() % b + 1;
    return value;
    }
  else {
    c = b - a;
    value = rand() % c + a + 1;
    return value;
    }
 }
 
float randomFloatRange(float a, float b) {
  srand(time(NULL));
  return ( (b - a) * ( (float)rand() / RAND_MAX) ) + a;
}
  
/* char* getLastName(GAME *game) {
  TEXTFILE *namefile = (TEXTFILE *) dict_get(&game->data.textfiles, "names/last");
  unsigned int numLastNames = vector_size(&namefile->lines);
  char *lastname = (char *)vector_get(&namefile->lines, randomIntRange(0, numLastNames));
  
  return lastname;
}

char* getFirstName(GAME *game, int a) {

  TEXTFILE *namefile;
  unsigned int numFirstNames;
  char *firstname;

  if (a == 0)
    namefile = (TEXTFILE *)dict_get(&game->data.textfiles, "names/first_male");
  else
    namefile = (TEXTFILE *)dict_get(&game->data.textfiles, "names/first_female");
  
  numFirstNames = vector_size(&namefile->lines);
  firstname = (char *)vector_get(&namefile->lines, randomIntRange(0, numFirstNames));
  return firstname;
}

*/
#endif