/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __ARCH_TEST_H__
#define __ARCH_TEST_H__
// These previous two lines and the #endif at the end make sure that this is only ever included once

// You pretty much always need to include these in archetypes
#include "../NekoEngine/entity.h"
#include "../NekoEngine/hash.h"

// This defines the archetype identifier. Just copy this format every time, but change both
// instances of ARCH_TEST to ARCH_WHATEVERYOUWANT
#define ARCH_TEST HASH("ARCH_TEST")

// This is the function prototype for the function that sets up the archetype. This should be the
// only thing you need.
void arch_test(ENTITY *);

#endif