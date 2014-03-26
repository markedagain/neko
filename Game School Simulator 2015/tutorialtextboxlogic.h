/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_TUTORIALTEXTBOXLOGIC__
#define __COMP_TUTORIALTEXTBOXLOGIC__

#include "entity.h"
#include "hash.h"

#define COMP_TUTORIALTEXTBOXLOGIC HASH("COMP_TUTORIALTEXTBOXLOGIC")
void comp_tutorialTextBoxLogic_logicUpdate(COMPONENT *self, void *event);
void comp_tutorialTextBoxLogic(COMPONENT *self);
void comp_tutorialTextBoxLogic_initialize(COMPONENT *self, void * event);
void comp_tutorialTextBoxLogic_destroy(COMPONENT *self, void *event);
void comp_tutorialTextBoxLogic_nextText(ENTITY *tutorialBox);
void comp_tutorialTextBoxLogic_pushText(ENTITY *tutorialBox, char *newText);
void comp_tutorialTextBoxLogic_destroyTutorial(SPACE *ui);

typedef struct {
  LIST *textList;
  LIST_NODE *currentText;
  ENTITY *text;
} CDATA_TUTORIALTEXT;


#endif
