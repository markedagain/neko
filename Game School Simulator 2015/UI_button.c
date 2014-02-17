#include "UI_button.h"
#include "mousebox.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/generictext.h"
#include "../Nekoengine/spritetext.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/entity.h"
#include "../NekoEngine/sprite.h"
#include <math.h>
#include <stdio.h>
#include "ghostroom.h"
#include "playerlogic.h"
#include "roomlogic.h"
#include "UI_build.h"
#include "schoollogic.h"

// code is breaking and eduardo is screaming
void comp_UI_buttonUpdate(COMPONENT *self, void *event) {
  CDATA_UI_BUTTON *data = (CDATA_UI_BUTTON *)self->data;
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  VEC2 dimensions = { 40.0f, 20.0f };
  VEC3 position = { 10, 10, 0 };
  VEC4 color = { 0, 0, 1, 1 };
  SPACE *ui = game_getSpace(self->owner->space->game, "ui");
  ENTITY *player = space_getEntity(ui, "player");
  ENTITY *camera = 0;
  CDATA_PLAYERLOGIC *playerData = (CDATA_PLAYERLOGIC *)entity_getComponentData(player, COMP_PLAYERLOGIC);
  CDATA_UI_BUTTON *comData = (CDATA_UI_BUTTON *)self->data;

  if (mbox->over) {
    sprite->color.r = min(sprite->color.r + 0.05f, 1);
    sprite->color.b = max(sprite->color.b - 0.05f, 1);
    sprite->color.g = max(sprite->color.g - 0.05f, 0);
  }
  else {
    sprite->color.r = max(sprite->color.r - 0.05f, 0);
    sprite->color.b = min(sprite->color.b + 0.05f, 1);
    sprite->color.g = min(sprite->color.g + 0.05f, 1);
  }

  if (mbox->left.pressed) {
    VEC3 position;
    ENTITY *newButton;
    CDATA_UI_BUTTON *buttonData;
    ENTITY *text;
    VEC4 color;

    switch (comData->type) {
    case BUTTON_DEFAULT:
      if(comData->showing == FALSE) {
        // LOBBY BUTTON
        //vec3_set(&position, -250, -60, 0);
        vec3_set(&position, -250, 160, 0);
        newButton = space_addEntityAtPosition(self->owner->space, arch_uibuild, "buildButton", &position);
        buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(newButton, COMP_UI_BUTTON);
        //vec3_set(&position, -250, -50, 0);
        vec3_set(&position, 0.0f, 0.0f, 0.0f);
        text = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", "Lobby", &color,TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
        entity_attach(text, newButton);
        buttonData->type = BUTTON_BUILDLOBBY;

        // CLASS BUTTON
        //vec3_set(&position, -190, -60, 0);
        vec3_set(&position, -190, 160, 0);
        newButton = space_addEntityAtPosition(self->owner->space, arch_uibuild, "buildButton", &position);
        buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(newButton, COMP_UI_BUTTON);
        //vec3_set(&position, -190, -50, 0);
        vec3_set(&position, 0.0f, 0.0f, 0.0f);
        text = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", "Class", &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
        entity_attach(text, newButton);
        buttonData->type = BUTTON_BUILDCLASS;

        // LIBRARY BUTTON
        //vec3_set(&position, -130, -60, 0);
        vec3_set(&position, -130, 160, 0);
        newButton = space_addEntityAtPosition(self->owner->space, arch_uibuild, "buildButton", &position);
        buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(newButton, COMP_UI_BUTTON);
        //vec3_set(&position, -130, -50, 0);
        vec3_set(&position, 0.0f, 0.0f, 0.0f);
        text = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", "Library", &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
        entity_attach(text, newButton);
        buttonData->type = BUTTON_BUILDLIBRARY;
  
        // TEAMSPACE BUTTON
        //vec3_set(&position, -70, -60, 0);
        vec3_set(&position, -70, 160, 0);
        newButton = space_addEntityAtPosition(self->owner->space, arch_uibuild, "buildButton", &position);
        buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(newButton, COMP_UI_BUTTON);
        //vec3_set(&position, -70, -50, 0);
        vec3_set(&position, 0.0f, 0.0f, 0.0f);
        text = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", "Team", &color, TEXTALIGN_CENTER, TEXTALIGN_MIDDLE);
        entity_attach(text, newButton);
        buttonData->type = BUTTON_BUILDTEAMSPACE;

        //pan(self, 0.0f, -40.0f, NULL);

        comData->showing = TRUE;
      }
      else {
        LIST_NODE *node;
        LIST *buttons = list_create();
        space_getAllEntities(self->owner->space, "buildButton", buttons);
        node = buttons->first;
        while (node) {
          entity_destroy((ENTITY *)node->data);
          node = node->next;
        }
        //pan(self, 0.0f, 40.0f, NULL);

        list_destroy(buttons);
        comData->showing = FALSE;
      }
      break;

    case BUTTON_BUILDLOBBY:
      playerData->roomType = ROOMTYPE_LOBBY;
      playerData->gameMode = BUILD;
      break;

    case BUTTON_BUILDCLASS:
      playerData->roomType = ROOMTYPE_CLASS;
      playerData->gameMode = BUILD;
      break;

    case BUTTON_BUILDLIBRARY:
      playerData->roomType = ROOMTYPE_LIBRARY;
      playerData->gameMode = BUILD;
      break;

    case BUTTON_BUILDTEAMSPACE:
      playerData->roomType = ROOMTYPE_TEAMSPACE;
      playerData->gameMode = BUILD;
      break;

    default:
      break;
    }
  }
 /*
  if (mbox->entered && data->ent3 == NULL) {
    vec3_set(&position, 0, -50, 0);
    data->ent3 = genericSprite_create(ui, &position, NULL, "cursor/build");
  }

  else if (mbox->exited && data->ent3) {
    entity_destroy(data->ent3);
    data->ent3 = NULL;
  }
  */
  /*
  if(mbox->left.pressed && data->ent2 == NULL) {
    vec3_set(&position, 100, 100, 0);
    data->ent2 = genericSprite_create(ui, &position, NULL, "backgrounds/i_love_you");
  }
  else if(mbox->left.pressed && data->ent2) {
    entity_destroy(data->ent2);
    data->ent2 = NULL;
  }
  */
}

void comp_UI_button(COMPONENT *self) {
  CDATA_UI_BUTTON data = { 0 };
  data.type = BUTTON_DEFAULT;
  COMPONENT_INIT(self, COMP_UI_BUTTON, data);
  component_depend(self, COMP_MOUSEBOX);
  self->events.logicUpdate = comp_UI_buttonUpdate;
}