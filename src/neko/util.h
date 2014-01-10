/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __UTIL_H__
#define __UTIL_H__

#define TALLOC(typ,n) malloc(n*sizeof(typ))

#define M_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062

unsigned long GraphicsColor(unsigned char, unsigned char, unsigned char, unsigned char);

#ifndef __INTELLISENSE__
typedef enum { false, true } bool;
#endif

#endif
