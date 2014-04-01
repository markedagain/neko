/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "tutorial.h"
#include "mousebox.h"
#include "UI_button.h"
#include "custombutton.h"
#include "colors.h"
#include "tutorialtextbox.h"
#include "tutorialtextboxlogic.h"

void tutorial_disableUIButtons(SPACE *ui) {
  ENTITY *buildButton = space_getEntity(ui, "build_button");
  ENTITY *pauseButton = space_getEntity(ui, "pause_button");
  ENTITY *slowButton = space_getEntity(ui, "slow_button");
  ENTITY *fastButton = space_getEntity(ui, "fast_button");
  ENTITY *manageButton = space_getEntity(ui, "manage_button");

  // disable build button
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(buildButton, COMP_MOUSEBOX);
  mbox->active = false;

  // disable pause button
  mbox = (CDATA_MOUSEBOX *)entity_getComponentData(pauseButton, COMP_MOUSEBOX);
  mbox->active = false;

  // disable slow button
  mbox = (CDATA_MOUSEBOX *)entity_getComponentData(slowButton, COMP_MOUSEBOX);
  mbox->active = false;

  // disable fast button
  mbox = (CDATA_MOUSEBOX *)entity_getComponentData(fastButton, COMP_MOUSEBOX);
  mbox->active = false;

  // disable manage button
  mbox = (CDATA_MOUSEBOX *)entity_getComponentData(manageButton, COMP_MOUSEBOX);
  mbox->active = false;
}

void tutorial_enableUIButtons(SPACE *ui) {
  ENTITY *buildButton = space_getEntity(ui, "build_button");
  ENTITY *pauseButton = space_getEntity(ui, "pause_button");
  ENTITY *slowButton = space_getEntity(ui, "slow_button");
  ENTITY *fastButton = space_getEntity(ui, "fast_button");
  ENTITY *manageButton = space_getEntity(ui, "manage_button");

  // enable build button
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(buildButton, COMP_MOUSEBOX);
  mbox->active = true;

  // enable pause button
  mbox = (CDATA_MOUSEBOX *)entity_getComponentData(pauseButton, COMP_MOUSEBOX);
  mbox->active = true;

  // enable slow button
  mbox = (CDATA_MOUSEBOX *)entity_getComponentData(slowButton, COMP_MOUSEBOX);
  mbox->active = true;

  // enable fast button
  mbox = (CDATA_MOUSEBOX *)entity_getComponentData(fastButton, COMP_MOUSEBOX);
  mbox->active = true;

  // enable manage button
  mbox = (CDATA_MOUSEBOX *)entity_getComponentData(manageButton, COMP_MOUSEBOX);
  mbox->active = true;
}

void tutorial_disableBuildButtons(SPACE *ui) {
  LIST *buildButtons = list_create();
  LIST_NODE *node;

  space_getAllEntities(ui, "buildButton", buildButtons);
  node = buildButtons->first;

  while (node) {
    CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData((ENTITY *)node->data, COMP_MOUSEBOX);
    mbox->active = false;
    node = node->next;
  }
  list_destroy(buildButtons);
}

void tutorial_enableBuildButtons(SPACE *ui) {
  LIST *buildButtons = list_create();
  LIST_NODE *node;

  space_getAllEntities(ui, "buildButton", buildButtons);
  node = buildButtons->first;

  while (node) {
    CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData((ENTITY *)node->data, COMP_MOUSEBOX);
    mbox->active = true;
    node = node->next;
  }
  UI_button_updateBuildButtons(ui);
  list_destroy(buildButtons);
}

ENTITY *tutorial_createTextBox(SPACE *ui) {
  VEC2 dimensions = { 640.0f, 360.0f };
  VEC3 position = { 0 };
  ENTITY *created = createCustomButton(NULL, NULL, tutorialBackground_onPressed, NULL, NULL,
                           ui, &position, "textboxbackground",
                           640.0f, 360.0f,
                           false, NULL, NULL, &colors[C_GRAY_DARK],
                           false, NULL, NULL, NULL, TEXTALIGN_CENTER, TEXTALIGN_CENTER);
  CDATA_SPRITE *sprite = entity_getComponentData(created, COMP_SPRITE);
  sprite->color.a = 0.75f;
  vec3_set(&position, 0, 80.0f, 0);
  return space_addEntityAtPosition(ui, arch_tutorialTextBox, "textBox", &position);
}

void tutorialBackground_onPressed(COMPONENT *self) {
  ENTITY *textBox = space_getEntity(self->owner->space, "textBox");
  comp_tutorialTextBoxLogic_nextText(textBox);
}

void createFirstTutorial(SPACE *ui) {
  ENTITY *textBox = tutorial_createTextBox(ui);
  comp_tutorialTextBoxLogic_pushText(textBox, "first");
  comp_tutorialTextBoxLogic_pushText(textBox, "second");
  comp_tutorialTextBoxLogic_pushText(textBox, "third");
}
