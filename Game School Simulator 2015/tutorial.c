/******************************************************************************
Filename: tutorial.c

Project Name: Game School Simulator 2015

Author: Tai Der Hui

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


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
  /*mbox = (CDATA_MOUSEBOX *)entity_getComponentData(pauseButton, COMP_MOUSEBOX);
  mbox->active = false;

  // disable slow button
  mbox = (CDATA_MOUSEBOX *)entity_getComponentData(slowButton, COMP_MOUSEBOX);
  mbox->active = false;

  // disable fast button
  mbox = (CDATA_MOUSEBOX *)entity_getComponentData(fastButton, COMP_MOUSEBOX);
  mbox->active = false;*/

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
  //mbox = (CDATA_MOUSEBOX *)entity_getComponentData(pauseButton, COMP_MOUSEBOX);
  //mbox->active = true;

  // enable slow button
  //mbox = (CDATA_MOUSEBOX *)entity_getComponentData(slowButton, COMP_MOUSEBOX);
  //mbox->active = true;

  // enable fast button
  // mbox = (CDATA_MOUSEBOX *)entity_getComponentData(fastButton, COMP_MOUSEBOX);
  //mbox->active = true;

  // enable manage button
  mbox = (CDATA_MOUSEBOX *)entity_getComponentData(manageButton, COMP_MOUSEBOX);
  mbox->active = true;
}

void tutorial_disableBuildButtons(SPACE *ui) {
  LIST *buildButtons = list_create();
  LIST_NODE *node;
  CDATA_MOUSEBOX *buildBox = (CDATA_MOUSEBOX *)entity_getComponentData((ENTITY *)space_getEntity(ui, "build_button"), COMP_MOUSEBOX);

  buildBox->active = false;
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
  CDATA_MOUSEBOX *buildBox = (CDATA_MOUSEBOX *)entity_getComponentData((ENTITY *)space_getEntity(ui, "build_button"), COMP_MOUSEBOX);

  buildBox->active = true;
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
  SPACE *tutorial = game_getSpace(ui->game, "tutorial");
  // background button
  ENTITY *created = createCustomButton(NULL, NULL, tutorialBackground_onPressed, NULL, NULL,
                           tutorial, &position, "textboxbackground",
                           640.0f, 360.0f,
                           false, NULL, NULL, &colors[C_GRAY_DARK],
                           false, NULL, NULL, NULL, TEXTALIGN_CENTER, TEXTALIGN_CENTER);
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(created, COMP_SPRITE);
  sprite->color.a = 0.75f;
  vec3_set(&position, 0, 80.0f, 0);
  return space_addEntityAtPosition(tutorial, arch_tutorialTextBox, "textBox", &position);
}

void tutorialBackground_onPressed(COMPONENT *self) {
  ENTITY *textBox = space_getEntity(self->owner->space, "textBox");
  comp_tutorialTextBoxLogic_nextText(textBox);
}

void createFirstTutorial(SPACE *ui) {
  ENTITY *textBox = tutorial_createTextBox(ui);
  comp_tutorialTextBoxLogic_pushText(textBox, "What up Bro, they told me you would be coming!\nI am Brad Bromayor, \nyour one and only advisor as you build your new game school!\n\nClick anywhere to continue.");
  comp_tutorialTextBoxLogic_pushText(textBox, "Oh yeah, you're totally building a game school!\n\nWe got approved for the loan, \nand got this gorgeous piece of land!");
  comp_tutorialTextBoxLogic_pushText(textBox, "Let's kick things off by buying a Lobby.\n\nClick the Build Button to continue.\n(or press the Space button)");
  comp_tutorialTextBoxLogic_nextText(textBox);
  tutorial_disableUIButtons(ui);
  tutorial_enableBuildButtons(ui);
  sound_playSound(&ui->game->systems.sound, "dudebro");
}

void createFirstTutorialPartTwo(SPACE *ui) {
  ENTITY *textBox = tutorial_createTextBox(ui);
  comp_tutorialTextBoxLogic_pushText(textBox, "Nice, Bro!\n\nHere you can see the rooms you are able to create!");
  comp_tutorialTextBoxLogic_pushText(textBox, "The highlighted buttons indicate which rooms\nyou can create right now!\n\nLet's build a lobby, shall we?");
  comp_tutorialTextBoxLogic_nextText(textBox);
}


void createSecondTutorial(SPACE *ui) {
  ENTITY *textBox = tutorial_createTextBox(ui);
  comp_tutorialTextBoxLogic_pushText(textBox, "Great! Whenever you try to build a new room you\nwill see the available build locations on screen.");
  comp_tutorialTextBoxLogic_pushText(textBox, "All you have to do is to click on the one you want to build at.\nClick on the available slot to continue.");
  comp_tutorialTextBoxLogic_nextText(textBox);
  tutorial_disableUIButtons(ui);
  tutorial_enableBuildButtons(ui);
}

void createThirdTutorial(SPACE *ui) {
  ENTITY *textBox = tutorial_createTextBox(ui);
  comp_tutorialTextBoxLogic_pushText(textBox, "I feel like we are forgeting something...\nRight! Students!! This is a game school after all!\nThat means we need a classroom.");
  comp_tutorialTextBoxLogic_pushText(textBox, "Let's open up that Build menu again,\nand a get a classroom in!");
  comp_tutorialTextBoxLogic_nextText(textBox);
  tutorial_disableUIButtons(ui);
  tutorial_enableBuildButtons(ui);
}

void createFourthTutorial(SPACE *ui) {
  CDATA_MOUSEBOX *manageBox = (CDATA_MOUSEBOX *)entity_getComponentData((ENTITY *)space_getEntity(ui, "manage_button"), COMP_MOUSEBOX);
  ENTITY *textBox = tutorial_createTextBox(ui);
  comp_tutorialTextBoxLogic_pushText(textBox, "This looks great!\n\nWell, I think it's about time we let our\nfirst students in, don't you?");
  comp_tutorialTextBoxLogic_pushText(textBox, "Let's check the current status of incoming students!\n\nClick the Management Screen Button above, man.");
  comp_tutorialTextBoxLogic_nextText(textBox);
  tutorial_disableUIButtons(ui);
  tutorial_disableBuildButtons(ui);
  manageBox->active = true;
}

void createFifthTutorial(SPACE *ui) {
  ENTITY *textBox = tutorial_createTextBox(ui);
  comp_tutorialTextBoxLogic_pushText(textBox, "Here, you can manage various attributes of your school!\n\nRequired GPA and Tuition affect the\nnumber of incoming students.");
  comp_tutorialTextBoxLogic_pushText(textBox, "You can also see your current budget and various stats.\n\nWelp, that's all I've got for now.");
  comp_tutorialTextBoxLogic_pushText(textBox, "Let's wait for our incoming students to arrive!");
  comp_tutorialTextBoxLogic_nextText(textBox);
  tutorial_enableUIButtons(ui);
  tutorial_enableBuildButtons(ui);
}

void createSixthTutorial(SPACE *ui) {
  ENTITY *textBox = tutorial_createTextBox(ui);
  comp_tutorialTextBoxLogic_pushText(textBox, "Your first students have arrived!\n\nThis means your reputation can start to change.\nWhen students drop out, your reputation goes down.\nBut when your students graduate your rep goes up!");
  comp_tutorialTextBoxLogic_pushText(textBox, "When students drop out, your reputation goes down.\nBut when your students graduate, your rep goes up!");
  comp_tutorialTextBoxLogic_pushText(textBox, "Your students gain stats while studying at your school.\nYou can get details on students by\nclicking their avatar on the screen.");
  comp_tutorialTextBoxLogic_pushText(textBox, "The higher their main stat is, the more repuation\nyou get when they graduate!");
  comp_tutorialTextBoxLogic_pushText(textBox, "If a students motivation drops below 0% they will drop out!\n\nYou can stop that from happening by\nbuilding rooms that provide motivation boosts!");
  comp_tutorialTextBoxLogic_pushText(textBox, "The amount their stats increase is\nalso determined by their motivation.\nSo keep that motivation high!");
  comp_tutorialTextBoxLogic_pushText(textBox, "Well, that's all I have for you.\n\nFrom what I have heard,\nthe best game school in the nation has 500 reputation!\nIf you can beat that, you will have the best game school ever!");
  comp_tutorialTextBoxLogic_pushText(textBox, "I know you'll do great whatever you decide to do.\n\nGood Luck, and Have Fun!");
  comp_tutorialTextBoxLogic_nextText(textBox);
  tutorial_enableUIButtons(ui);
  tutorial_enableBuildButtons(ui);
}
