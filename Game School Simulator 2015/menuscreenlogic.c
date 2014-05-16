/******************************************************************************
Filename: menuscreenlogic.c

Project Name: Game School Simulator 2015

Author: Adam Rezich

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "menuscreenlogic.h"
#include "genericsprite.h"
#include "generictext.h"
#include "UI_button.h"
#include "UI_build.h"
#include "buttonfunctions.h"
#include "custombutton.h"
#include "mousebox.h"
#include "creditsscreen.h"

static void fadeCopyrightIn_update(ACTION *action, double dt) {
  ENTITY *self = (ENTITY *)action->data;
  ENTITY *copyright = space_getEntity(self->space, "copyright");
  float alpha = multiSprite_getAlpha(entity_getComponent(copyright, COMP_MULTISPRITE));
  alpha = action_ease(action, EASING_QUAD_IN, 0.0f, 1.0f);
  multiSprite_setAlpha(entity_getComponent(copyright, COMP_MULTISPRITE), alpha);
}

static void scaleTitle_update(ACTION *action, double dt) {
  ENTITY *self = (ENTITY *)action->data;
  ENTITY *logo = space_getEntity(self->space, "logo");
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(logo, COMP_TRANSFORM);
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(logo, COMP_SPRITE);
  trans->scale.x = action_ease(action, EASING_QUAD_IN, 2.0f, -1.0f);
  trans->scale.y = action_ease(action, EASING_QUAD_IN, 2.0f, -1.0f);
  sprite->color.a = action_ease(action, EASING_QUAD_IN, 0.0f, 1.0f); 
}


static void fadeIn_update(ACTION *action, double dt) {
  ENTITY *self = (ENTITY *)action->data;
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self, COMP_SPRITE);
  sprite->color.a = 1.0f - action_getEase(action, EASING_QUAD_IN);
}
static void fadeIn_onEnd(ACTION *action) {
  ENTITY *self = (ENTITY *)action->data;
  entity_destroy(self);
}

static void moveTitle_update(ACTION *action, double dt) {
  ENTITY *self = (ENTITY *)action->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self, COMP_TRANSFORM);
  trans->translation.x = action_ease(action, EASING_QUAD_OUT, 0.0f, -76.0f);
  trans->translation.y = action_ease(action, EASING_QUAD_OUT, 0.0f, 96.0f);
}

static void moveTitleContainer_update(ACTION *action, double dt) {
  ENTITY *self = (ENTITY *)action->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self, COMP_TRANSFORM);
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self, COMP_SPRITE);
  trans->translation.x = action_ease(action, EASING_QUAD_OUT, 0.0f, -76.0f);
  trans->translation.y = action_ease(action, EASING_QUAD_OUT, 0.0f, 96.0f);
  trans->scale.x = action_ease(action, EASING_QUAD_OUT, 0.0f, 1.0f);
  trans->scale.y = action_ease(action, EASING_QUAD_OUT, 0.0f, 1.0f);
  sprite->color.a = action_ease(action, EASING_QUAD_OUT, 0.0f, 1.0f);
}

static void moveNewGameButton_start(ACTION *action) {
  ENTITY *self = (ENTITY *)action->data;
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self, COMP_MOUSEBOX);

  mbox->active = false;
}


static void moveNewGameButton_exit(ACTION *action) {
  ENTITY *self = (ENTITY *)action->data;
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self, COMP_MOUSEBOX);

  mbox->active = true;
}

static void moveNewGameButton_update(ACTION *action, double dt) {
  ENTITY *self = (ENTITY *)action->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self, COMP_TRANSFORM);
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self, COMP_SPRITE);
  trans->translation.x = action_ease(action, EASING_QUAD_OUT, 0.0f, -76.0f);
  trans->translation.y = action_ease(action, EASING_QUAD_OUT, 0.0f, -63.0f);
  trans->scale.x = action_ease(action, EASING_QUAD_OUT, 0.0f, 1.0f);
  trans->scale.y = action_ease(action, EASING_QUAD_OUT, 0.0f, 1.0f);
  sprite->color.a = action_ease(action, EASING_QUAD_OUT, 0.0f, 1.0f);
}

static void moveOptionsButton_start(ACTION *action) {
  ENTITY *self = (ENTITY *)action->data;
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self, COMP_MOUSEBOX);

  mbox->active = false;
}


static void moveOptionsButton_exit(ACTION *action) {
  ENTITY *self = (ENTITY *)action->data;
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self, COMP_MOUSEBOX);

  mbox->active = true;
}

static void moveOptionsButton_update(ACTION *action, double dt) {
  ENTITY *self = (ENTITY *)action->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self, COMP_TRANSFORM);
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self, COMP_SPRITE);
  trans->translation.x = action_ease(action, EASING_QUAD_OUT, 0.0f, 212.0f);
  trans->translation.y = action_ease(action, EASING_QUAD_OUT, 0.0f, 96.0f);
  trans->scale.x = action_ease(action, EASING_QUAD_OUT, 0.0f, 1.0f);
  trans->scale.y = action_ease(action, EASING_QUAD_OUT, 0.0f, 1.0f);
  sprite->color.a = action_ease(action, EASING_QUAD_OUT, 0.0f, 1.0f);
}

static void moveCreditsButton_start(ACTION *action) {
  ENTITY *self = (ENTITY *)action->data;
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self, COMP_MOUSEBOX);

  mbox->active = false;
}


static void moveCreditsButton_exit(ACTION *action) {
  ENTITY *self = (ENTITY *)action->data;
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self, COMP_MOUSEBOX);

  mbox->active = true;
}

static void moveCreditsButton_update(ACTION *action, double dt) {
  ENTITY *self = (ENTITY *)action->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self, COMP_TRANSFORM);
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self, COMP_SPRITE);
  trans->translation.x = action_ease(action, EASING_QUAD_OUT, 0.0f, 212.0f);
  trans->translation.y = action_ease(action, EASING_QUAD_OUT, 0.0f, -26.0f);
  trans->scale.x = action_ease(action, EASING_QUAD_OUT, 0.0f, 1.0f);
  trans->scale.y = action_ease(action, EASING_QUAD_OUT, 0.0f, 1.0f);
  sprite->color.a = action_ease(action, EASING_QUAD_OUT, 0.0f, 1.0f);
}

static void moveQuitButton_start(ACTION *action) {
  ENTITY *self = (ENTITY *)action->data;
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self, COMP_MOUSEBOX);

  mbox->active = false;
}


static void moveQuitButton_exit(ACTION *action) {
  ENTITY *self = (ENTITY *)action->data;
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self, COMP_MOUSEBOX);

  mbox->active = true;
}

static void moveQuitButton_update(ACTION *action, double dt) {
  ENTITY *self = (ENTITY *)action->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self, COMP_TRANSFORM);
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self, COMP_SPRITE);
  trans->translation.x = action_ease(action, EASING_QUAD_OUT, 0.0f, 212.0f);
  trans->translation.y = action_ease(action, EASING_QUAD_OUT, 0.0f, -121.0f);
  trans->scale.x = action_ease(action, EASING_QUAD_OUT, 0.0f, 1.0f);
  trans->scale.y = action_ease(action, EASING_QUAD_OUT, 0.0f, 1.0f);
  sprite->color.a = action_ease(action, EASING_QUAD_OUT, 0.0f, 1.0f);
}

void comp_menuScreenLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_MENUSCREENLOGIC *data = (CDATA_MENUSCREENLOGIC *)self->data;
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  ENTITY *pressStart;
  if (!data->beganFading) {
    data->beganFading = true;
    al_pushBack(&data->actions, action_create(space_getEntity(self->owner->space, "fader"), fadeIn_update, NULL, fadeIn_onEnd, false, 0.75f));
  }
  if ((input->mouse.left || input->keyboard.anyKey) && !data->pressedStart) {
    VEC3 position = { 0 };
    VEC4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
    ENTITY *titleContainer = genericSprite_create(self->owner->space, &position, "titleContainer", "titlescreen/title");
    ENTITY *title, *credits, *newGameButton, *optionsButton, *quitButton, *creditsButton;
    CDATA_SPRITE *titleContainerSprite = (CDATA_SPRITE *)entity_getComponentData(titleContainer, COMP_SPRITE);
    CDATA_TRANSFORM *titleContainerTransform = (CDATA_TRANSFORM *)entity_getComponentData(titleContainer, COMP_TRANSFORM);
    CDATA_MOUSEBOX *mbox;
    
    titleContainerSprite->color.a = 0.0f;
    titleContainerTransform->scale.x = 0.0f;
    titleContainerTransform->scale.y = 0.0f;

    entity_destroy(space_getEntity(self->owner->space, "pressStart"));
    entity_destroy(space_getEntity(self->owner->space, "logo"));
    title = genericSprite_create(self->owner->space, &position, "logo", "logo");
    al_pushBack(&data->actions, action_create(title, moveTitle_update, NULL, NULL, false, 0.5f));
    al_pushBack(&data->actions, action_create(titleContainer, moveTitleContainer_update, NULL, NULL, false, 0.5f));

    input->mouse.handled[MBUTTON_LEFT] = true;
    newGameButton = createCustomButton(newGame_onEntered, NULL, newGame_onPressed, newGame_onExit, NULL,
                       self->owner->space, &position, "newGameButton", 1.0f, 1.0f, true, "titlescreen/newgame",
                       NULL, &color, false, NULL, NULL, NULL, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
    al_pushBack(&data->actions, action_create(newGameButton, moveNewGameButton_update, moveNewGameButton_start, moveNewGameButton_exit, false, 0.5f));

    optionsButton = createCustomButton(options_onEntered, NULL, options_onPressed, options_onExit, NULL,
                       self->owner->space, &position, "optionsButton", 1.0f, 1.0f, true, "titlescreen/options",
                       NULL, &color, false, NULL, NULL, NULL, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
    al_pushBack(&data->actions, action_create(optionsButton, moveOptionsButton_update, moveOptionsButton_start, moveOptionsButton_exit, false, 0.5f));

    quitButton = createCustomButton(exit_onEntered, NULL, exit_onPressed, exit_onExit, NULL,
                       self->owner->space, &position, "quitButton", 1.0f, 1.0f, true, "titlescreen/quit",
                       NULL, &color, false, NULL, NULL, NULL, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
    al_pushBack(&data->actions, action_create(quitButton, moveQuitButton_update, moveQuitButton_start, moveQuitButton_exit, false, 0.5f));
    creditsButton = createCustomButton(credits_onEntered, NULL, credits_onPressed, credits_onExit, NULL,
                       self->owner->space, &position, "creditsButton", 1.0f, 1.0f, true, "titlescreen/credits",
                       NULL, &color, false, NULL, NULL, NULL, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
    al_pushBack(&data->actions, action_create(creditsButton, moveCreditsButton_update, moveCreditsButton_start, moveCreditsButton_exit, false, 0.5f));
    
    
    credits = space_addEntityAtPosition(self->owner->space, arch_creditsScreen, "credits", &position);
    mbox = (CDATA_MOUSEBOX *)entity_getComponentData(credits, COMP_MOUSEBOX);
    mbox->active = false;
    data->pressedStart = true;
  }
  pressStart = space_getEntity(self->owner->space, "pressStart");
  if (pressStart) {
    multiSprite_setAlpha(entity_getComponent(pressStart, COMP_MULTISPRITE), sinf(self->owner->space->game->systems.time.elapsed * 2.0f));
  }
  al_update(&data->actions, self->owner->space->game->systems.time.dt);
}

void comp_menuScreenLogic(COMPONENT *self) {
  CDATA_MENUSCREENLOGIC data = { 0 };
  data.pressedStart = false;
  data.beganFading = false;
  al_init(&data.actions);
  COMPONENT_INIT(self, COMP_MENUSCREENLOGIC, data);
  self->events.logicUpdate = comp_menuScreenLogic_logicUpdate;
  self->events.initialize = comp_menuScreenLogic_initialize;
  self->events.destroy = comp_menuScreenLogic_destroy;
}

void comp_menuScreenLogic_initialize(COMPONENT *self, void *event) {
  CDATA_MENUSCREENLOGIC *data = (CDATA_MENUSCREENLOGIC *)self->data;
  al_pushBack(&data->actions, action_create(self->owner, fadeCopyrightIn_update, NULL, NULL, false, 0.75f));
  al_pushBack(&data->actions, action_create(self->owner, scaleTitle_update, NULL, NULL, false, 1.25f));
}

void comp_menuScreenLogic_destroy(COMPONENT *self, void *event) {
  CDATA_MENUSCREENLOGIC *data = (CDATA_MENUSCREENLOGIC *)self->data;
  al_destroy(&data->actions);
}
