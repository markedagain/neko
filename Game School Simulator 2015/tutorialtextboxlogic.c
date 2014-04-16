/******************************************************************************
Filename: tutorialtextboxlogic.c

Project Name: Game School Simulator 2015

Author: Tai Der Hui

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "tutorialtextboxlogic.h"
#include "generictext.h"
#include "genericsprite.h"
#include "colors.h"
#include "brad.h"

void comp_tutorialTextBoxLogic_logicUpdate(COMPONENT *self, void *event) {
}

void comp_tutorialTextBoxLogic(COMPONENT *self) {
  CDATA_TUTORIALTEXT data = { 0 };
  data.textList = list_create();
  COMPONENT_INIT(self, COMP_TUTORIALTEXTBOXLOGIC, data);
  self->events.logicUpdate = comp_tutorialTextBoxLogic_logicUpdate;
  self->events.initialize = comp_tutorialTextBoxLogic_initialize;
  self->events.destroy = comp_tutorialTextBoxLogic_destroy;
}

void comp_tutorialTextBoxLogic_initialize(COMPONENT *self, void *event) {
  CDATA_TUTORIALTEXT *data = (CDATA_TUTORIALTEXT *)self->data;
  VEC3 pos = { 0, -10.0f, 0 };
  VEC2 dimensions = { 500.0f, 125.0f};
  VEC4 color = { 0, 0, 0, 1.0f };

  // box sprite
  ENTITY *whiteBox = space_addEntityAtPosition(self->owner->space, arch_brad, "textboxbackground", &pos);
  entity_attach(whiteBox, self->owner);
  vec3_set(&pos, -228.0f, 47.0f, 0);

  // text
  color = colors[C_WHITE_LIGHT];
  data->text = genericText_create(self->owner->space, &pos, "textboxtext", "fonts/gothic/16", "", &color, TEXTALIGN_LEFT, TEXTALIGN_TOP);
  entity_attach(data->text, self->owner);
  comp_tutorialTextBoxLogic_pushText(self->owner, "");
  data->currentText = data->textList->first;
}

void comp_tutorialTextBoxLogic_destroy(COMPONENT *self, void *event) {
  CDATA_TUTORIALTEXT *data = (CDATA_TUTORIALTEXT *)self->data;
  list_destroy(data->textList);
}

void comp_tutorialTextBoxLogic_pushText(ENTITY *tutorialBox, char *newText) {
  CDATA_TUTORIALTEXT *data = (CDATA_TUTORIALTEXT *)entity_getComponentData(tutorialBox, COMP_TUTORIALTEXTBOXLOGIC);
  list_insert_end(data->textList, (void *)newText);
}

void comp_tutorialTextBoxLogic_nextText(ENTITY *tutorialBox) {
  CDATA_TUTORIALTEXT *data = (CDATA_TUTORIALTEXT *)entity_getComponentData(tutorialBox, COMP_TUTORIALTEXTBOXLOGIC);
  data->currentText = data->currentText->next;
  if (data->currentText)
    genericText_setText(data->text, (char *)data->currentText->data);
  else
    comp_tutorialTextBoxLogic_destroyTutorial(tutorialBox->space);
}

void comp_tutorialTextBoxLogic_destroyTutorial(SPACE *ui) {
  ENTITY *textBoxBackground = space_getEntity(ui, "textboxbackground");
  ENTITY *textBox = space_getEntity(ui, "textBox");

  entity_destroy(textBoxBackground);
  entity_destroy(textBox);
}
