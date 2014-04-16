/******************************************************************************
Filename: pausescreenlogic.c

Project Name: Game School Simulator 2015

Author: Tai Der Hui

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/

#include "pausescreenlogic.h"
#include "custombutton.h"
#include "colors.h"
#include "generictext.h"
#include "mousebox.h"
#include "UI_button.h"
#include "UI_build.h"
#include "genericsprite.h"
#include "buttonfunctions.h"
#include "custombutton.h"
#include "custombuttonlogic.h"

void comp_pauseScreenLogic_frameUpdate(COMPONENT *self, void *event) {
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  CDATA_PAUSESCREEN *data = (CDATA_PAUSESCREEN *)self->data;

  if (!data->textCreated) {
    self->owner->space->game->systems.time.scale = 0;

    comp_pauseScreenLogic_makeMenu(self);
    data->textCreated = true;
  }
  
}

void comp_pauseScreenLogic(COMPONENT *self) {
  CDATA_PAUSESCREEN data = { GM_DEFAULT };
  COMPONENT_INIT(self, COMP_PAUSESCREENLOGIC, data);
  self->events.frameUpdate = comp_pauseScreenLogic_frameUpdate;
}

void comp_pauseScreenLogic_makeMenu(COMPONENT *self) {
  VEC3 pos = { 0, 0, 0 };
  SPACE *tutorial = self->owner->space;
  ENTITY *created;
  CDATA_UI_BUTTON *buttonData;
  CDATA_SPRITE *sprite;
  CDATA_PAUSESCREEN *data = (CDATA_PAUSESCREEN *)self->data;
  VEC4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
  CDATA_CUSTOMBUTTON *customButtonData;

  // create main sprite shadow
  vec3_set(&pos, 4, -4, 0);
  genericSprite_create(tutorial, &pos, "options", "ui/management_shadow");

  // create main sprite
  vec3_set(&pos, 0, 0, 0);
  genericSprite_create(tutorial, &pos, "options", "ui/options");

  // if tutorial is currently switched on
  if (self->owner->space->game->config.tutorial) {
    // create the true false button
    vec3_set(&pos, -25.0f, 27.0f, 0);
    created = createCustomButton(tutorial_onEntered, NULL, tutorial_onPressed, tutorial_onExit, NULL,
                            self->owner->space, &pos, "options",
                            1.0f, 1.0f,
                            true, "ui/check_checked", "ui/check_unchecked", NULL,
                            false, NULL, NULL, 
                            NULL, TEXTALIGN_CENTER, TEXTALIGN_CENTER);
    customButtonData = (CDATA_CUSTOMBUTTON *)entity_getComponentData(created, COMP_CUSTOMBUTTONLOGIC);
    customButtonData->frameUpdate = true;
  }

  // if tutorial isn't currently switched on
  else {
    CDATA_CUSTOMBUTTON *data;
    CDATA_SPRITE *spriteData;
    // create the true false button
    vec3_set(&pos, -25.0f, 27.0f, 0);
    created = createCustomButton(tutorial_onEntered, NULL, tutorial_onPressed, tutorial_onExit, NULL,
                            self->owner->space, &pos, "options",
                            1.0f, 1.0f,
                            true, "ui/check_checked", "ui/check_unchecked", NULL,
                            false, NULL, NULL, 
                            NULL, TEXTALIGN_CENTER, TEXTALIGN_CENTER);
    data = (CDATA_CUSTOMBUTTON *)entity_getComponentData(created, COMP_CUSTOMBUTTONLOGIC);
    data->sprite.altSprite = true;
    spriteData = (CDATA_SPRITE *)entity_getComponentData(created, COMP_SPRITE);
    spriteData->source = data->sprite.altSource;
    customButtonData = (CDATA_CUSTOMBUTTON *)entity_getComponentData(created, COMP_CUSTOMBUTTONLOGIC);
    customButtonData->frameUpdate = true;
  }

  // create the true false button
  // if currently full screen
  if (self->owner->space->game->config.screen.full) {
    vec3_set(&pos, -25.0f, -33.0f, 0);
    created = createCustomButton(fullScreen_onEntered, NULL, fullScreen_onPressed, fullScreen_onExit, NULL,
                            self->owner->space, &pos, "options",
                            1.0f, 1.0f,
                            true, "ui/check_checked", "ui/check_unchecked", NULL,
                            false, NULL, NULL, 
                            NULL, TEXTALIGN_CENTER, TEXTALIGN_CENTER);
    customButtonData = (CDATA_CUSTOMBUTTON *)entity_getComponentData(created, COMP_CUSTOMBUTTONLOGIC);
    customButtonData->frameUpdate = true;
  }

  // if currently not full screen
  else {
    CDATA_CUSTOMBUTTON *data;
    CDATA_SPRITE *spriteData; 
    vec3_set(&pos, -25.0f, -33.0f, 0);
    created = createCustomButton(fullScreen_onEntered, NULL, fullScreen_onPressed, fullScreen_onExit, NULL,
                            self->owner->space, &pos, "options",
                            1.0f, 1.0f,
                            true, "ui/check_checked", "ui/check_unchecked", NULL,
                            false, NULL, NULL, 
                            NULL, TEXTALIGN_CENTER, TEXTALIGN_CENTER);
    data = (CDATA_CUSTOMBUTTON *)entity_getComponentData(created, COMP_CUSTOMBUTTONLOGIC);
    data->sprite.altSprite = true;
    spriteData = (CDATA_SPRITE *)entity_getComponentData(created, COMP_SPRITE);
    spriteData->source = data->sprite.altSource;
    customButtonData = (CDATA_CUSTOMBUTTON *)entity_getComponentData(created, COMP_CUSTOMBUTTONLOGIC);
    customButtonData->frameUpdate = true;
  }

  if (!space_getEntity(self->owner->space, "menuScreen")) {
    // create main menu button
    vec3_set(&pos, 15, 71, 0);
    created = space_addEntityAtPosition(tutorial, arch_uibuild, "options", &pos);
    buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(created, COMP_UI_BUTTON);
    buttonData->type = BUTTON_MAIN_MENU;
    sprite = (CDATA_SPRITE *)entity_getComponentData(created, COMP_SPRITE);
    sprite->source = "ui/button_mainmenu";
  }

  // master text
  vec3_set(&pos, 121, 16, 0);
  sprintf(data->masterBuffer, "%d%%", (int)(self->owner->space->game->systems.sound.volume.master * 100));
  data->masterText = genericText_create(self->owner->space, &pos, "options", "fonts/gothic/12", data->masterBuffer, &color, TEXTALIGN_MIDDLE, TEXTALIGN_CENTER);

  // master vol up
  vec3_set(&pos, 148, 16, 0);
  created = space_addEntityAtPosition(tutorial, arch_uibuild, "options", &pos);
  buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(created, COMP_UI_BUTTON);
  buttonData->type = BUTTON_MASTER_VOL_UP;
  sprite = (CDATA_SPRITE *)entity_getComponentData(created, COMP_SPRITE);
  sprite->source = "ui/button_plus";

  // master vol down
  vec3_set(&pos, 94, 16, 0);
  created = space_addEntityAtPosition(tutorial, arch_uibuild, "options", &pos);
  buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(created, COMP_UI_BUTTON);
  buttonData->type = BUTTON_MASTER_VOL_DOWN;
  sprite = (CDATA_SPRITE *)entity_getComponentData(created, COMP_SPRITE);
  sprite->source = "ui/button_minus";

  // sound text
  vec3_set(&pos, 121, -6, 0);
  sprintf(data->soundBuffer, "%d%%", (int)(self->owner->space->game->systems.sound.volume.sound * 100));
  data->soundText = genericText_create(self->owner->space, &pos, "options", "fonts/gothic/12", data->soundBuffer, &color, TEXTALIGN_MIDDLE, TEXTALIGN_CENTER);

  // sound vol up
  vec3_set(&pos, 148, -6, 0);
  created = space_addEntityAtPosition(tutorial, arch_uibuild, "options", &pos);
  buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(created, COMP_UI_BUTTON);
  buttonData->type = BUTTON_SOUND_VOL_UP;
  sprite = (CDATA_SPRITE *)entity_getComponentData(created, COMP_SPRITE);
  sprite->source = "ui/button_plus";

  // sound vol down
  vec3_set(&pos, 94, -6, 0);
  created = space_addEntityAtPosition(tutorial, arch_uibuild, "options", &pos);
  buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(created, COMP_UI_BUTTON);
  buttonData->type = BUTTON_SOUND_VOL_DOWN;
  sprite = (CDATA_SPRITE *)entity_getComponentData(created, COMP_SPRITE);
  sprite->source = "ui/button_minus";

  // music text
  vec3_set(&pos, 121, -30, 0);
  sprintf(data->musicBuffer, "%d%%", (int)(self->owner->space->game->systems.sound.volume.music * 100));
  data->musicText = genericText_create(self->owner->space, &pos, "options", "fonts/gothic/12", data->musicBuffer, &color, TEXTALIGN_MIDDLE, TEXTALIGN_CENTER);

  // music vol up
  vec3_set(&pos, 148, -30, 0);
  created = space_addEntityAtPosition(tutorial, arch_uibuild, "options", &pos);
  buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(created, COMP_UI_BUTTON);
  buttonData->type = BUTTON_MUSIC_VOL_UP;
  sprite = (CDATA_SPRITE *)entity_getComponentData(created, COMP_SPRITE);
  sprite->source = "ui/button_plus";

  // music vol down
  vec3_set(&pos, 94, -30, 0);
  created = space_addEntityAtPosition(tutorial, arch_uibuild, "options", &pos);
  buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(created, COMP_UI_BUTTON);
  buttonData->type = BUTTON_MUSIC_VOL_DOWN;
  sprite = (CDATA_SPRITE *)entity_getComponentData(created, COMP_SPRITE);
  sprite->source = "ui/button_minus";


  // ambient text
  vec3_set(&pos, 121, -50, 0);
  sprintf(data->ambientBuffer, "%d%%", (int)(self->owner->space->game->systems.sound.volume.ambient * 100));
  data->ambientText = genericText_create(self->owner->space, &pos, "options", "fonts/gothic/12", data->ambientBuffer, &color, TEXTALIGN_MIDDLE, TEXTALIGN_CENTER);

  // ambient vol up
  vec3_set(&pos, 148, -50, 0);
  created = space_addEntityAtPosition(tutorial, arch_uibuild, "options", &pos);
  buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(created, COMP_UI_BUTTON);
  buttonData->type = BUTTON_AMBIENT_VOL_UP;
  sprite = (CDATA_SPRITE *)entity_getComponentData(created, COMP_SPRITE);
  sprite->source = "ui/button_plus";

  // ambient vol down
  vec3_set(&pos, 94, -50, 0);
  created = space_addEntityAtPosition(tutorial, arch_uibuild, "options", &pos);
  buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(created, COMP_UI_BUTTON);
  buttonData->type = BUTTON_AMBIENT_VOL_DOWN;
  sprite = (CDATA_SPRITE *)entity_getComponentData(created, COMP_SPRITE);
  sprite->source = "ui/button_minus";

  // close button
  vec3_set(&pos, 125, 70, 0);
  created = space_addEntityAtPosition(tutorial, arch_uibuild, "options", &pos);
  buttonData = (CDATA_UI_BUTTON *)entity_getComponentData(created, COMP_UI_BUTTON);
  buttonData->type = BUTTON_CLOSE_OPTIONS;
  sprite = (CDATA_SPRITE *)entity_getComponentData(created, COMP_SPRITE);
  sprite->source = "ui/close";
}
