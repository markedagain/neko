/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "namescreenlogic.h"
#include "sprite.h"
#include "genericsprite.h"
#include "generictext.h"
#include "schoollogic.h"
#include "colors.h"
#include "sound.h"
#include "gameinitialize.h"
#include "menuscreenlogic.h"

#define MAX_NAME 30

void comp_nameScreenLogic_logicUpdate(COMPONENT *self, void *event) {
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  CDATA_NAMESCREEN *data = (CDATA_NAMESCREEN *)self->data;

  if (input->keyboard.keys[KEY_BACKSPACE] == ISTATE_PRESSED) {
    int count = strlen(data->name);
    // if there is stuff in the string, backspace it
    if (count > 0)
      data->name[count - 1] = 0;
  }

  // don't do anything if backspace is held down
  else if (input->keyboard.keys[KEY_BACKSPACE] == ISTATE_DOWN)
  {}

  // if enter, store the string
  else if (input->keyboard.keys[KEY_ENTER] == ISTATE_PRESSED) {
    SPACE *sim = game_getSpace(self->owner->space->game, "sim");
    CDATA_SCHOOLLOGIC *schoolData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(space_getEntity(sim, "gameManager"), COMP_SCHOOLLOGIC);
  
    strcpy(schoolData->schoolName, data->name);
    schoolData->counter = 1;
    space_destroy(self->owner->space);
    startGame(self->owner->space->game);
    //(game_getSpace(self->owner->space->game, "ui"))->active = true;
  }


  // if just normal ascii input
  else {
    int length = strlen(data->name);
    int inputLength = strlen(input->keyboard.ascii);

    // if there's enough space for everything
    if (length + inputLength <= MAX_NAME)
      strcat(data->name, input->keyboard.ascii);

    // if user types too damn fast
    else if (MAX_NAME - length > 0) {
      int originalLength = strlen(data->name);
      int numNewChars = MAX_NAME - length;
      int i;
      for (i = 0; i < numNewChars; ++i) {
        data->name[originalLength + i] = input->keyboard.ascii[i];
      }
    }
  }
  genericText_setText(data->displayText, data->name);
}

void comp_nameScreenLogic(COMPONENT *self) {
  CDATA_NAMESCREEN data = { 0 };
  COMPONENT_INIT(self, COMP_NAMESCREENLOGIC, data);
  self->events.logicUpdate = comp_nameScreenLogic_logicUpdate;
  self->events.initialize = comp_nameScreenLogic_initialize;
}

void comp_nameScreenLogic_initialize(COMPONENT *self, void *event) {
  VEC3 position = { 0 };
  VEC4 color = { 0.7f, 0.7f, 0.7f, 0.7f, };
  CDATA_NAMESCREEN *data = (CDATA_NAMESCREEN *)self->data;
  ENTITY *menuScreen = space_getEntity(self->owner->space, "menuScreen");
  CDATA_MENUSCREENLOGIC *menuData = (CDATA_MENUSCREENLOGIC *)entity_getComponentData(menuScreen, COMP_MENUSCREENLOGIC);

  al_clear(&menuData->actions);

  entity_destroy(space_getEntity(self->owner->space, "newGameButton"));
  entity_destroy(space_getEntity(self->owner->space, "optionsButton"));
  entity_destroy(space_getEntity(self->owner->space, "quitButton"));
  entity_destroy(space_getEntity(self->owner->space, "logo"));
  entity_destroy(space_getEntity(self->owner->space, "titleContainer"));
  entity_destroy(space_getEntity(self->owner->space, "copyright"));

  vec4_set(&color, 0, 0, 0, 1.0f);
  data->displayText = genericText_create(self->owner->space, &position, "inputNameText", "fonts/gothic/12", "", &colors[C_WHITE_LIGHT], TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);

  vec3_set(&position, 0, 20.0f, 0);
  genericText_create(self->owner->space, &position, "inputNameText", "fonts/gothic/12", "Enter the name of your school:", &colors[C_WHITE_DARK], TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
}
