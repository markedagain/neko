/******************************************************************************
Filename: studentdata.c

Project Name: Game School Simulator 2015

Author: Samuel Valdez

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "studentdata.h"
#include <string.h>
#include <malloc.h>
#include "../NekoEngine/vector.h"
#include "../NekoEngine/entity.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/linkedlist.h"
#include "../NekoEngine/random.h"
#include "timemanager.h"
#include "schoollogic.h"
#include "newsfeedlogic.h"
#include "studentmanagerlogic.h"
#define MALE_HEAD_COUNT 5
#define MALE_FACE_COUNT 5
#define MALE_HAIR_COUNT 10
#define MALE_BODY_COUNT 5
#define MALE_LEGS_COUNT 5

#define FEMALE_HEAD_COUNT 5
#define FEMALE_FACE_COUNT 5
#define FEMALE_HAIR_COUNT 11
#define FEMALE_BODY_COUNT 5
#define FEMALE_LEGS_COUNT 5

void comp_studentData_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_STUDENTDATA *comData = (CDATA_STUDENTDATA *)self->data;
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  CDATA_SCHOOLLOGIC *schoolLogic = (CDATA_SCHOOLLOGIC *) entity_getComponentData((ENTITY *)space_getEntity(self->owner->space, "gameManager"), COMP_SCHOOLLOGIC);
  CDATA_TIMEMANAGER *timeData = (CDATA_TIMEMANAGER *) entity_getComponentData((ENTITY *)space_getEntity(self->owner->space, "gameManager"), COMP_TIMEMANAGER);

  //ONLY EXECUTE ONCE
  if(comData->counter == 0)
    generate_student(self);
  comData->counter++;
  
  // Graduate
  if(comData->semesterStarted == timeData->currentSemester - 8 && !comData->graduated) {
    int repIncrease = (int)(5 * (comData->gpa / 4.0f));
    SPACE *fg = game_getSpace(self->owner->space->game, "fg");
    ENTITY *studentManager = space_getEntity(fg, "studentManager");
    COMPONENT *studentManagerLogic = entity_getComponent(studentManager, COMP_STUDENTMANAGERLOGIC);
    schoolLogic->currentStudents--;
    schoolLogic->reputation += repIncrease;
    comp_studentManagerLogic_removeGraduate(studentManagerLogic, self->owner);
    list_remove(schoolLogic->students, comData->listNodePtr);
    comData->listNodePtr = list_insert_end(schoolLogic->alumni, self->owner);
    comData->graduated = true;
  }
}

void comp_studentData_initialize(COMPONENT *self, void *event) {
  CDATA_STUDENTDATA *comData = (CDATA_STUDENTDATA *)self->data;
  generate_student(self);
}

void comp_studentData(COMPONENT *self) {
  int lowValue = 0;
  int highValue = 20;
  
  CDATA_STUDENTDATA student = { 0 };
  
  student.name.first = "Samuel";
  student.name.last = "Valdez";
  student.techSkill = randomIntRange(lowValue, highValue);
  student.artSkill = randomIntRange(lowValue, highValue);
  student.designSkill = randomIntRange(lowValue, highValue);
  student.gpa = 4.0;
  student.motivation = randomIntRange(lowValue, highValue);
  student.yearStarted = 1989;
  student.counter = 0;
  student.graduated = false;
  student.listNodePtr = NULL;

  COMPONENT_INIT(self, COMP_STUDENTDATA, student);
  self->events.logicUpdate = comp_studentData_logicUpdate;
  self->events.initialize = comp_studentData_initialize;
}

void generate_student(COMPONENT *self) {
  CDATA_TIMEMANAGER *timeData = (CDATA_TIMEMANAGER *) entity_getComponentData((ENTITY *)space_getEntity(self->owner->space, "gameManager"), COMP_TIMEMANAGER);
  CDATA_STUDENTDATA *data = (CDATA_STUDENTDATA *)self->data;
  int gender = randomIntRange(1, 2);
  int lowValue = 0;
  int highValue = 20;
  GAME *owner = self->owner->space->game;
  TEXTFILE *namefile = (TEXTFILE *)dict_get(&self->owner->space->game->data.textfiles, "names/last");
  unsigned int totalNames = vector_size(&namefile->lines);
  char *lastname = (char *)vector_get(&namefile->lines, randomIntRange(0, totalNames - 1));
  char *firstname;

  data->name.last = lastname;

  if(gender == 1) {
    namefile = (TEXTFILE *) dict_get(&self->owner->space->game->data.textfiles, "names/first_male");
    totalNames = vector_size(&namefile->lines);
    firstname = (char *)vector_get(&namefile->lines, randomIntRange(0, totalNames - 1));
    data->name.first = firstname;
    data->gender = GEN_MALE;

    data->head = randomIntRange(1, MALE_HEAD_COUNT);
    data->face = randomIntRange(1, MALE_FACE_COUNT);
    data->hair = randomIntRange(1, MALE_HAIR_COUNT);
    data->body = randomIntRange(1, MALE_BODY_COUNT);
    data->legs = randomIntRange(1, MALE_LEGS_COUNT);
  }
  else {
    namefile = (TEXTFILE *) dict_get(&self->owner->space->game->data.textfiles, "names/first_female");
    totalNames = vector_size(&namefile->lines);
    firstname = (char *)vector_get(&namefile->lines, randomIntRange(0, totalNames - 1));
    data->name.first = firstname;
    data->gender = GEN_FEMALE;

    data->head = randomIntRange(1, FEMALE_HEAD_COUNT);
    data->face = randomIntRange(1, FEMALE_FACE_COUNT);
    data->hair = randomIntRange(1, FEMALE_HAIR_COUNT);
    data->body = randomIntRange(1, FEMALE_BODY_COUNT);
    data->legs = randomIntRange(1, FEMALE_LEGS_COUNT);
  }

  data->techSkill = randomIntRange(lowValue, highValue);
  data->artSkill = randomIntRange(lowValue, highValue);
  data->designSkill = randomIntRange(lowValue, highValue);

  if(data->techSkill >= data->artSkill && data->techSkill >= data->designSkill)
    data->major = M_TECH;
  else if(data->artSkill >= data->designSkill && data->artSkill >= data->techSkill)
    data->major = M_ART;
  else if(data->designSkill >= data->techSkill && data->designSkill >= data->artSkill)
    data->major = M_DESIGN;

  data->motivation = randomIntRange(25, 100);
  data->yearStarted = timeData->currentYear;
  data->semesterStarted = timeData->currentSemester;
}