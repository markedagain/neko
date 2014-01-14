/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "neko.h"
#include "util.h"

NEKO_API void *data_load(char *, int *);
bool file_exists(char *);
void *file_load(char *);