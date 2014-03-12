/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "menuscreenlogic.h"
#include "genericsprite.h"
#include "generictext.h"
#include "UI_button.h"
#include "UI_build.h"
#include "buttonfunctions.h"
#include "custombutton.h"
#include "mousebox.h"

static void moveTitle_update(ACTION *action, double dt) {
  ENTITY *self = (ENTITY *)action->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self, COMP_TRANSFORM);
  trans->translation.x = action_ease(action, EASING_QUAD_OUT, 0.0f, -76.0f);
  trans->translation.y = action_ease(action, EASING_QUAD_OUT, 0.0f, 93.5f);
}

static void moveTitleContainer_update(ACTION *action, double dt) {
  ENTITY *self = (ENTITY *)action->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self, COMP_TRANSFORM);
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self, COMP_SPRITE);
  trans->translation.x = action_ease(action, EASING_QUAD_OUT, 0.0f, -76.0f);
  trans->translation.y = action_ease(action, EASING_QUAD_OUT, 0.0f, 93.0f);
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
  trans->translation.y = action_ease(action, EASING_QUAD_OUT, 0.0f, -64.0f);
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
  trans->translation.y = action_ease(action, EASING_QUAD_OUT, 0.0f, 42.0f);
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
  trans->translation.y = action_ease(action, EASING_QUAD_OUT, 0.0f, -118.0f);
  trans->scale.x = action_ease(action, EASING_QUAD_OUT, 0.0f, 1.0f);
  trans->scale.y = action_ease(action, EASING_QUAD_OUT, 0.0f, 1.0f);
  sprite->color.a = action_ease(action, EASING_QUAD_OUT, 0.0f, 1.0f);
}

void comp_menuScreenLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_MENUSCREENLOGIC *data = (CDATA_MENUSCREENLOGIC *)self->data;
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  if ((input->mouse.left || input->keyboard.anyKey) && !data->pressedStart) {
    VEC3 position = { 0 };
    VEC4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
    ENTITY *titleContainer = genericSprite_create(self->owner->space, &position, "titleContainer", "titlescreen/title");
    ENTITY *title, *newGameButton, *optionsButton, *quitButton;
    CDATA_SPRITE *titleContainerSprite = (CDATA_SPRITE *)entity_getComponentData(titleContainer, COMP_SPRITE);
    CDATA_TRANSFORM *titleContainerTransform = (CDATA_TRANSFORM *)entity_getComponentData(titleContainer, COMP_TRANSFORM);
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
    data->pressedStart = true;
  }
  al_update(&data->actions, updateEvent->dt);
}

void comp_menuScreenLogic(COMPONENT *self) {
  CDATA_MENUSCREENLOGIC data = { 0 };
  data.pressedStart = false;
  al_init(&data.actions);
  COMPONENT_INIT(self, COMP_MENUSCREENLOGIC, data);
  self->events.logicUpdate = comp_menuScreenLogic_logicUpdate;
  self->events.initialize = comp_menuScreenLogic_initialize;
}

void comp_menuScreenLogic_initialize(COMPONENT *self, void *event) {
  
}
