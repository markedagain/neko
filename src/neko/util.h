/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __UTIL_H__
#define __UTIL_H__

#define TALLOC(typ,n) malloc(n*sizeof(typ))

unsigned long GraphicsColor(unsigned char a, unsigned char r, unsigned char g, unsigned char b) {
  return (a << 24) + (r << 16) + (g << 8) + b;
}

#endif
