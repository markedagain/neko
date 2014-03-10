/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "newsfeedlogic.h"
#include "../NekoEngine/generictext.h"
#include "../Nekoengine/spritetext.h"
#include "easing.h"

char *pushStrings[STRINGS_LAST] = {
  "Welcome to: %s!",
  "%i students have enrolled!",
  "%i students have dropped out!",
  "%i students have graduated!",
  "Semester %i has started!",
  "Its %i, happy new year!"
};

void comp_newsfeedlogic_initialize(COMPONENT *self, void *event) {
  int i;
  char textBuffer[80] = {0};
  SPACE *uiSpace = game_getSpace(self->owner->space->game, "ui");
  CDATA_NEWSFEEDLOGIC *comData = (CDATA_NEWSFEEDLOGIC *)self->data;
  VEC3 pos = {-300, -130, 0};
  VEC4 color = {0, 0, 0, 1};

  for(i = 0; i < 5; i++) {
    pos.y += 10;
    comData->lines[i] = genericText_create(uiSpace, &pos, "textSprite", "fonts/gothic/12", textBuffer, &color, TEXTALIGN_LEFT, TEXTALIGN_MIDDLE);
  }

  comData->fadeOutStartTime = (float)self->owner->space->game->systems.time.elapsed;
}

void comp_newsfeedlogic_logicUpdate(COMPONENT *self, void *event) {
  int i;
  CDATA_NEWSFEEDLOGIC *comData = (CDATA_NEWSFEEDLOGIC *)self->data;
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;

  comData->delayTime += updateEvent->dt;

  if(comData->delayTime > 3.0f) {
    // FADE OUT
    for(i = 0; i < 5; i++) {
      COMPONENT *spriteText = (COMPONENT *) entity_getComponent(comData->lines[i], COMP_MULTISPRITE);
      float timeChange = (float)self->owner->space->game->systems.time.elapsed - (float)comData->fadeOutStartTime;
      if(timeChange <= 3.0f)
        multiSprite_setAlpha(spriteText, e_quad_in((float)self->owner->space->game->systems.time.elapsed - (float)comData->fadeOutStartTime, 1.0f, -1.0f, 3.0f));
    }
  }
}

void comp_newsfeedlogic_push(COMPONENT *ptr, char *string) {
  //LIST_NODE *messageNode;
  char textBuffer[80];
  SPACE *uiSpace = game_getSpace(ptr->owner->space->game, "ui");
  ENTITY *newsFeed = space_getEntity(uiSpace, "newsFeed");
  CDATA_NEWSFEEDLOGIC *comData = (CDATA_NEWSFEEDLOGIC *)entity_getComponentData(newsFeed, COMP_NEWSFEEDLOGIC);

  
  if(comData->messages->count < 5) {
    int i;

    if(comData->messages->count != 0) {
      for(i = 0; i < comData->messages->count; i++) {
        CDATA_SPRITETEXT *spriteText = (CDATA_SPRITETEXT *) entity_getComponentData(comData->lines[comData->messages->count - i - 1], COMP_SPRITETEXT);
        //COMPONENT *multiSprite = (COMPONENT *) entity_getComponent(comData->lines[comData->messages->count - i - 1], COMP_MULTISPRITE);
        genericText_setText(comData->lines[comData->messages->count - i], spriteText->text);
        //multiSprite_setAlpha(multiSprite, 1);
      }
    }
  }
  else {
    int i;
    for(i = 0; i < 4; i++) {
      CDATA_SPRITETEXT *spriteText = (CDATA_SPRITETEXT *) entity_getComponentData(comData->lines[4 - i - 1], COMP_SPRITETEXT);
      //COMPONENT *multiSprite = (COMPONENT *) entity_getComponent(comData->lines[4 - i - 1], COMP_MULTISPRITE);
      genericText_setText(comData->lines[4 - i], spriteText->text);
      //multiSprite_setAlpha(multiSprite, 1);
    }
  }

  // Place the message in its sprite
  sprintf(textBuffer, string);
  genericText_setText(comData->lines[0], textBuffer);
  list_insert_end(comData->messages, textBuffer);
  {
    COMPONENT *multiSprite = (COMPONENT *) entity_getComponent(comData->lines[0], COMP_MULTISPRITE);
    multiSprite_setAlpha(multiSprite, 1);
  }

  comData->fadeOutStartTime = (float)ptr->owner->space->game->systems.time.elapsed + 3;
  comData->delayTime = 0;
}

void comp_newsfeedlogic_destroy(COMPONENT *self, void *event){
  CDATA_NEWSFEEDLOGIC *comData = (CDATA_NEWSFEEDLOGIC *)self->data;
  list_destroy(comData->messages);
}

void comp_newsfeedlogic(COMPONENT *self) {
  CDATA_NEWSFEEDLOGIC data = {0};
  data.messages = list_create();
  data.delayTime = 0.0;

  COMPONENT_INIT(self, COMP_NEWSFEEDLOGIC, data);
  self->events.initialize = comp_newsfeedlogic_initialize;
  self->events.logicUpdate = comp_newsfeedlogic_logicUpdate;
}