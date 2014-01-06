/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdlib.h>
#include "event.h"

void eventcontainer_initialize(EVENTCONTAINER *container) {
  container->initialize = NULL;
  container->destroy = NULL;
  container->logicUpdate = NULL;
  container->frameUpdate = NULL;
}
