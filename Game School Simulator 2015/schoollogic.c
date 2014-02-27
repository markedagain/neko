/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "schoollogic.h"
#include "room.h"
#include "student.h"
#include "studentdata.h"
#include "../NekoEngine/linkedlist.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/sprite.h"
#include "../Nekoengine/spritetext.h"
#include "../NekoEngine/generictext.h"
#include "../NekoEngine/entity.h"
#include "random.h"
#include <math.h>
#include <string.h>
#include "roomactorlogic.h"
#include "roomactor.h"
#include "timemanager.h"

void comp_schoolLogic_initialize(COMPONENT *self, void *event) {
  CDATA_SCHOOLLOGIC *comData = (CDATA_SCHOOLLOGIC *)self->data;
  printf("\n\n\n\n\n\nWelcome To: %s\n\n\n\n\n\n", comData->schoolName);
}

void comp_schoolLogic_frameUpdate(COMPONENT *self, void *event) {
  CDATA_SCHOOLLOGIC *comData = (CDATA_SCHOOLLOGIC *)self->data;


}

void comp_schoolLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_SCHOOLLOGIC *comData = (CDATA_SCHOOLLOGIC *)self->data;
  SPACE *uiSpace = game_getSpace(self->owner->space->game, "ui");
  VEC3 position;
  VEC4 color;  
  // Display $$$ on screen
  if (comData->currMoney != comData->money) {    
    if (!comData->moneyUI) {
      vec3_set(&position, 320, 180, 0);
      vec4_set(&color, 0, 0, 1, 1 );
      sprintf(comData->buffer, "$%li", comData->money);
      comData->moneyUI = genericText_create(uiSpace, &position, NULL, "fonts/gothic/20", comData->buffer, &color, TEXTALIGN_RIGHT, TEXTALIGN_TOP);
    }
    sprintf(comData->buffer, "$%li", comData->money);
    genericText_setText(comData->moneyUI, comData->buffer);
    // sprintf(buffer,"$%d", comData->money);
    // moneyUI = 
    comData->currMoney = comData->money;
  }
}

void comp_schoolLogic_updateDataMonth(COMPONENT *self, CDATA_SCHOOLLOGIC *comData) {
  int i = 0;
  SPACE *uiSpace = game_getSpace(self->owner->space->game, "ui");
  LIST_NODE *studentPtr;
  LIST_NODE *roomPtr;

  // Calculate incomingStudents
  if(comData->currentStudents < comData->studentCapacity + comData->expectedGraduates) {
    comData->incomingStudents += 1 + (int)(comData->reputation * .1);
    if(comData->incomingStudents > (comData->studentCapacity - comData->currentStudents) + comData->expectedGraduates) {
      comData->incomingStudents = comData->studentCapacity - comData->currentStudents + comData->expectedGraduates;
    }
  }
  else {
    comData->incomingStudents = 0;
  }

  //Add money
  studentPtr = comData->students->first;
  for(i = 0; i < comData->students->count; i++) {
    CDATA_STUDENTDATA *studentData = (CDATA_STUDENTDATA *)entity_getComponentData((ENTITY *)studentPtr->data, COMP_STUDENTDATA);
    comData->money += studentData->tuition / 6;
  }

  //Lose money
  //Go through list of rooms and pay upkeep
  roomPtr = comData->roomList->first;
  for(i = 0; i < comData->roomList->count; i++) {
    CDATA_ROOMLOGIC *roomData = (CDATA_ROOMLOGIC *)entity_getComponentData(roomPtr->data, COMP_ROOMLOGIC);
    comData->money -= roomData->upkeep;
  }

  // Modify student stats
  studentPtr = comData->students->first;
  for(i = 0; i < comData->students->count; i++) {
    CDATA_STUDENTDATA *studentData = (CDATA_STUDENTDATA *)entity_getComponentData((ENTITY *)studentPtr->data, COMP_STUDENTDATA);
    // Calculate increase (calculated as float because its used to calculate GPA)
    studentData->techIncrease += comData->techBonus * (float)studentData->motivation / 100.0f;
    studentData->designIncrease += comData->designBonus * (float)studentData->motivation / 100.0f;
    studentData->artIncrease += comData->artBonus * (float)studentData->motivation / 100.0f;

    // Skills
    studentData->techSkill += (int)(comData->techBonus * (float)studentData->motivation / 100.0f);
    studentData->designSkill += (int)(comData->designBonus * (float)studentData->motivation / 100.0f);
    studentData->artSkill += (int)(comData->artBonus * (float)studentData->motivation / 100.0f);

    studentPtr = studentPtr->next;
  }

  printf("Students: %i/%i (%i incoming)", comData->currentStudents, comData->studentCapacity, comData->incomingStudents);
  printf("       Incoming: %i\n", comData->incomingStudents);
  printf("Money: $%i", comData->money);
  printf("       Tuition: $%i\n", comData->tuition);
  printf("Rep: %i", comData->reputation);
  printf("              Alumni: %i\n", comData->alumni->count);

}
/*
void comp_schoolLogic_updateMoneyText(COMPONENT *self) {
  SPACE *uiSpace = game_getSpace(self->owner->space->game, "ui");
  VEC3 position;
  VEC4 color;
  if (!comData

  genericText_setText(comData->moneyUI, comData->buffer);
}
*/
void comp_schoolLogic_updateDataSemester(COMPONENT *self, CDATA_SCHOOLLOGIC *comData) {
  ENTITY *newStudent;
  LIST_NODE *studentPtr;
  CDATA_TIMEMANAGER *timeData = (CDATA_TIMEMANAGER *) entity_getComponentData((ENTITY *)space_getEntity(self->owner->space, "gameManager"), COMP_TIMEMANAGER);
  int i = 0;
  int lowValue = -50;
  int highValue = 50;

  //Add students
  if(comData->incomingStudents > 0) {
    for(i = 0; i < comData->incomingStudents; i++)
    {
      CDATA_STUDENTDATA *studentData;
      LIST_NODE *nodeptr;
      newStudent = space_addEntity(self->owner->space, arch_student, "Student");
      studentData = (CDATA_STUDENTDATA *)entity_getComponentData(newStudent, COMP_STUDENTDATA);
      nodeptr = list_insert_end(comData->students, newStudent);
      studentData->listNodePtr = nodeptr;
      comData->currentStudents++;
      studentData->tuition = comData->tuition;
      printf("Motivation: %%%d\n", studentData->motivation);
    }
    comData->incomingStudents = 0;
  }

  studentPtr = comData->students->first;
  for(i = 0; i < comData->students->count; i++) {
    CDATA_STUDENTDATA *studentData = (CDATA_STUDENTDATA *)entity_getComponentData((ENTITY *)studentPtr->data, COMP_STUDENTDATA);

    // GPA
    if(studentData->major == M_TECH) {
      int semestersPassed = timeData->currentSemester - studentData->semesterStarted;
      studentData->gradePoints += ((float)studentData->techIncrease / (comData->techBonus * 6)) * 4.0f;
      if(semestersPassed != 0) {
        studentData->gpa = studentData->gradePoints / semestersPassed;
      }
    }
    if(studentData->major == M_DESIGN) {
      int semestersPassed = timeData->currentSemester - studentData->semesterStarted;
      studentData->gradePoints += ((float)studentData->designIncrease / (comData->designBonus * 6)) * 4.0f;
      if(semestersPassed != 0) {
        studentData->gpa = studentData->gradePoints / semestersPassed;
      }
    }
    if(studentData->major == M_ART) {
      int semestersPassed = timeData->currentSemester - studentData->semesterStarted;
      studentData->gradePoints += ((float)studentData->artIncrease / (comData->artBonus * 6)) * 4.0f;
      if(semestersPassed != 0) {
        studentData->gpa = studentData->gradePoints / semestersPassed;
      }
    }
    studentData->techIncrease = 0;
    studentData->designIncrease = 0;
    studentData->artIncrease = 0;

    // Life
    studentData->lifeModifier = randomIntRange(lowValue, highValue);
    studentData->motivation += studentData->lifeModifier;
    if(studentData->motivation < 0)
      studentData->motivation = 0;
    if(studentData->motivation > 100)
      studentData->motivation = 100;

    studentPtr = studentPtr->next;

    // Drop students below the min GPA 
    if(studentData->gpa < comData->minGpa) {
      printf("\n%s %s has droped out due to a %1.1f GPA!\n", studentData->name.first, studentData->name.last, studentData->gpa);
      comData->currentStudents--;
      entity_destroy(list_remove(comData->students, studentData->listNodePtr));
      continue;
    }

    // Drop students whos motivation has reached 0 
    else if(studentData->motivation == 0) {
      printf("\n%s %s has droped out due to losing all motivation!\n", studentData->name.first, studentData->name.last);
      comData->currentStudents--;
      entity_destroy(list_remove(comData->students, studentData->listNodePtr));
      continue;
    }
  }

  comData->expectedGraduates = 0;

  studentPtr = comData->students->first;
  for(i = 0; i < comData->students->count; i++) {
    CDATA_STUDENTDATA *studentData = (CDATA_STUDENTDATA *)entity_getComponentData((ENTITY *)studentPtr->data, COMP_STUDENTDATA);
    if(studentData->semesterStarted == timeData->currentSemester - 7 && !studentData->graduated)
      comData->expectedGraduates++;
  }
}

void comp_schoolLogic_updateDataYear(COMPONENT *self, CDATA_SCHOOLLOGIC *comData) {
  
}

void comp_schoolLogic_findBuildSpots(COMPONENT *ptr, ROOM_TYPE roomType, int roomSize, LIST *legalSlots) {
  int i = 0;
  CDATA_ROOMLOGIC *lastKnownRoomData = NULL;
  int distanceFromLastKnown = 47;
  CDATA_SCHOOLLOGIC *comData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(space_getEntity(game_getSpace(ptr->owner->space->game, "sim"), "gameManager"), COMP_SCHOOLLOGIC);

  if(comData->roomConstructed == TRUE) {
    printf("\n1 RPS (Room Per Second)!!!... its the law.\n");
    return;
  }

  // CHECK FOR OPEN BUILD SITE
  if(roomType == ROOMTYPE_LOBBY) {
    if(comData->rooms.coord[2][7] == NULL) {
      POINT *spotPtr = (POINT *)malloc(sizeof(POINT));
        
      spotPtr->x = 7;
      spotPtr->y = 2;
      list_insert_end(legalSlots, (void *)spotPtr);
      return;
    }
    else if(comData->rooms.coord[1][7] == NULL) {
      POINT *spotPtr = (POINT *)malloc(sizeof(POINT));
        
      spotPtr->x = 7;
      spotPtr->y = 1;
      list_insert_end(legalSlots, (void *)spotPtr);
      return;
    }
    else if(comData->rooms.coord[0][7] == NULL) {
      POINT *spotPtr = (POINT *)malloc(sizeof(POINT));
        
      spotPtr->x = 7;
      spotPtr->y = 0;
      list_insert_end(legalSlots, (void *)spotPtr);
      return;
    }
    else {
      printf("NO MORE SPACE\n");
      return;
    }
  }
  else { // IF NOT A LOBBY
    BOOL openSlot[MAX_FLOORS][MAX_ROOMS_PER_FLOOR];
    int createdRoom = 0;
    int j = 0;
    int k = 0;
    int lastFilledCol = -1;
    int lastFilledColSize = -1;

    /****************************************************
    FIND BUILD SPOTS
    1) Set all spots to true
    1.5) Take out all spots without a lobby on their floor
    2) Take out all spots with a room already in them
    3) Take out all spots which do not have a room below them and lobby spots
    4) Take out all spots which do not have a building either to their left or right
    5) Take out all spots which do not have enough room for the length of the room
    6) Return a list of remaining rooms available
    *****************************************************/
    // 1) Set all spots to true
    for(i = 0; i < MAX_FLOORS * MAX_ROOMS_PER_FLOOR; i++) {
       int floor = i / MAX_ROOMS_PER_FLOOR;
       int col = i % MAX_ROOMS_PER_FLOOR;
       openSlot[floor][col] = TRUE;
    }

    // 1.5) Take out all spots without a lobby on their floor
    for(i = 0; i < MAX_FLOORS * MAX_ROOMS_PER_FLOOR; i++) {
       int floor = i / MAX_ROOMS_PER_FLOOR;
       int col = i % MAX_ROOMS_PER_FLOOR;

       if(comData->rooms.coord[2][7] == NULL && floor == 2)
         openSlot[floor][col] = FALSE;
       if(comData->rooms.coord[1][7] == NULL && floor == 1)
         openSlot[floor][col] = FALSE;
       if(comData->rooms.coord[0][7] == NULL && floor == 0)
         openSlot[floor][col] = FALSE;
    }

    // 2) Take out all spots with a room already in them
    for(i = 0; i < MAX_FLOORS * MAX_ROOMS_PER_FLOOR; i++) {
       int floor = i / MAX_ROOMS_PER_FLOOR;
       int col = i % MAX_ROOMS_PER_FLOOR;
       
       if(comData->rooms.coord[floor][col]) {
         CDATA_ROOMLOGIC *otherRoomData = (CDATA_ROOMLOGIC *)entity_getComponentData(comData->rooms.coord[floor][col], COMP_ROOMLOGIC);
         for(j = 0; j < otherRoomData->size; j++) {
           openSlot[floor][col + j] = FALSE;
         }
       }
    }

    // 4) Take out all spots which do not have a building either to their left or right
    for(i = 0; i < MAX_FLOORS * MAX_ROOMS_PER_FLOOR; i++) {
       int floor = i / MAX_ROOMS_PER_FLOOR;
       int col = i % MAX_ROOMS_PER_FLOOR;

       if(col == 0) {
         lastFilledCol = -1;
         lastFilledColSize = -1;
       }

       if(comData->rooms.coord[floor][col]) {
         lastKnownRoomData = (CDATA_ROOMLOGIC *)entity_getComponentData(comData->rooms.coord[floor][col], COMP_ROOMLOGIC);
         lastFilledCol = col;
         lastFilledColSize = lastKnownRoomData->size - 1;
       }

       if (openSlot[floor][col] == TRUE
       && (comData->rooms.coord[floor][col - 1] == NULL && col - 1 > lastFilledCol + lastFilledColSize)
       && (openSlot[floor][col + roomSize] == TRUE || col + roomSize > 15))
         openSlot[floor][col] = FALSE;
    }

    // 3) Take out all spots which do not have a room below them
    for(i = 0; i < MAX_FLOORS * MAX_ROOMS_PER_FLOOR; i++) {
       int floor = i / MAX_ROOMS_PER_FLOOR;
       int col = i % MAX_ROOMS_PER_FLOOR;

       // Check every slot of the desired room
       for(j = 0; j < roomSize; j++) {
         // Remember that the top floor is 0 and bottom floor is 2
         if(openSlot[floor][col] == TRUE && openSlot[floor + 1][col + j] == TRUE && floor != 2)
         {
           openSlot[floor][col] = FALSE;
         }
       }

       // Take out Lobby slots
       if((col == 7 || col == 8) && floor != 2)
         openSlot[floor][col] = FALSE;
    }

    // 5) Check to make sure size of room does not interfere with an existing room
    for(i = 0; i < MAX_FLOORS * MAX_ROOMS_PER_FLOOR; i++) {
       int floor = i / MAX_ROOMS_PER_FLOOR;
       int col = i % MAX_ROOMS_PER_FLOOR;

       if(openSlot[floor][col] == TRUE) {
         for(j = 0; j < roomSize; j++) {
           if(comData->rooms.coord[floor][col + j] == NULL)
             continue;
           else
            openSlot[floor][col] = FALSE;
         }
       }
    }

    // 6) Return a list of remaining rooms available
    for(i = 0; i < MAX_FLOORS * MAX_ROOMS_PER_FLOOR; i++) {
      int floor = i / MAX_ROOMS_PER_FLOOR;
      int col = i % MAX_ROOMS_PER_FLOOR;
      
        
      if(openSlot[floor][col] == TRUE) {
        POINT *spotPtr = (POINT *)malloc(sizeof(POINT));
        spotPtr->x = col;
        spotPtr->y = floor;

        list_insert_end(legalSlots, (void *)spotPtr);
      }
    }

    return;
  }

  return;
}

void comp_schoolLogic_findRooms(COMPONENT *comp, LIST *roomList) {
  CDATA_SCHOOLLOGIC *comData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(space_getEntity(game_getSpace(comp->owner->space->game, "sim"), "gameManager"), COMP_SCHOOLLOGIC);
  int i, j;

  for (i = 0; i < 3; ++i) {
    for (j = 0; j < 15; ++j) {
      if (j == 7)
        continue;
      if (comData->rooms.coord[i][j] != NULL) {
        VEC3 *room = (VEC3 *)malloc(sizeof(VEC3));
        CDATA_ROOMLOGIC *roomData = (CDATA_ROOMLOGIC *)entity_getComponentData(comData->rooms.coord[i][j], COMP_ROOMLOGIC);
        room->x = (float)j;
        room->y = (float)i;
        room->z = (float)roomData->size;
        list_insert_end(roomList, room);
      }
    }
  }
}

void comp_schoolLogic_constructRoom(COMPONENT *ptr, ROOM_TYPE roomType, int roomSize, int floorToUse, int colToUse) {
  ENTITY *newRoom;
  ENTITY *newRoomActor;
  CDATA_ROOMLOGIC *newRoomCompData;
  CDATA_ACTORLOGIC *actorCompData;
  SPACE *simSpace = game_getSpace(ptr->owner->space->game, "sim");
  SPACE *mg = game_getSpace(ptr->owner->space->game, "mg");
  ENTITY *entity = space_getEntity(simSpace, "gameManager");
  CDATA_SCHOOLLOGIC *comData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(entity, COMP_SCHOOLLOGIC);
  VEC3 middle;
  float squareSize = 80.0f;
  CDATA_SPRITE *sprite;
  
  middle.z = 0;
  middle.y = (2.5f - floorToUse) * squareSize;

  // CREATE ROOM
  newRoom = space_addEntity(simSpace, arch_room, NULL);
  newRoomCompData = (CDATA_ROOMLOGIC *)entity_getComponentData(newRoom, COMP_ROOMLOGIC);
  newRoomCompData->type = roomType;
  list_insert_end(comData->roomList, newRoom); //Add newRoom to the rooms list
  comData->rooms.coord[floorToUse][colToUse] = newRoom; // Construct Room
  comData->roomConstructed = TRUE;

  // CREATE ACTOR
  switch (roomSize) {
    case (1):
      middle.x = (colToUse - 7.5f) * squareSize;
      break;
    case (2):
      middle.x = (colToUse - 8.0f) * squareSize + squareSize;
      break;
    case (3):
      middle.x = (colToUse - 8.5f) * squareSize + squareSize + squareSize;
      break;
    }
  newRoomActor = space_addEntityAtPosition(mg, arch_roomActor, "roomActor", &middle);
  actorCompData = (CDATA_ACTORLOGIC *)entity_getComponentData(newRoomActor, COMP_ROOMACTORLOGIC);
  actorCompData->type = roomType;
  sprite = (CDATA_SPRITE *)entity_getComponentData(newRoomActor, COMP_SPRITE);
  switch (roomType) {
    case ROOMTYPE_LOBBY:
        sprite->source = "rooms/frontdoor";
        break;
    case ROOMTYPE_CLASS:
      sprite->source = "rooms/class";
      break;
    case ROOMTYPE_LIBRARY:
      sprite->source = "rooms/library";
      break;
    case ROOMTYPE_TEAMSPACE:
      sprite->source = "rooms/teamspace";
      break;
    case ROOMTYPE_CAFETERIA:
      sprite->source = "rooms/cafeteria";
      break;
    case ROOMTYPE_STORE:
      sprite->source = "rooms/store";
      break;
    case ROOMTYPE_OFFICES:
      sprite->source = "rooms/offices";
      break;
    case ROOMTYPE_AUDITORIUM:
      sprite->source = "rooms/auditorium";
      break;
    case ROOMTYPE_TUTORING:
      sprite->source = "rooms/tutoring";
      break;
    case ROOMTYPE_WIFI:
      sprite->source = "rooms/wifi";
      break;
    case ROOMTYPE_RECREATION:
      sprite->source = "rooms/recreation";
      break;
    case ROOMTYPE_FIGURE:
      sprite->source = "rooms/figure";
      break;
    case ROOMTYPE_POTTERY:
      sprite->source = "rooms/library";
      break;
  }
}

int comp_schoolLogic_getRoomSize(ROOM_TYPE type) {
  if(type == ROOMTYPE_CLASS || type == ROOMTYPE_STORE || type == ROOMTYPE_OFFICES || type == ROOMTYPE_TUTORING || type == ROOMTYPE_WIFI)
    return 1;
  else if(type == ROOMTYPE_LOBBY || type == ROOMTYPE_LIBRARY || type == ROOMTYPE_RECREATION || type == ROOMTYPE_FIGURE || type == ROOMTYPE_POTTERY)
    return 2;
  else if(type == ROOMTYPE_TEAMSPACE || type == ROOMTYPE_CAFETERIA || type == ROOMTYPE_AUDITORIUM)
    return 3;

  return 1;
}

int comp_schoolLogic_getRoomCost(ROOM_TYPE type) {
  switch (type) {
    case ROOMTYPE_LOBBY:
      return 100000;

    case ROOMTYPE_CLASS:
      return 40000;

    case ROOMTYPE_LIBRARY:
      return 50000;

    case ROOMTYPE_TEAMSPACE:
      return 75000;

    case ROOMTYPE_CAFETERIA:
      return 100000;

    case ROOMTYPE_STORE:
      return 75000;

    case ROOMTYPE_OFFICES:
      return 50000;

    case ROOMTYPE_AUDITORIUM:
      return 150000;

    case ROOMTYPE_TUTORING:
      return 30000;

    case ROOMTYPE_WIFI:
      return 20000;

    case ROOMTYPE_RECREATION:
      return 30000;

    case ROOMTYPE_FIGURE:
      return 30000;

    case ROOMTYPE_POTTERY:
      return 60000;

    default:
      printf("ERROR: Unkown room!!\n");
      break;
  }
  return 0;
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
        printf(" - Tech:%i Design:%i Art:%i Motivation:%%%d GPA:%1.1f\n", studentData->techSkill, studentData->designSkill, studentData->artSkill, studentData->motivation, studentData->gpa);
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
  data.money = 100000;
  data.tuition = 12000;
  data.minIncomingGpa = 2.0f;
  data.minGpa = 1.8f;
  data.studentCapacity = 0;
  data.currentStudents = 0;
  data.incomingStudents = 0;
  data.expectedGraduates = 0;
  data.students = list_create();
  data.alumni = list_create();
  data.roomMaintainance = 0;
  data.roomList = list_create();
  data.reputation = 0;
  data.techBonus = 1;
  data.designBonus = 1;
  data.artBonus = 1;
  data.motivationBonus = 0;
  data.roomConstructed = FALSE;
  data.currMoney = 0;

  COMPONENT_INIT(self, COMP_SCHOOLLOGIC, data);
  self->events.logicUpdate = comp_schoolLogic_logicUpdate;
  self->events.frameUpdate = comp_schoolLogic_frameUpdate;
  self->events.initialize = comp_schoolLogic_initialize;
  self->events.destroy = comp_schoolLogic_destroy;
}