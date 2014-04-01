/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __TUTORIAL_H__
#define __TUTORIAL_H__
#include "entity.h"

#define TUTORIAL 1

void tutorial_enableUIButtons(SPACE *ui);
void tutorial_disableUIButtons(SPACE *ui);
void tutorial_enableBuildButtons(SPACE *ui);
void tutorial_disableBuildButtons(SPACE *ui);
ENTITY * tutorial_createTextBox(SPACE *ui);
void tutorialBackground_onPressed(COMPONENT *self);
void createFirstTutorial(SPACE *ui);
void createFirstTutorialPartTwo(SPACE *ui);
void createSecondTutorial(SPACE *ui);
void createThirdTutorial(SPACE *ui);
void createFourthTutorial(SPACE *ui);
void createFifthTutorial(SPACE *ui);

#endif