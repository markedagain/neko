/******************************************************************************
Filename: studentactorlogic.c

Project Name: Game School Simulator 2015

Author: Tai Der Hui

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "studentactorlogic.h"
#include "genericsprite.h"
#include "generictext.h"
#include "multisprite.h"
#include "random.h"
#include "studentmanagerlogic.h"
#include "popText.h"
#include "mousebox.h"
#include "timemanager.h"
#include "inspectionscreenlogic.h"
#include <string.h>

#define STUDENT_OFFSET 8.0f
#define FADE_TIME 1.0f
#define INDIVIDUAL_ROOM_SIZE 80.0f
#define ROOM_X_OFFSET -25.0f
#define ANIMATION_TIME 0.3f

void comp_studentActorLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_STUDENTACTOR *data = (CDATA_STUDENTACTOR *)self->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  VEC3 pos = { 0 };
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  SPACE *ui = game_getSpace(self->owner->space->game, "ui");
  ENTITY *inspectionScreen = space_getEntity(ui, "inspection_screen");
  CDATA_INSPECTIONSCREEN *inspectData = (CDATA_INSPECTIONSCREEN *)entity_getComponentData(inspectionScreen, COMP_INSPECTIONSCREENLOGIC);

  if (mbox->entered) {
    ENTITY *created;
    VEC3 position = { 0, 30.0f, 0 };
    VEC4 color = { 0, 0, 0, 1.0f };
    CDATA_STUDENTDATA *studentData = (CDATA_STUDENTDATA *)entity_getComponentData(data->studentPtr, COMP_STUDENTDATA);
    char buffer[30];
    sprintf(buffer, "%s %s", studentData->name.first, studentData->name.last);
    created = genericText_create(self->owner->space, &position, "nameText", "fonts/gothic/12", buffer, &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
    entity_attach(created, self->owner);
    comp_studentActorLogic_flipText(created);
  }

  if(mbox->left.pressed && randomIntRange(0, 3) == 0)
    sound_playSound(&self->owner->space->game->systems.sound, "oh");

  // name, major, 3 stats, gpa, motivation, expected graduation year
  if (mbox->left.pressed && !data->triggered) {
    CDATA_STUDENTDATA *studentData = (CDATA_STUDENTDATA *)entity_getComponentData(data->studentPtr, COMP_STUDENTDATA);
    SPACE *sim = game_getSpace(self->owner->space->game, "sim");
    ENTITY *gameManager = (ENTITY *)space_getEntity(sim, "gameManager");
    CDATA_TIMEMANAGER *timeData = (CDATA_TIMEMANAGER *)entity_getComponentData(gameManager, COMP_TIMEMANAGER);

    if (inspectData->posActive) {
      inspectData->clear = true;
      inspectData->posActive = false;
    }
    // name
    sprintf(inspectData->nameBuffer, "%s\n%s", studentData->name.first, studentData->name.last);

    // major
    switch (studentData->major) {
    case M_TECH:
      strcpy(inspectData->major, "Programmer");
      break;
    case M_ART:
      strcpy(inspectData->major, "Artist");
      break;
    case M_DESIGN:
      strcpy(inspectData->major, "Designer");
      break;
    }

    // quote
    sprintf(inspectData->trait, "Traits:\n%s\n%s\n%s", studentData->trait1, studentData->trait2, studentData->trait3);

    // gpa
    sprintf(inspectData->GPA, "GPA: %.2f", studentData->gpa);

    // motivation
    sprintf(inspectData->motivation, "Motivation: %.2d%%", studentData->motivation);

    // expected graduation
    sprintf(inspectData->expectedGraduationYear, "Graduation: %d", studentData->yearStarted + 4);
    
    inspectData->active = true;
    inspectData->studentActive = true;
    inspectData->triggered = true;
    data->triggered = true;
  }
  
  else if (mbox->left.pressed && !data->triggered && inspectData->studentActive) {
    inspectData->clear = true;
    inspectData->studentActive = false;
  }
  
  else if (!mbox->left.pressed)
    data->triggered = false;

  if (mbox->exited) {
    ENTITY *text = entity_getChild(self->owner, "nameText");
    if (text)
      entity_destroy(text);
  }

  data->lifeTimer += (float)self->owner->space->game->systems.time.dt;

  if (!data->setSprite) {
    VEC3 position = { 0 };
    COMPONENT *multiSprite = entity_getComponent(self->owner, COMP_MULTISPRITE);
    ENTITY *legs;
    ENTITY *head;
    ENTITY *face;
    ENTITY *body;
    ENTITY *hair;

    // creating the generic sprites
    legs = genericSprite_create(self->owner->space, &position, NULL, data->legs);
    head = genericSprite_create(self->owner->space, &position, NULL, data->head);
    face = genericSprite_create(self->owner->space, &position, NULL, data->face);
    body = genericSprite_create(self->owner->space, &position, NULL, data->body);
    hair = genericSprite_create(self->owner->space, &position, NULL, data->hair);

    data->legsPointer = legs;

    // setting the student actor's multisprite
    multiSprite_addSprite(multiSprite, legs);
    multiSprite_addSprite(multiSprite, head);
    multiSprite_addSprite(multiSprite, face);
    multiSprite_addSprite(multiSprite, body);
    multiSprite_addSprite(multiSprite, hair);

    data->setSprite = true;
  }

  if (data->outerState == OS_LEFT || data->outerState == OS_RIGHT || data->outerState == OS_WALKTODOOR) {
    data->animationTimer += (float)self->owner->space->game->systems.time.dt;
    if (data->animationTimer > ANIMATION_TIME) {
      switch (data->currentFrame) {
        // standing
        case 0:
          __studentActorLogic_setLegs(self, AF_WALK1);
          data->currentFrame = 1;
          break;
        case 1:
          __studentActorLogic_setLegs(self, AF_WALK2);
          data->currentFrame = 2;
          break;
        case 2:
          __studentActorLogic_setLegs(self, AF_WALK1);
          data->currentFrame = 1;
          break;
        }
      data->animationTimer = 0;
    }
  }

  if(self->owner->space->systems.camera.transform.scale.x <= 0.65f && data->zoomedOut == false) {
    COMPONENT *multiSprite = entity_getComponent(self->owner, COMP_MULTISPRITE);
    comp_mouseBox_setInactive(mbox);
    multiSprite_setVisible(multiSprite, false);
    data->zoomedOut = true;
  }

  if(self->owner->space->systems.camera.transform.scale.x > 0.65f && data->zoomedOut == true) {
    COMPONENT *multiSprite = entity_getComponent(self->owner, COMP_MULTISPRITE);
    mbox->active = true;
    multiSprite_setVisible(multiSprite, true);
    data->zoomedOut = false;
  }

  if (data->lifeTimer > data->lifetime) {
    data->outerState = OS_WALKTODOOR;
    data->innerState = IS_ENTER;
    data->lifetime = 10000.0f;
  }

  comp_studentActorLogic_updateState(self);
}

void comp_studentActorLogic_flipSprite(COMPONENT *self) {
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  CDATA_STUDENTACTOR *data = (CDATA_STUDENTACTOR *)self->data;
  ENTITY *text = entity_getChild(self->owner, "nameText");
  
  if (data->velocity < 0) {
    trans->scale.x = -1.0f;
    if (text)
      comp_studentActorLogic_flipText(text);
  }

  else {
    trans->scale.x = 1.0f;
    if (text)
      comp_studentActorLogic_flipText(text);
  }
}

void comp_studentActorLogic_flipText(ENTITY *text) {
   CDATA_TRANSFORM *parentTrans = (text->parent == NULL ? NULL : (CDATA_TRANSFORM *)entity_getComponentData(text->parent, COMP_TRANSFORM));
   CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(text, COMP_TRANSFORM);
   if (parentTrans->scale.x < 0)
     trans->scale.x = -1.0f;
   else
     trans->scale.x = 1.0f;
}


void comp_studentActorLogic(COMPONENT *self) {
  CDATA_STUDENTACTOR data = { 0 };
  data.outerState = OS_FADEIN;
  data.innerState = IS_ENTER;
  COMPONENT_INIT(self, COMP_STUDENTACTORLOGIC, data);
  self->events.logicUpdate = comp_studentActorLogic_logicUpdate;
  self->events.initialize = comp_studentActorLogic_initialize;
}

void comp_studentActorLogic_initialize(COMPONENT *self, void *event) {
  CDATA_STUDENTACTOR *data = (CDATA_STUDENTACTOR *)self->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);

  data->fadeIn = true;

}

void comp_studentActorLogic_updateState(COMPONENT *self) {
  CDATA_STUDENTACTOR *data = (CDATA_STUDENTACTOR *)self->data;
  switch (data->outerState) {

  // fading in
  case OS_FADEIN:
    data->stateTimer += (float)self->owner->space->game->systems.time.dt;
    {
    COMPONENT *multiSprite = (COMPONENT *)entity_getComponent(self->owner, COMP_MULTISPRITE);
    multiSprite_setAlpha(multiSprite, data->stateTimer / FADE_TIME);
    }
    if (data->stateTimer > FADE_TIME) {
      data->outerState = (STUDENT_STATE)randomIntRange(0, 1);
      data->innerState = IS_ENTER;
    } 
    break; // end fading in

  // if idling
  case OS_IDLE:
    switch (data->innerState) {

    // on enter
    case IS_ENTER:
      data->velocity = 0;
      data->stateTimer = 0;
      data->stateTime = (STUDENT_STATE)randomIntRange(10, 20) / 10.0f;
      data->innerState = IS_UPDATE;
      __studentActorLogic_setLegs(self, AF_IDLE);
      
      break;

    // on update
    case IS_UPDATE:
      data->stateTimer += (float)self->owner->space->game->systems.time.dt;
      if (data->stateTimer > data->stateTime)
        data->innerState = IS_EXIT;
      break;

    // on exit
    case IS_EXIT:
      //comp_studentActorLogic_createPopText(self, "hello moto");
      data->outerState = (STUDENT_STATE)randomIntRange(0, 1);
      data->innerState = IS_ENTER;
      break;

    } // end idling
    break;

  // if going left
  case OS_LEFT:
    switch (data->innerState) {

    // on enter
    case IS_ENTER:
      data->velocity = -0.5f;
      data->stateTimer = 0;
      data->stateTime = randomIntRange(5, 10) / 10.0f;
      comp_studentActorLogic_flipSprite(self);
      data->innerState = IS_UPDATE;
      __studentActorLogic_setLegs(self, AF_WALK1);
      break;

    // on update
    case IS_UPDATE:
      data->stateTimer += (float)self->owner->space->game->systems.time.dt;
      {
        CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
        trans->translation.x += data->velocity;

        // if hitting the walls
        if (trans->translation.x < data->origin - 40.0f + STUDENT_OFFSET - ROOM_X_OFFSET || trans->translation.x > data->origin + data->roomSize - 40.0f - STUDENT_OFFSET - ROOM_X_OFFSET) {
          data->velocity = -data->velocity;
          comp_studentActorLogic_flipSprite(self);
        }

        // if time is up
        if (data->stateTimer > data->stateTime)
          data->innerState = IS_EXIT;

      }
      break;

    case IS_EXIT:
      data->outerState = randomIntRange(1, 2);
      data->innerState = IS_ENTER;
      break;

    } 
    break; // end going left


  // if going right
  case OS_RIGHT:
    switch (data->innerState) {

    // on enter
    case IS_ENTER:
      data->velocity = 0.5f;
      data->stateTimer = 0;
      data->stateTime = data->roomSize / INDIVIDUAL_ROOM_SIZE * randomIntRange(5, 10) / 10.0f;
      comp_studentActorLogic_flipSprite(self);
      data->innerState = IS_UPDATE;
      __studentActorLogic_setLegs(self, AF_WALK1);
      break;

    // on update
    case IS_UPDATE:
      data->stateTimer += (float)self->owner->space->game->systems.time.dt;
      {
        CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
        trans->translation.x += data->velocity;

        // if hitting the walls
        if (trans->translation.x < data->origin - 40.0f + STUDENT_OFFSET - ROOM_X_OFFSET || trans->translation.x > data->origin + data->roomSize - 40.0f - STUDENT_OFFSET - ROOM_X_OFFSET) {
          data->velocity = -data->velocity;
          comp_studentActorLogic_flipSprite(self);
        }

        // if time is up
        if (data->stateTimer > data->stateTime)
          data->innerState = IS_EXIT;

      }
      break;

    case IS_EXIT:
      data->outerState = randomIntRange(0, 1);
      data->innerState = IS_ENTER;
      break;

    } 
    break; // end going right

  // walking to door
  case OS_WALKTODOOR:
    switch (data->innerState) {

    // on enter
    case IS_ENTER:
      {
        CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
        // set velocity based on position relative to door, and flip sprite
        data->velocity = trans->translation.x > data->origin ? -0.5f : 0.5f;
        comp_studentActorLogic_flipSprite(self);
        __studentActorLogic_setLegs(self, AF_WALK1);
        data->innerState = IS_UPDATE;
      }
      break; 

    // on update
    case IS_UPDATE:
      {
        CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
        trans->translation.x += data->velocity;

        // once i'm at the door, fadeout
        if (fabsf(trans->translation.x - data->origin) <= 0.5f) {
          data->outerState = OS_FADEOUT;
          data->innerState = IS_ENTER;
        }
      }
      break;

    }
    break; // end walking to door


  // fading out
  case OS_FADEOUT:
    switch (data->innerState) {

    // on enter
    case IS_ENTER:
      data->stateTimer = 0;
      data->innerState = IS_UPDATE;
      data->lifetime = 10000.0f;
      __studentActorLogic_setLegs(self, AF_IDLE);
      {
        CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
        mbox->active = false;
      }
      break;

    // on update
    case IS_UPDATE:
      {
        COMPONENT *multiSprite = (COMPONENT *)entity_getComponent(self->owner, COMP_MULTISPRITE);
        data->stateTimer += (float)self->owner->space->game->systems.time.dt;
        if (data->stateTimer > FADE_TIME)
          data->innerState = IS_EXIT;
        multiSprite_setAlpha(multiSprite, 1 - data->stateTimer / FADE_TIME);
      }
      break;

    // on exit
    case IS_EXIT:
      {
        ENTITY *manager = space_getEntity(self->owner->space, "studentManager");
        COMPONENT *managerLogic = entity_getComponent(manager, COMP_STUDENTMANAGERLOGIC);
        CDATA_STUDENTMANAGER *managerData = (CDATA_STUDENTMANAGER *)entity_getComponentData(manager, COMP_STUDENTMANAGERLOGIC);
      
        //when the student fades out, remove him from the drawnStudents list
        list_remove(managerData->drawnStudents, comp_studentManagerLogic_findStudent(managerLogic, (ENTITY *)self->owner, FT_ACTOR));
        --(managerData->displayCurrent);
        entity_destroy(self->owner);
      }
      break;

    } 
    break; // end fadeout

  } // end giant switch

}

void comp_studentActorLogic_createPopText(COMPONENT *self, char *text) {
  VEC3 position = { 0 };
  VEC4 color = { 0, 0, 0, 1.0f };
  ENTITY *popText = popText_create(self->owner->space, &position, "individualText", "fonts/gothic/12", text, &color, POPTYPE_STAY, 4.0f);
  entity_attach(popText, self->owner);
}

void __studentActorLogic_setLegs(COMPONENT *self, ANIMATION_FRAME frame) {
  CDATA_STUDENTACTOR *data = (CDATA_STUDENTACTOR *)self->data;
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(data->legsPointer, COMP_SPRITE);
  switch (frame) {
  case AF_IDLE:
    sprite->source = data->legs;
    data->currentFrame = 0;
    break;
  case AF_WALK1:
    sprite->source = data->walk1;
    data->currentFrame = 1;
    break;
  case AF_WALK2:
    sprite->source = data->walk2;
    data->currentFrame = 2;
    break;
  }
}