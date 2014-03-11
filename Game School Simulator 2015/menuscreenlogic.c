/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "menuscreenlogic.h"
#include "genericsprite.h"
#include "generictext.h"
#include "UI_button.h"
#include "UI_build.h"
#include "buttonfunctions.h"
#include "custombutton.h"

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

void comp_menuScreenLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_MENUSCREENLOGIC *data = (CDATA_MENUSCREENLOGIC *)self->data;
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  if ((input->mouse.left || input->keyboard.anyKey) && !data->pressedStart) {
    VEC3 position = { 0 };
    VEC4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
    ENTITY *titleContainer = genericSprite_create(self->owner->space, &position, "titleContainer", "titlescreen/title");
    ENTITY *title;
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

    /*ENTITY *created = genericSprite_create(self->owner->space, &position, "menubox", "blank");
    CDATA_SPRITE *spriteData = (CDATA_SPRITE *)entity_getComponentData(created, COMP_SPRITE);
    input->mouse.handled[MBUTTON_LEFT] = true;
    spriteData->size.x = 500.0f;
    spriteData->size.y = 500.0f;*/

    // create the new game button
    /*position.y = 80.0f;
    createCustomButton(newGame_onEntered, NULL, newGame_onPressed, newGame_onExit, NULL,
                             self->owner->space, &position, "newGameButton",
                             1.0f, 1.0f,
                             true, "newgame", NULL, NULL,
                             false, NULL, NULL, 
                             NULL, TEXTALIGN_CENTER, TEXTALIGN_CENTER);*/

    // create the options button
    /*position.y = -80.0f;
    position.x = -125.0f;
    createCustomButton(options_onEntered, NULL, options_onPressed, options_onExit, NULL,
                             self->owner->space, &position, "optionsButton",
                             1.0f, 1.0f,
                             true, "options", NULL, NULL,
                             false, NULL, NULL, 
                             NULL, TEXTALIGN_CENTER, TEXTALIGN_CENTER);*/

    // create the exit button
    /*position.x = 125.0f;
    createCustomButton(exit_onEntered, NULL, exit_onPressed, exit_onExit, NULL,
                             self->owner->space, &position, "exitButton",
                             1.0f, 1.0f,
                             true, "exit", NULL, NULL,
                             false, NULL, NULL, 
                             NULL, TEXTALIGN_CENTER, TEXTALIGN_CENTER);*/
    position.x = -76.0f;
    position.y = -64.0f;
    createCustomButton(newGame_onEntered, NULL, newGame_onPressed, newGame_onExit, NULL,
                       self->owner->space, &position, "newGameButton", 1.0f, 1.0f, true, "titlescreen/newgame",
                       NULL, &color, false, NULL, NULL, NULL, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
    position.x = 212.0f;
    position.y = 42.0f;
    createCustomButton(options_onEntered, NULL, options_onPressed, options_onExit, NULL,
                       self->owner->space, &position, "optionsButton", 1.0f, 1.0f, true, "titlescreen/options",
                       NULL, &color, false, NULL, NULL, NULL, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
    position.x = 212.0f;
    position.y = -118.0f;
    createCustomButton(exit_onEntered, NULL, exit_onPressed, exit_onExit, NULL,
                       self->owner->space, &position, "quitButton", 1.0f, 1.0f, true, "titlescreen/quit",
                       NULL, &color, false, NULL, NULL, NULL, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
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
