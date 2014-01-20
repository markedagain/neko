/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __HASH_H__
#define __HASH_H__

#include <string.h>
#include <stdio.h>
#include <stdint.h>

/* credit to http://lolengine.net/blog/2011/12/20/cpp-constant-string-hash */

#define STRLEN(s)   ((sizeof(s)/sizeof(s[0]))-1)
#define H1(s,i,x)   (x*65599u+(uint8_t)s[(i)<STRLEN(s)?STRLEN(s)-1-(i):STRLEN(s)])
#define H4(s,i,x)   H1(s,i,H1(s,i+1,H1(s,i+2,H1(s,i+3,x))))
#define H16(s,i,x)  H4(s,i,H4(s,i+4,H4(s,i+8,H4(s,i+12,x))))
#define H64(s,i,x)  H16(s,i,H16(s,i+16,H16(s,i+32,H16(s,i+48,x))))
#define H256(s,i,x) H64(s,i,H64(s,i+64,H64(s,i+128,H64(s,i+192,x))))

#define HASH(s)     ((uint32_t)(H256(s,0,0)^(H256(s,0,0)>>16)))

unsigned int hash_string(const char *string);

#endif
