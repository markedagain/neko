/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "moneyinfologic.h"
#include "sprite.h"
#include "genericsprite.h"
#include "generictext.h"
#include "schoollogic.h"
#include "colors.h"
#include "sound.h"
#include "mousebox.h"
#include "../NekoEngine/generictext.h"
#include "../Nekoengine/spritetext.h"
#include "schoollogic.h"
#include "studentdata.h"

void comp_moneyInfoLogic_initialize(COMPONENT *self, void *event) {
  CDATA_MONEYINFOLOGIC *comData = (CDATA_MONEYINFOLOGIC *)self->data;
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  SPACE *uiSpace = game_getSpace(self->owner->space->game, "ui");
  COMPONENT *box = (COMPONENT *)entity_getComponent(self->owner, COMP_MOUSEBOX);
  char textBuffer[40] = {0};
  VEC3 pos = {220, 130, 0};
  VEC4 color = colors[C_GREEN_LIGHT];

  mbox->manual = true;
  set_box(box, 230, 180, 360, 150);

  comData->incomeText = genericText_create(uiSpace, &pos, "incomeText", "fonts/gothic/12", textBuffer, &color, TEXTALIGN_LEFT, TEXTALIGN_MIDDLE);
  vec3_set(&pos, 220, 100, 0);
  color = colors[C_RED_LIGHT];
  comData->expensesText = genericText_create(uiSpace, &pos, "expensesText", "fonts/gothic/12", textBuffer, &color, TEXTALIGN_LEFT, TEXTALIGN_MIDDLE);
  vec3_set(&pos, 220, 70, 0);
  color = colors[C_WHITE_LIGHT];
  comData->totalText = genericText_create(uiSpace, &pos, "totalText", "fonts/gothic/12", textBuffer, &color, TEXTALIGN_LEFT, TEXTALIGN_MIDDLE);
}

void comp_moneyInfoLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_MONEYINFOLOGIC *comData = (CDATA_MONEYINFOLOGIC *)self->data;
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);

  if(mbox->entered) {
    CDATA_SCHOOLLOGIC *schoolData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(space_getEntity(game_getSpace(self->owner->space->game, "sim"), "gameManager"), COMP_SCHOOLLOGIC);
    COMPONENT *incomeMultiSprite = (COMPONENT *) entity_getComponent(comData->incomeText, COMP_MULTISPRITE);
    COMPONENT *expensesMultiSprite = (COMPONENT *) entity_getComponent(comData->expensesText, COMP_MULTISPRITE);
    COMPONENT *totalMultiSprite = (COMPONENT *) entity_getComponent(comData->totalText, COMP_MULTISPRITE);
    char textBuffer[40] = {0};
    float income = 0;
    float expenses = 0;
    float total = 0;
    int i = 0;
    LIST_NODE *studentPtr;
    LIST_NODE *roomPtr;

    // Calculate Income
    studentPtr = schoolData->students->first;
    for(i = 0; i < schoolData->students->count; i++) {
      CDATA_STUDENTDATA *studentData = (CDATA_STUDENTDATA *)entity_getComponentData((ENTITY *)studentPtr->data, COMP_STUDENTDATA);
      income += studentData->tuition / 6;
      studentPtr = studentPtr->next;
    }

    // Calculate Expenses
    roomPtr = schoolData->roomList->first;
    for(i = 0; i < schoolData->roomList->count; i++) {
      CDATA_ROOMLOGIC *roomData = (CDATA_ROOMLOGIC *)entity_getComponentData(roomPtr->data, COMP_ROOMLOGIC);
      expenses -= roomData->upkeep;
      roomPtr = roomPtr->next;
    }

    total = income + expenses;

    sprintf(textBuffer, "Income:\n   %.2f", income);
    genericText_setText(comData->incomeText, textBuffer);

    sprintf(textBuffer, "Expenses:\n    %.2f", expenses);
    genericText_setText(comData->expensesText, textBuffer);

    sprintf(textBuffer, "Total:\n    %.2f", total);
    genericText_setText(comData->totalText, textBuffer);

    vec3_set(&trans->translation, trans->translation.x, trans->translation.y - 110, trans->translation.z);
    multiSprite_setAlpha(incomeMultiSprite, 1);
    multiSprite_setAlpha(expensesMultiSprite, 1);
    multiSprite_setAlpha(totalMultiSprite, 1);
  }

  if(mbox->exited) {
    COMPONENT *incomeMultiSprite = (COMPONENT *) entity_getComponent(comData->incomeText, COMP_MULTISPRITE);
    COMPONENT *expensesMultiSprite = (COMPONENT *) entity_getComponent(comData->expensesText, COMP_MULTISPRITE);
    COMPONENT *totalMultiSprite = (COMPONENT *) entity_getComponent(comData->totalText, COMP_MULTISPRITE);

    vec3_set(&trans->translation, trans->translation.x, trans->translation.y + 110, trans->translation.z);
    multiSprite_setAlpha(incomeMultiSprite, 0);
    multiSprite_setAlpha(expensesMultiSprite, 0);
    multiSprite_setAlpha(totalMultiSprite, 0);
  }
}

void comp_moneyInfoLogic(COMPONENT *self) {
  CDATA_MONEYINFOLOGIC data = {0};
  COMPONENT_INIT(self, COMP_MONEYINFOLOGIC, data);
  self->events.logicUpdate = comp_moneyInfoLogic_logicUpdate;
  self->events.initialize = comp_moneyInfoLogic_initialize;
}
