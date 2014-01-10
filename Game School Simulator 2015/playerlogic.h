/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_PLAYERLOGIC_H__
#define __COMP_PLAYERLOGIC_H__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"
#include "../AlphaEngine/AEEngine.h"

#define COMP_PLAYERLOGIC HASH("COMP_PLAYERLOGIC")

void comp_playerLogic_logicUpdate(COMPONENT *, void *);
void comp_playerLogic(COMPONENT *);


#endif