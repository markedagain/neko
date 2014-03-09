/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "newsfeedlogic.h"
#include "../NekoEngine/generictext.h"
#include "../Nekoengine/spritetext.h"

char *pushStrings[STRINGS_LAST] = {
  "Welcome to: %s!",
  "%s %s has enrolled!",
  "%s %s has droped out!",
  "%s %s has graduated!",
  "Semester %i has started!",
  "Its %i, happy new year!"
};

void comp_newsfeedlogic_initialize(COMPONENT *self, void *event){
  CDATA_NEWSFEEDLOGIC *comData = (CDATA_NEWSFEEDLOGIC *)self->data;
}

void comp_newsfeedlogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_NEWSFEEDLOGIC *comData = (CDATA_NEWSFEEDLOGIC *)self->data;
}

void comp_newsfeedlogic_push(COMPONENT *ptr, char *string) {
  LIST_NODE *messageNode;
  char textBuffer[80];
  ENTITY *textSprite;
  SPACE *uiSpace = game_getSpace(ptr->owner->space->game, "ui");
  ENTITY *newsFeed = space_getEntity(uiSpace, "newsFeed");
  CDATA_NEWSFEEDLOGIC *comData = (CDATA_NEWSFEEDLOGIC *)entity_getComponentData(newsFeed, COMP_NEWSFEEDLOGIC);

  VEC3 pos = {-300, -120, 0};
  VEC4 color = {0, 0, 0, 1};
  textSprite = genericText_create(uiSpace, &pos, "textSprite", "fonts/gothic/12", textBuffer, &color, TEXTALIGN_LEFT, TEXTALIGN_MIDDLE);

  sprintf(textBuffer, string);
  genericText_setText(textSprite, textBuffer);
  list_insert_end(comData->messages, textSprite);

  messageNode = comData->messages->first;
  do {
    ENTITY *message = (ENTITY *) messageNode->data;
    CDATA_TRANSFORM *transform = (CDATA_TRANSFORM *)entity_getComponentData(message, COMP_TRANSFORM);
    VEC3 pos = {transform->translation.x, transform->translation.y + 10, transform->translation.z};
    transform->translation = pos;
    messageNode = messageNode->next;
  } while(messageNode != NULL);
}

void comp_newsfeedlogic_destroy(COMPONENT *self, void *event){
  CDATA_NEWSFEEDLOGIC *comData = (CDATA_NEWSFEEDLOGIC *)self->data;
  list_destroy(comData->messages);
}

void comp_newsfeedlogic(COMPONENT *self) {
  CDATA_NEWSFEEDLOGIC data = {0};
  data.messages = list_create();

  COMPONENT_INIT(self, COMP_NEWSFEEDLOGIC, data);
  self->events.logicUpdate = comp_newsfeedlogic_logicUpdate;
  self->events.initialize = comp_newsfeedlogic_initialize;
}