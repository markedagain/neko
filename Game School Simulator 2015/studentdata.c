/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

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
#define HEAD_COUNT 5
#define FACE_COUNT 5
#define HAIR_COUNT 5
#define BODY_COUNT 5
#define LEGS_COUNT 5

void comp_studentData_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_STUDENTDATA *comData = (CDATA_STUDENTDATA *)self->data;
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  CDATA_SCHOOLLOGIC *schoolLogic = (CDATA_SCHOOLLOGIC *) entity_getComponentData((ENTITY *)space_getEntity(self->owner->space, "gameManager"), COMP_SCHOOLLOGIC);
  CDATA_TIMEMANAGER *timeData = (CDATA_TIMEMANAGER *) entity_getComponentData((ENTITY *)space_getEntity(self->owner->space, "gameManager"), COMP_TIMEMANAGER);


  // float foo = 0;
  // float baz = 99.9;
  //ONLY EXECUTE ONCE
  if(comData->counter == 0)
    generate_student(self);
  comData->counter++;
  /*printf("\nName: %s %s\n", comData->name.first, comData->name.last);
  printf("Gender: %s\n", comData->gender);
  printf("Tech Skill: %d\n", comData->techSkill);
  printf("Art Skill: %d\n", comData->artSkill);
  printf("Design Skill: %d\n", comData->designSkill);
  printf("Motivation: %%%d\n", comData->motivation);
  printf("Year Started: %d\n", comData->yearStarted);*/
    // printf("Totally Random Float: %f\n", randomFloatRange(foo, baz));
  
  // Graduate
  if(comData->semesterStarted == timeData->currentSemester - 8 && !comData->graduated) {
    char message[80];
    int repIncrease = (int)(5 * (comData->gpa / 4.0f));
    schoolLogic->currentStudents--;
    schoolLogic->reputation += repIncrease;
    printf("\n%s %s has graduated! +%i Rep\n", comData->name.first, comData->name.last, repIncrease);
    list_remove(schoolLogic->students, comData->listNodePtr);
    comData->listNodePtr = list_insert_end(schoolLogic->alumni, self->owner);
    comData->graduated = true;
    sprintf(message, pushStrings[STRINGS_GRAD], comData->name.first, comData->name.last);
    comp_newsfeedlogic_push(self, message);
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
  data->head = randomIntRange(1, HEAD_COUNT);
  data->face = randomIntRange(1, FACE_COUNT);
  data->hair = randomIntRange(1, HAIR_COUNT);
  data->body = randomIntRange(1, BODY_COUNT);
  data->legs = randomIntRange(1, LEGS_COUNT);

  if(gender == 1) {
    namefile = (TEXTFILE *) dict_get(&self->owner->space->game->data.textfiles, "names/first_male");
    totalNames = vector_size(&namefile->lines);
    firstname = (char *)vector_get(&namefile->lines, randomIntRange(0, totalNames - 1));
    data->name.first = firstname;
    data->gender = GEN_MALE;
  }
  else {
    namefile = (TEXTFILE *) dict_get(&self->owner->space->game->data.textfiles, "names/first_female");
    totalNames = vector_size(&namefile->lines);
    firstname = (char *)vector_get(&namefile->lines, randomIntRange(0, totalNames - 1));
    data->name.first = firstname;
    data->gender = GEN_FEMALE;
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