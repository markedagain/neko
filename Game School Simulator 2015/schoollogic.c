/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "schoollogic.h"
#include "room.h"
#include "student.h"
#include "studentdata.h"
#include "../NekoEngine/linkedlist.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/sprite.h"
#include <math.h>

void comp_schoolLogic_initialize(COMPONENT *self, void *event) {
  CDATA_SCHOOLLOGIC *comData = (CDATA_SCHOOLLOGIC *)self->data;
  printf("\n\n\n\n\n\nWelcome To: %s\n\n\n\n\n\n", comData->schoolName);
}

void comp_schoolLogic_logicUpdate(COMPONENT *self, void *event) {
  /*EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_SCHOOLLOGIC *comData = (CDATA_SCHOOLLOGIC *)self->data;
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  */
  //printf(">>> %hu FPS <<<\n", self->owner->space->game->systems.time.currentFramesPerSecond);
}

void comp_schoolLogic_updateDataMonth(COMPONENT *self, CDATA_SCHOOLLOGIC *comData) {
  int i = 0;
  LIST_NODE *studentPtr;
  LIST_NODE *roomPtr;
  
  // Calculate incomingStudents
  if(comData->currentStudents < comData->studentCapacity) {
    comData->incomingStudents += 1 + comData->reputation;
    if(comData->incomingStudents > (comData->studentCapacity - comData->currentStudents)) {
      comData->incomingStudents = comData->studentCapacity - comData->currentStudents;
    }
  }
  else {
    comData->incomingStudents = 0;
  }

  //Add money
  comData->money += (int)floor((float)(comData->tuition * comData->currentStudents) / 6.0f);
  //Lose money
  //Go through list of rooms and pay upkeep
  roomPtr = comData->roomList->first;
  for(i = 0; i < comData->roomList->count; i++) {
    CDATA_ROOMLOGIC *roomData = (CDATA_ROOMLOGIC *)entity_getComponentData(roomPtr->data, COMP_ROOMLOGIC);
    comData->money -= roomData->upkeep;
  }

  // Add student stats
  studentPtr = comData->students->first;
  for(i = 0; i < comData->students->count; i++) {
    CDATA_STUDENTDATA *studentData = (CDATA_STUDENTDATA *)entity_getComponentData((ENTITY *)studentPtr->data, COMP_STUDENTDATA);
    studentData->techSkill += (int)(1 + comData->techBonus * ((float)studentData->motivation / 100.0));
    studentData->designSkill += (int)(1 + comData->designBonus * ((float)studentData->motivation / 100.0));
    studentData->artSkill += (int)(1 + comData->artBonus * ((float)studentData->motivation / 100.0));
    studentPtr = studentPtr->next;
  }

  printf("Students: %i/%i", comData->currentStudents, comData->studentCapacity);
  printf("       Incoming: %i\n", comData->incomingStudents);
  printf("Money: $%i", comData->money);
  printf("       Tuition: $%i\n", comData->tuition);
  printf("Rep: %i", comData->reputation);
  printf("              Alumni: %i\n", comData->alumni->count);
}

void comp_schoolLogic_updateDataSemester(COMPONENT *self, CDATA_SCHOOLLOGIC *comData) {
  ENTITY *newStudent;

  int i = 0;

  //Add students
  if(comData->incomingStudents > 0) {
    for(i = 0; i <= comData->incomingStudents; i++)
    {
      CDATA_STUDENTDATA *studentData;
      LIST_NODE *nodeptr;
      newStudent = space_addEntity(self->owner->space, arch_student, "Student");
      studentData = (CDATA_STUDENTDATA *)entity_getComponentData(newStudent, COMP_STUDENTDATA);
      nodeptr = list_insert_end(comData->students, newStudent);
      studentData->listNodePtr = nodeptr;
      comData->currentStudents++;
    }
    comData->incomingStudents = 0;
  }
}

void comp_schoolLogic_updateDataYear(COMPONENT *self, CDATA_SCHOOLLOGIC *comData) {
  
}

void comp_schoolLogic_constructRoom(COMPONENT *self, CDATA_SCHOOLLOGIC *comData, ROOM_TYPE roomType) {
  ENTITY *newRoom;
  CDATA_ROOMLOGIC *newRoomCompData;
  int floorToUse;
  int colToUse;
  int i = 0;

  // CHECK FOR OPEN BUILD SITE
  if(roomType == ROOMTYPE_LOBBY) {
    if(comData->rooms.coord[2][7] == NULL) {
      floorToUse = 2;
      colToUse = 7;
    }
    else if(comData->rooms.coord[1][7] == NULL) {
      floorToUse = 1;
      colToUse = 7;
    }
    else if(comData->rooms.coord[0][7] == NULL) {
      floorToUse = 0;
      colToUse = 7;
    }
    else {
      printf("NO MORE SPACE\n");
      return;
    }
  }
  else {
    int createdRoom = 0;
    for(i = 0; i < MAX_FLOORS * MAX_ROOMS_PER_FLOOR; i++) {
      int floor = i / MAX_ROOMS_PER_FLOOR;
      int col = i % MAX_ROOMS_PER_FLOOR;
      // If there is an empty space
      // And (the spot to the left is occupied and the spot next is not the end of the row)
      // Or (teh spot to the right is occupied)
      if((comData->rooms.coord[floor][col] == NULL)
      && ((comData->rooms.coord[floor][col + 1] && col + 1 < 15)
      || (comData->rooms.coord[floor][col - 1] && col - 1 > 0))){
        // Check if room under *remember that floors is reversed (2 is 1st floor 0 is 3rd floor)
        if(floor < 2) {
          if(comData->rooms.coord[floor + 1][col] == NULL)
            continue;
        }
        // Build new room
        floorToUse = floor;
        colToUse = col;
        createdRoom = 1;
        break;
      }
    }
    //return since no space is found
    if(createdRoom == 0) {
      printf("NO SPACE TO CONSTRUCT ROOM\n");
      return;
    }
  }
  
  newRoom = space_addEntity(self->owner->space, arch_room, NULL);
  newRoomCompData = (CDATA_ROOMLOGIC *)entity_getComponentData(newRoom, COMP_ROOMLOGIC);
  newRoomCompData->type = roomType;
  list_insert_end(comData->roomList, newRoom); //Add newRoom to the rooms list
  comData->rooms.coord[floorToUse][colToUse] = newRoom; // Construct Room
  

  //Show school layout
  for(i = 0; i < MAX_FLOORS * MAX_ROOMS_PER_FLOOR; i++) {
    int floor = i / MAX_ROOMS_PER_FLOOR;
    int col = i % MAX_ROOMS_PER_FLOOR;
    //printf(" (%i,%i) ", floor, col);
    if(comData->rooms.coord[floor][col])
      printf(" X ");
    else
      printf(" 0 ");
    if(col == 15)
      printf("\n");
  }
}

void comp_schoolLogic_listRooms(COMPONENT *self, CDATA_SCHOOLLOGIC *comData) {
  LIST_NODE *roomNode;
    if(comData->roomList->first != NULL) {
      roomNode = comData->roomList->first;
      do {
        ENTITY *room = (ENTITY *)roomNode->data;
        printf("1) ");
        printf(room->name);
        printf("\n");
        roomNode = roomNode->next;
      } while(roomNode != NULL);
    }
}

void comp_schoolLogic_listStudents(COMPONENT *self, CDATA_SCHOOLLOGIC *comData) {
  LIST_NODE *studentNode;
    if(comData->students->first != NULL) {
      studentNode = comData->students->first;
      do {
        ENTITY *student = (ENTITY *)studentNode->data;
        CDATA_STUDENTDATA *studentData = (CDATA_STUDENTDATA *)entity_getComponentData(student, COMP_STUDENTDATA);
        printf("1) ");
        printf("Name: %s %s", studentData->name.first, studentData->name.last);
        printf(" - Tech:%i Design:%i Art:%i\n", studentData->techSkill, studentData->designSkill, studentData->artSkill);
        printf("\n");
        studentNode = studentNode->next;
      } while(studentNode != NULL);
    }
}

void comp_schoolLogic_listAlumni(COMPONENT *self, CDATA_SCHOOLLOGIC *comData) {
  LIST_NODE *alumniNode;
    if(comData->students->first != NULL) {
      alumniNode = comData->alumni->first;
      do {
        ENTITY *alumni = (ENTITY *)alumniNode->data;
        CDATA_STUDENTDATA *alumniData = (CDATA_STUDENTDATA *)entity_getComponentData(alumni, COMP_STUDENTDATA);
        printf("1) ");
        printf("Name: %s %s\n", alumniData->name.first, alumniData->name.last);
        printf("\n");
        alumniNode = alumniNode->next;
      } while(alumniNode != NULL);
    }
}

void comp_schoolLogic_destroy(COMPONENT *self, void *event) {
  CDATA_SCHOOLLOGIC *comData = (CDATA_SCHOOLLOGIC *)self->data;
  list_destroy(comData->roomList);
  list_destroy(comData->students);
  list_destroy(comData->alumni);
}

void comp_schoolLogic(COMPONENT *self) {
  CDATA_SCHOOLLOGIC data = { 0 };
  data.schoolName = "Eduardo's Super Awesome Game School";
  data.money = 50000;
  data.tuition = 3000;
  data.studentCapacity = 0;
  data.currentStudents = 0;
  data.incomingStudents = 0;
  data.students = list_create();
  data.alumni = list_create();
  data.roomMaintainance = 0;
  data.roomList = list_create();
  data.reputation = 0;
  data.techBonus = 1;
  data.designBonus = 1;
  data.artBonus = 1;

  COMPONENT_INIT(self, COMP_SCHOOLLOGIC, data);
  self->events.logicUpdate = comp_schoolLogic_logicUpdate;
}