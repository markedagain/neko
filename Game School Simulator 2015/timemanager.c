/******************************************************************************
Filename: timemanager.c

Project Name: Game School Simulator 2015

Author: Eduardo Gorinstein

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "timemanager.h"
#include "schoollogic.h"
#include "../NekoEngine/input.h"
#include "newsfeedlogic.h"
#include "studentmanagerlogic.h"
#include "spritetext.h"
#include "generictext.h"
#include "sprite.h"
#include "colors.h"
#include "playerlogic.h"
#include "management.h"

#define WIN_CONDITION 500
#define LOSE_CONDITION -100000

char *month[12] = {
  "Jan",
  "Feb",
  "Mar",
  "Apr",
  "May",
  "June",
  "July",
  "Aug",
  "Sept",
  "Oct",
  "Nov",
  "Dec"
};

char *semester[2] = {
  "Fall",
  "Spring"
};

void comp_timeManager_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_TIMEMANAGER *comData = (CDATA_TIMEMANAGER *)self->data;
  COMPONENT *schoolLogic = entity_getComponent(self->owner, COMP_SCHOOLLOGIC);
  CDATA_SCHOOLLOGIC *schoolData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(self->owner, COMP_SCHOOLLOGIC);
  SPACE *uiSpace = game_getSpace(self->owner->space->game, "ui");
  CDATA_MANAGEMENT *manageData = (CDATA_MANAGEMENT *)entity_getComponentData(space_getEntity(uiSpace, "manage_button"), COMP_MANAGEMENT);
  
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  char buffer[80];

  if(comData->currentSemester >= 0) {
    // Display time on screen   
    if (!comData->timeUI) {
      VEC3 position;
      VEC4 color;
      vec3_set(&position, 220, 175, 0);
      vec4_set(&color, 1, 1, 1, 1 );
      sprintf(buffer, "%s %i, %s", month[comData->monthCounter], comData->currentYear, semester[comData->semesterCounter - 1]);
      comData->timeUI = genericText_create(uiSpace, &position, NULL, "fonts/gothic/20", buffer, &color, TEXTALIGN_RIGHT, TEXTALIGN_TOP);
    }
    sprintf(buffer, "%s %i, %s", month[comData->monthCounter], comData->currentYear, semester[comData->semesterCounter - 1]);
    genericText_setText(comData->timeUI, buffer);
  }
  else {
    // Display time on screen   
    if (!comData->timeUI) {
      VEC3 position;
      VEC4 color;
      vec3_set(&position, 220, 175, 0);
      vec4_set(&color, 1, 1, 1, 1 );
      sprintf(buffer, "July 1989, Fall");
      comData->timeUI = genericText_create(uiSpace, &position, NULL, "fonts/gothic/20", buffer, &color, TEXTALIGN_RIGHT, TEXTALIGN_TOP);
    }
  }

  // START TIME
  if(manageData->closed > 0 || self->owner->space->game->config.tutorial == 0) {
    comData->frameCounter++;
    
    if(comData->paused)
      return;

    // NEW MONTH
    if(comData->frameCounter >= self->owner->space->game->systems.time.framesPerSecond * comData->secondsPerMonth / comData->speedMultiplier) {
      SPACE *ui = game_getSpace(self->owner->space->game, "ui");
      CDATA_PLAYERLOGIC *playerData = (CDATA_PLAYERLOGIC *)entity_getComponentData(space_getEntity(uiSpace, "player"), COMP_PLAYERLOGIC);
      comData->months++;
      
      // Monthly functions //
      comp_schoolLogic_updateDataMonth(schoolLogic, schoolData);
      comData->frameCounter = 0;
      comData->monthCounter++;
      schoolData->roomConstructed = FALSE;

      // if you get enough rep, win!
      if (schoolData->reputation > WIN_CONDITION && !comData->gameEnded) {
        VEC3 position;

        // create main sprite shadow
        vec3_set(&position, 4, -4, 0);
        genericSprite_create(ui, &position, "options", "ui/management_shadow");

        // create main sprite
        vec3_set(&position, 0, 0, 0);
        genericSprite_create(ui, &position, "options", "ui/victory");

        comp_timeManager_pause(self);
        playerData->currentMode = GM_WIN;
        comData->gameEnded = true;
      }

      // if you are too far in debt, you lose!
      if (schoolData->money < LOSE_CONDITION && !comData->gameEnded) {
        VEC3 position;

        // create main sprite shadow
        vec3_set(&position, 4, -4, 0);
        genericSprite_create(ui, &position, "options", "ui/management_shadow");

        // create main sprite
        vec3_set(&position, 0, 0, 0);
        genericSprite_create(ui, &position, "options", "ui/lose");
        comp_timeManager_pause(self);
        playerData->currentMode = GM_LOSE;
        comData->gameEnded = true;
      }

      // NEW SEMESTER
      if(comData->monthCounter == 6 || comData->monthCounter == 12) {
        //char message[80];
        SPACE *fg = game_getSpace(self->owner->space->game, "fg");
        ENTITY *studentManager = space_getEntity(fg, "studentManager");
        COMPONENT *studentManagerLogic = (COMPONENT *)entity_getComponent(studentManager, COMP_STUDENTMANAGERLOGIC);

        // Bring up new semester report


        comData->currentSemester++;
        if(comData->semesterCounter == 1)
          comData->semesterCounter = 2;
        else if(comData->semesterCounter == 2)
          comData->semesterCounter = 1;

        // Semesterly functions //
        comp_schoolLogic_updateDataSemester(schoolLogic, schoolData);
        
        // update number of students to display
        comp_studentManagerLogic_updateDisplayFraction(studentManagerLogic);
      }
    }

    // NEW YEAR
    if(comData->monthCounter >= 12) {
      comData->previousYear = comData->currentYear;
      comData->currentYear++;
      comData->monthCounter = 0;
    }
  }

  
}

void comp_timeManager_pause(COMPONENT *ptr) {
  CDATA_TIMEMANAGER *comData = (CDATA_TIMEMANAGER *)entity_getComponentData(space_getEntity(game_getSpace(ptr->owner->space->game, "sim"), "gameManager"), COMP_TIMEMANAGER);
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(space_getEntity(game_getSpace(ptr->owner->space->game, "ui"), "pauseButton"), COMP_SPRITE);

  // Play
  if(comData->paused) {
    comData->paused = FALSE;
    sprite->source = "ui/pause";
  }
  else { // Pause
    comData->paused = TRUE;
    sprite->source = "ui/play";
  }
}

void comp_timeManager_changeSpeed(COMPONENT *ptr) {
  CDATA_TIMEMANAGER *comData = (CDATA_TIMEMANAGER *)entity_getComponentData(space_getEntity(game_getSpace(ptr->owner->space->game, "sim"), "gameManager"), COMP_TIMEMANAGER);
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(space_getEntity(game_getSpace(ptr->owner->space->game, "ui"), "speedButton"), COMP_SPRITE);

  // SLOW -> MEDIUM
  if(comData->secondsPerMonth == 6) {
    comData->secondsPerMonth = 3;
    sprite->source = "ui/speed_medium";
  }
  // MEDIUM -> FAST
  else if(comData->secondsPerMonth == 3) {
    comData->secondsPerMonth = 2;
    sprite->source = "ui/speed_fast";
  }
  // FAST -> VERY FAST
  else if(comData->secondsPerMonth == 2) {
    comData->secondsPerMonth = 1;
    sprite->source = "ui/speed_veryfast";
  }
  // VERY FAST -> SLOW
  else if(comData->secondsPerMonth == 1) {
    comData->secondsPerMonth = 6;
    sprite->source = "ui/speed_slow";
  }
}

// Initialize values
void comp_timeManager(COMPONENT *self) {
  CDATA_TIMEMANAGER data = { 0 };
  data.secondsPerMonth = 6;
  data.speedMultiplier = 1;
  data.paused = FALSE;
  data.months = 0;
  data.currentSemester = -1;
  data.previousYear = 1988;
  data.currentYear = 1989;
  data.frameCounter = 10;
  data.monthCounter = 5;
  data.semesterCounter = 2;

  COMPONENT_INIT(self, COMP_TIMEMANAGER, data);
  component_depend(self, COMP_SCHOOLLOGIC);
  self->events.logicUpdate = comp_timeManager_logicUpdate;
}