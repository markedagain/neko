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
#include <math.h>
#include <string.h>
#include "roomactorlogic.h"
#include "roomactor.h"

void comp_schoolLogic_initialize(COMPONENT *self, void *event) {
  CDATA_SCHOOLLOGIC *comData = (CDATA_SCHOOLLOGIC *)self->data;
  printf("\n\n\n\n\n\nWelcome To: %s\n\n\n\n\n\n", comData->schoolName);
}

void comp_schoolLogic_frameUpdate(COMPONENT *self, void *event) {
  CDATA_SCHOOLLOGIC *comData = (CDATA_SCHOOLLOGIC *)self->data;


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
  // ENTITY *currMoney = 0;
  // char buffer[20];
  // VEC3 position = { 10, 10, 0 };
  // VEC4 color = { 0, 0, 1, 1 };
  LIST_NODE *studentPtr;
  LIST_NODE *roomPtr;
  // SPACE *uiSpace = game_getSpace(self->owner->space->game, "ui");
  // int prevMoney = comData->money;

  // Calculate incomingStudents
  if(comData->currentStudents < comData->studentCapacity) {
    comData->incomingStudents += 1 + (int)(comData->reputation * .1);
    if(comData->incomingStudents > (comData->studentCapacity - comData->currentStudents)) {
      comData->incomingStudents = comData->studentCapacity - comData->currentStudents;
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

  // Add student stats
  studentPtr = comData->students->first;
  for(i = 0; i < comData->students->count; i++) {
    CDATA_STUDENTDATA *studentData = (CDATA_STUDENTDATA *)entity_getComponentData((ENTITY *)studentPtr->data, COMP_STUDENTDATA);
    studentData->techSkill += (int)(1 + comData->techBonus * ((float)studentData->motivation / 100.0));
    studentData->designSkill += (int)(1 + comData->designBonus * ((float)studentData->motivation / 100.0));
    studentData->artSkill += (int)(1 + comData->artBonus * ((float)studentData->motivation / 100.0));
    studentPtr = studentPtr->next;
  }

  printf("Students: %i/%i (%i incoming)", comData->currentStudents, comData->studentCapacity, comData->incomingStudents);
  printf("       Incoming: %i\n", comData->incomingStudents);
  printf("Money: $%i", comData->money);
  printf("       Tuition: $%i\n", comData->tuition);
  printf("Rep: %i", comData->reputation);
  printf("              Alumni: %i\n", comData->alumni->count);
  /*
  if(!currMoney) {
    sprintf(buffer,"%d", comData->money);
    vec3_set(&position, -318, -100, 0);
    currMoney = genericText_create(uiSpace, &position, NULL, "fonts/gothic/20", buffer, &color);
  }
  else {
    sprintf(buffer, "%d", comData->money);
    genericText_setText(currMoney, buffer);
  }
  */
}

void comp_schoolLogic_updateDataSemester(COMPONENT *self, CDATA_SCHOOLLOGIC *comData) {
  ENTITY *newStudent;

  int i = 0;

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
}

void comp_schoolLogic_updateDataYear(COMPONENT *self, CDATA_SCHOOLLOGIC *comData) {
  
}

LIST* comp_schoolLogic_findBuildSpots(COMPONENT *ptr, ROOM_TYPE roomType, int roomSize) {
  int i = 0;
  CDATA_ROOMLOGIC *lastKnownRoomData = NULL;
  int distanceFromLastKnown = 47;
  CDATA_SCHOOLLOGIC *comData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(space_getEntity(game_getSpace(ptr->owner->space->game, "sim"), "gameManager"), COMP_SCHOOLLOGIC);

  if(comData->roomConstructed == TRUE) {
    printf("\n1 RPS (Room Per Second)!!!... its the law.\n");
    return NULL;
  }

  // CHECK FOR OPEN BUILD SITE
  if(roomType == ROOMTYPE_LOBBY) {
    if(comData->rooms.coord[2][7] == NULL) {
      LIST *legalSlots = list_create();
      POINT *spotPtr = (POINT *)malloc(sizeof(POINT));
        
      spotPtr->x = 7;
      spotPtr->y = 2;
      list_insert_end(legalSlots, (void *)spotPtr);
      return legalSlots;
    }
    else if(comData->rooms.coord[1][7] == NULL) {
      LIST *legalSlots = list_create();
      POINT *spotPtr = (POINT *)malloc(sizeof(POINT));
        
      spotPtr->x = 7;
      spotPtr->y = 1;
      list_insert_end(legalSlots, (void *)spotPtr);
      return legalSlots;
    }
    else if(comData->rooms.coord[0][7] == NULL) {
      LIST *legalSlots = list_create();
      POINT *spotPtr = (POINT *)malloc(sizeof(POINT));
        
      spotPtr->x = 7;
      spotPtr->y = 0;
      list_insert_end(legalSlots, (void *)spotPtr);
      return legalSlots;
    }
    else {
      printf("NO MORE SPACE\n");
      return NULL;
    }
  }
  else { // IF NOT A LOBBY
    BOOL openSlot[MAX_FLOORS][MAX_ROOMS_PER_FLOOR];
    LIST *legalSlots = list_create();
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

    // 3) Take out all spots which do not have a room below them
    for(i = 0; i < MAX_FLOORS * MAX_ROOMS_PER_FLOOR; i++) {
       int floor = i / MAX_ROOMS_PER_FLOOR;
       int col = i % MAX_ROOMS_PER_FLOOR;

       // Remember that the top floor is 0 and bottom floor is 2
       if(openSlot[floor][col] == TRUE && openSlot[floor + 1][col] == TRUE && floor != 2)
         openSlot[floor][col] = FALSE;
       if((col == 7 || col == 8) && floor != 2)
         openSlot[floor][col] = FALSE;
    }

    // 4) Take out all spots which do not have a building either to their left or right
    for(i = 0; i < MAX_FLOORS * MAX_ROOMS_PER_FLOOR; i++) {
       int floor = i / MAX_ROOMS_PER_FLOOR;
       int col = i % MAX_ROOMS_PER_FLOOR;

       if(comData->rooms.coord[floor][col]) {
         lastKnownRoomData = (CDATA_ROOMLOGIC *)entity_getComponentData(comData->rooms.coord[floor][col], COMP_ROOMLOGIC);
         lastFilledCol = col;
         lastFilledColSize = lastKnownRoomData->size - 1;
       }

       if (openSlot[floor][col] == TRUE
       && ((comData->rooms.coord[floor][col - 1] == NULL && col - 1 > lastFilledCol + lastFilledColSize) || col == 0)
       && (openSlot[floor][col + roomSize] == TRUE || col + roomSize > 15))
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
      POINT *spotPtr = (POINT *)malloc(sizeof(POINT));
        
      if(openSlot[floor][col] == TRUE) {
        spotPtr->x = col;
        spotPtr->y = floor;

        list_insert_end(legalSlots, (void *)spotPtr);
      }
    }

    return legalSlots;
  }

  return NULL;
}

void comp_schoolLogic_findRooms(COMPONENT *comp, LIST *roomList) {
  CDATA_SCHOOLLOGIC *comData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(space_getEntity(game_getSpace(comp->owner->space->game, "sim"), "gameManager"), COMP_SCHOOLLOGIC);
  int i, j;

  for (i = 0; i < 3; ++i) {
    for (j = 0; j < 15; ++j) {
      if (i == 2 && j == 7)
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
  case(ROOMTYPE_LOBBY):
    sprite->source = "rooms/frontdoor";
    break;
  case(ROOMTYPE_CLASS):
    sprite->source = "rooms/template";
    break;
  case(ROOMTYPE_LIBRARY):
    sprite->source = "rooms/template2";
    break;
  case(ROOMTYPE_TEAMSPACE):
    sprite->source = "rooms/template3";
    break;
  default:
    sprite->source = "rooms/template";
    break;
  }
}

int comp_schoolLogic_getRoomSize(ROOM_TYPE type) {
  if(type == ROOMTYPE_CLASS)
    return 1;
  else if(type == ROOMTYPE_LOBBY || type == ROOMTYPE_LIBRARY)
    return 2;
  else if(type == ROOMTYPE_TEAMSPACE)
    return 3;

  return 1;
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
  data.roomConstructed = FALSE;

  COMPONENT_INIT(self, COMP_SCHOOLLOGIC, data);
  self->events.logicUpdate = comp_schoolLogic_logicUpdate;
  self->events.frameUpdate = comp_schoolLogic_frameUpdate;
  self->events.initialize = comp_schoolLogic_initialize;
}