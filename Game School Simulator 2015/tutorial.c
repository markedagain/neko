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
  ENTITY *pauseButton = space_getEntity(ui, "pauseButton");
  ENTITY *fastButton = space_getEntity(ui, "speedButton");
  ENTITY *manageButton = space_getEntity(ui, "manage_button");

  // disable build button
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(buildButton, COMP_MOUSEBOX);
  mbox->active = false;

  // disable pause button
  mbox = (CDATA_MOUSEBOX *)entity_getComponentData(pauseButton, COMP_MOUSEBOX);
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
  ENTITY *pauseButton = space_getEntity(ui, "pauseButton");
  ENTITY *fastButton = space_getEntity(ui, "speedButton");
  ENTITY *manageButton = space_getEntity(ui, "manage_button");

  // if there even is a build button
  if (buildButton) {
    // enable build button
    CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(buildButton, COMP_MOUSEBOX);
    mbox->active = true;

    // enable pause button
    mbox = (CDATA_MOUSEBOX *)entity_getComponentData(pauseButton, COMP_MOUSEBOX);
    mbox->active = true;

    // enable fast button
    mbox = (CDATA_MOUSEBOX *)entity_getComponentData(fastButton, COMP_MOUSEBOX);
    mbox->active = true;

    // enable manage button
    mbox = (CDATA_MOUSEBOX *)entity_getComponentData(manageButton, COMP_MOUSEBOX);
    mbox->active = true;
  }
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
  comp_tutorialTextBoxLogic_pushText(textBox, "");
  /////////////////////////////////////////////                                                         ////
  comp_tutorialTextBoxLogic_pushText(textBox, "What up bro? I heard you'd be coming!\n"
                                              "I'm Brad Bromayor, here to help you out on your journey\n"
                                              "to make the best game school in the world!\n"
                                              "                             (CLICK ANYWHERE TO CONTINUE)");
  /////////////////////////////////////////////                                                         ////
  comp_tutorialTextBoxLogic_pushText(textBox, "I already talked to the dudes at the bank; your loan got\n"
                                              "approved and we got this totally rad plot of land!\n"
                                              "Let's get started!");
  /////////////////////////////////////////////                                                         ////
  comp_tutorialTextBoxLogic_pushText(textBox, "First things first! You need a lobby to build your school\n"
                                              "around. Let's build one!\n"
                                              "Click the Build button (the hammer icon at the top of\n"
                                              "the screen) or press SPACEBAR to open the Build Menu!");
  comp_tutorialTextBoxLogic_nextText(textBox);
  tutorial_disableUIButtons(ui);
  tutorial_enableBuildButtons(ui);
  //sound_playSound(&ui->game->systems.sound, "dudebro");
}

void createFirstTutorialPartTwo(SPACE *ui) {
  ENTITY *textBox = tutorial_createTextBox(ui);
  /////////////////////////////////////////////                                                         ////
  comp_tutorialTextBoxLogic_pushText(textBox, "Nice, bro!\n"
                                              "This is where you can see all the rooms you can build!\n");
  /////////////////////////////////////////////                                                         ////
  comp_tutorialTextBoxLogic_pushText(textBox, "The rooms that you have unlocked AND have enough money\n"
                                              "for are highlighted, like the Lobby is now.");
  /////////////////////////////////////////////                                                         ////
  comp_tutorialTextBoxLogic_pushText(textBox, "So hey, let's build a Lobby! Click on the Lobby button\n"
                                              "to start making the game school of your dreams!");
  comp_tutorialTextBoxLogic_nextText(textBox);
}


void createSecondTutorial(SPACE *ui) {
  ENTITY *textBox = tutorial_createTextBox(ui);
  /////////////////////////////////////////////                                                         ////
  comp_tutorialTextBoxLogic_pushText(textBox, "Rad!\n"
                                              "Whenever you go to build a new room, the different\n"
                                              "possible build locations will be shown on the screen.");
  /////////////////////////////////////////////                                                         ////
  comp_tutorialTextBoxLogic_pushText(textBox, "All you gotta do is pick one and click one, and the room\n"
                                              "will be built there immediately!");
  comp_tutorialTextBoxLogic_nextText(textBox);
  tutorial_disableUIButtons(ui);
  tutorial_enableBuildButtons(ui);
}

void createThirdTutorial(SPACE *ui) {
  ENTITY *textBox = tutorial_createTextBox(ui);
  /////////////////////////////////////////////                                                         ////
  comp_tutorialTextBoxLogic_pushText(textBox, "Right on!\n"
                                              "Lobbies are pretty chill, but I feel like our game\n"
                                              "school is missing something still...");
  comp_tutorialTextBoxLogic_pushText(textBox, "Oh, right, students! Game schools are nothing without\n"
                                              "their students! And students need classrooms so they\n"
                                              "can, like, go to class and stuff!");
  comp_tutorialTextBoxLogic_pushText(textBox, "Open up the Build menu again, and build a Classroom\n"
                                              "wherever you want!");
  comp_tutorialTextBoxLogic_nextText(textBox);
  tutorial_disableUIButtons(ui);
  tutorial_enableBuildButtons(ui);
}

void createFourthTutorial(SPACE *ui) {
  CDATA_MOUSEBOX *manageBox = (CDATA_MOUSEBOX *)entity_getComponentData((ENTITY *)space_getEntity(ui, "manage_button"), COMP_MOUSEBOX);
  ENTITY *textBox = tutorial_createTextBox(ui);
  /////////////////////////////////////////////                                                         ////
  comp_tutorialTextBoxLogic_pushText(textBox, "Dude, this is like, a real school now!\n"
                                              "Well, almost. Now we gotta wait for some students to\n"
                                              "enroll.");
  comp_tutorialTextBoxLogic_pushText(textBox, "To check on how your school is doing, including stuff\n"
                                              "like the number of incoming students, you need to check\n"
                                              "the Management screen. Click the pencil button above, or\n"
                                              "press M on your keyboard!");
  comp_tutorialTextBoxLogic_nextText(textBox);
  tutorial_disableUIButtons(ui);
  tutorial_disableBuildButtons(ui);
  manageBox->active = true;
}

void createFifthTutorial(SPACE *ui) {
  ENTITY *textBox = tutorial_createTextBox(ui);
  /////////////////////////////////////////////                                                         ////
  comp_tutorialTextBoxLogic_pushText(textBox, "This is where you can check on your school and see what's\n"
                                              "going on beneath the surface.");
  comp_tutorialTextBoxLogic_pushText(textBox, "You can also change the minimum GPA required for\n"
                                              "acceptance, as well as the semesterly tuition rate.\n"
                                              "Adjusting these will affect the number of students that\n"
                                              "enroll each semester, but also will affect your income!");
  comp_tutorialTextBoxLogic_pushText(textBox, "You gotta remember though, and this is IMPORTANT:\n"
                                              "You can take losses here and there, but if you ever fall\n"
                                              "below $-100,000, it's game over, man! Even I won't be\n"
                                              "able to keep the banks off your back!");
  comp_tutorialTextBoxLogic_pushText(textBox, "Well, that's all I've got for now. Let's sit back and\n"
                                              "wait for our first batch of students to enroll!");
  comp_tutorialTextBoxLogic_nextText(textBox);
  tutorial_enableUIButtons(ui);
  tutorial_enableBuildButtons(ui);
}

void createSixthTutorial(SPACE *ui) {
  ENTITY *textBox = tutorial_createTextBox(ui);
  /////////////////////////////////////////////                                                         ////
  comp_tutorialTextBoxLogic_pushText(textBox, "Dude! Your first students have finally arrived!\n"
                                              "This means, you're, like, a real school now and stuff,\n"
                                              "so you have a reputation to maintain!");
  comp_tutorialTextBoxLogic_pushText(textBox, "When students GRADUATE, your reputation will go up, but\n"
                                              "when students DROP OUT, your reputation will go down!");
  comp_tutorialTextBoxLogic_pushText(textBox, "Each student at your school has stats that increase as\n"
                                              "they study and learn. If you add better rooms to your\n"
                                              "school, or improve the existing ones, their stats will\n"
                                              "increase faster!");
  comp_tutorialTextBoxLogic_pushText(textBox, "The higher a graduate's main stat is, the more repuation\n"
                                              "you'll gain. Real game developers want to hire skilled\n"
                                              "employees, not bad ones!");
  comp_tutorialTextBoxLogic_pushText(textBox, "Students also have a Motivation stat. If a student's\n"
                                              "Motivation drops below 0%, they will drop out!\n"
                                              "Not cool, bro!");
  comp_tutorialTextBoxLogic_pushText(textBox, "You can prevent this by building rooms that increase\n"
                                              "Motivation. More motivation will also lead to students\n"
                                              "doing better in school in general, so yeah, Motivation\n"
                                              "is pretty important.");
  /////////////////////////////////////////////                                                         ////
  comp_tutorialTextBoxLogic_pushText(textBox, "I know I'm kinda goin' on a rant right now, but just one\n"
                                              "more thing, I promise! This one's important!");
  /////////////////////////////////////////////                                                         ////
  comp_tutorialTextBoxLogic_pushText(textBox, "The best game school in the nation apparently has\n"
                                              "500 REPUTATION. Got that? 500! That's a lot!");
  /////////////////////////////////////////////                                                         ////
  comp_tutorialTextBoxLogic_pushText(textBox, "If you can beat that, your game school will truly be the\n"
                                              "the greatest!");
  /////////////////////////////////////////////                                                         ////
  comp_tutorialTextBoxLogic_pushText(textBox, "That's all I got for now, bro, but I know you got it from\n"
                                              "here. Good luck, and have fun!");
  comp_tutorialTextBoxLogic_nextText(textBox);
  tutorial_enableUIButtons(ui);
  tutorial_enableBuildButtons(ui);
}
