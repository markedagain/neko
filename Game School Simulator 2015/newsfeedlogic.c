/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "newsfeedlogic.h"
#include "../NekoEngine/generictext.h"
#include "../Nekoengine/spritetext.h"

void comp_newsfeedlogic_initialize(COMPONENT *self, void *event){
  CDATA_NEWSFEEDLOGIC *comData = (CDATA_NEWSFEEDLOGIC *)self->data;
  VEC3 pos = {0, 0, 0};
  VEC4 color = {0, 0, 0, 1};
  sprintf(comData->textBuffer, "Hey, Hi, Hello");
  comData->textSprite = genericText_create(self->owner->space, &pos, "textSprite", "fonts/gothic/20", comData->textBuffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
  genericText_setText(comData->textSprite, comData->textBuffer);
}

void comp_newsfeedlogic_logicUpdate(COMPONENT *self, void *event) {
  
}



void comp_newsfeedlogic(COMPONENT *self) {
  CDATA_NEWSFEEDLOGIC data = {0};

  COMPONENT_INIT(self, COMP_NEWSFEEDLOGIC, data);
  self->events.logicUpdate = comp_newsfeedlogic_logicUpdate;
  self->events.initialize = comp_newsfeedlogic_initialize;
}