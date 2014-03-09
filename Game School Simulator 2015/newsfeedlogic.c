/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "newsfeedlogic.h"
#include "../NekoEngine/generictext.h"
#include "../Nekoengine/spritetext.h"

char *pushStrings[STRINGS_LAST] = {
  "Welcome to: %s!",
  "%s has enrolled!",
  "%s has droped out!",
  "%s has graduated!"
};

void comp_newsfeedlogic_initialize(COMPONENT *self, void *event){
  CDATA_NEWSFEEDLOGIC *comData = (CDATA_NEWSFEEDLOGIC *)self->data;
  VEC3 pos = {-300, -120, 0};
  VEC4 color = {0, 0, 0, 1};
  comData->textSprite = genericText_create(self->owner->space, &pos, "textSprite", "fonts/gothic/12", comData->textBuffer, &color, TEXTALIGN_LEFT, TEXTALIGN_MIDDLE);
}

void comp_newsfeedlogic_logicUpdate(COMPONENT *self, void *event) {
  
}

void comp_newsfeedlogic_push(COMPONENT *ptr, char *string){
  SPACE *uiSpace = game_getSpace(ptr->owner->space->game, "ui");
  ENTITY *newsFeed = space_getEntity(uiSpace, "newsFeed");
  CDATA_NEWSFEEDLOGIC *comData = (CDATA_NEWSFEEDLOGIC *)entity_getComponentData(newsFeed, COMP_NEWSFEEDLOGIC);
  sprintf(comData->textBuffer, string);
  genericText_setText(comData->textSprite, comData->textBuffer);
}

void comp_newsfeedlogic(COMPONENT *self) {
  CDATA_NEWSFEEDLOGIC data = {0};

  COMPONENT_INIT(self, COMP_NEWSFEEDLOGIC, data);
  self->events.logicUpdate = comp_newsfeedlogic_logicUpdate;
  self->events.initialize = comp_newsfeedlogic_initialize;
}