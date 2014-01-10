/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __UTIL_H__
#define __UTIL_H__

#define TALLOC(typ,n) malloc(n*sizeof(typ))

unsigned long GraphicsColor(unsigned char, unsigned char, unsigned char, unsigned char);

typedef enum { false, true } bool;

#endif
