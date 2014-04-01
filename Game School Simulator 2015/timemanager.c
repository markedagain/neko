/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

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

#define WIN_CONDITION 200
#define LOSE_CONDITION -100000

char *month[12] = {
  "January",
  "February",
  "March",
  "April",
  "May",
  "June",
  "July",
  "August",
  "September",
  "October",
  "November",
  "December"
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
  
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  char buffer[80];

  if(comData->currentSemester >= 0) {
    // Display time on screen   
    if (!comData->timeUI) {
      VEC3 position;
      VEC4 color;
      vec3_set(&position, 220, 176, 0);
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
      vec3_set(&position, 220, 176, 0);
      vec4_set(&color, 1, 1, 1, 1 );
      sprintf(buffer, "July 1989, Fall");
      comData->timeUI = genericText_create(uiSpace, &position, NULL, "fonts/gothic/20", buffer, &color, TEXTALIGN_RIGHT, TEXTALIGN_TOP);
    }
  }

  if(schoolData->roomList->count >= 2) {
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
        VEC2 dimensions = { 400.0f, 200.0f };
        VEC3 position;
        
        vec3_set(&position, 0, 0, 0);
        genericSprite_createBlank(uiSpace, &position, &dimensions, &colors[C_NAVY_LIGHT], "winScreen");
        genericText_create(uiSpace, &position, "winScreen", "fonts/gothic/28", "You won!\nPress enter to keep playing!", &colors[C_WHITE_LIGHT], TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
        comp_timeManager_pause(self);
        playerData->currentMode = GM_WIN;
        comData->gameEnded = true;
      }

      // if you are too far in debt, you lose!
      if (schoolData->money < LOSE_CONDITION && !comData->gameEnded) {
        VEC2 dimensions = { 400.0f, 200.0f };
        VEC3 position;
        
        vec3_set(&position, 0, 0, 0);
        genericSprite_createBlank(uiSpace, &position, &dimensions, &colors[C_NAVY_LIGHT], "loseScreen");
        genericText_create(uiSpace, &position, "loseScreen", "fonts/gothic/28", "You are too far in debt!\nYou lose!\nPress enter to quit.", &colors[C_WHITE_LIGHT], TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
        comp_timeManager_pause(self);
        playerData->currentMode = GM_LOSE;
        comData->gameEnded = true;
      }

      // NEW SEMESTER
      if(comData->monthCounter == 6 || comData->monthCounter == 12) {
        char message[80];
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
        
        // create pop text above student's heads
        //comp_studentManagerLogic_statGainText(studentManagerLogic);
        sprintf(message, pushStrings[STRINGS_SEMESTER], comData->currentSemester);
        comp_newsfeedlogic_push(self, message);
      }
    }

    // NEW YEAR
    if(comData->monthCounter >= 12) {
      char message[80];
      comData->previousYear = comData->currentYear;
      comData->currentYear++;
      comp_schoolLogic_updateDataYear(schoolLogic, schoolData);
      comData->monthCounter = 0;
      sprintf(message, pushStrings[STRINGS_YEAR], comData->currentYear);
      comp_newsfeedlogic_push(self, message);
    }
  }


}

void comp_timeManager_pause(COMPONENT *ptr) {
  CDATA_TIMEMANAGER *comData = (CDATA_TIMEMANAGER *)entity_getComponentData(space_getEntity(game_getSpace(ptr->owner->space->game, "sim"), "gameManager"), COMP_TIMEMANAGER);

  if(comData->paused)
    comData->paused = FALSE;
  else
    comData->paused = TRUE;
}

void comp_timeManager_fastForward(COMPONENT *ptr) {
  CDATA_TIMEMANAGER *comData = (CDATA_TIMEMANAGER *)entity_getComponentData(space_getEntity(game_getSpace(ptr->owner->space->game, "sim"), "gameManager"), COMP_TIMEMANAGER);

  if(comData->secondsPerMonth == 6)
    comData->secondsPerMonth = 3;
  else if(comData->secondsPerMonth == 3)
    comData->secondsPerMonth = 2;
  else if(comData->secondsPerMonth == 2)
    comData->secondsPerMonth = 1;
}

void comp_timeManager_slowDown(COMPONENT *ptr) {
  CDATA_TIMEMANAGER *comData = (CDATA_TIMEMANAGER *)entity_getComponentData(space_getEntity(game_getSpace(ptr->owner->space->game, "sim"), "gameManager"), COMP_TIMEMANAGER);

  if(comData->secondsPerMonth == 1)
    comData->secondsPerMonth = 2;
  else if(comData->secondsPerMonth == 2)
    comData->secondsPerMonth = 3;
  else if(comData->secondsPerMonth == 3)
    comData->secondsPerMonth = 6;
}

void comp_timeManager(COMPONENT *self) {
  CDATA_TIMEMANAGER data = { 0 };
  data.secondsPerMonth = 3;
  data.speedMultiplier = 1;
  data.paused = FALSE;
  data.months = -6;
  data.currentSemester = -1;
  data.previousYear = 1988;
  data.currentYear = 1989;
  data.frameCounter = 10;
  data.monthCounter = 0;
  data.semesterCounter = 2;

  COMPONENT_INIT(self, COMP_TIMEMANAGER, data);
  component_depend(self, COMP_SCHOOLLOGIC);
  self->events.logicUpdate = comp_timeManager_logicUpdate;
}