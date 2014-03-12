/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "custombutton.h"
#include "custombuttonlogic.h"
#include "transform.h"
#include "mousebox.h"

void arch_customButton(ENTITY *entity) {
  entity->id = ARCH_CUSTOMBUTTON;
  entity_connect(entity, comp_transform);
  entity_connect(entity, comp_customButtonLogic);
  entity_connect(entity, comp_sprite);
  entity_connect(entity, comp_mouseBox);
}

ENTITY *createCustomButton(void (*onEntered)(COMPONENT *), 
                           void (*onOver)(COMPONENT *), 
                           void (*onPressed)(COMPONENT *),
                           void (*onExit)(COMPONENT *), 
                           void (*destroy)(COMPONENT *),
                           SPACE *space, VEC3 *position, char *name,
                           float sizeX, float sizeY,
                           bool customSprite, char *spriteSource, 
                           char *altSource, VEC4 *color,
                           bool hasText, char *text, char *font, 
                           VEC4 *textColor, TEXTALIGN xAlign, TEXTALIGN yAlign)
{
  ENTITY *created = space_addEntityAtPosition(space, arch_customButton, name, position);
  CDATA_CUSTOMBUTTON *buttonData = (CDATA_CUSTOMBUTTON *)entity_getComponentData(created, COMP_CUSTOMBUTTONLOGIC);
  CDATA_SPRITE *buttonSprite = (CDATA_SPRITE *)entity_getComponentData(created, COMP_SPRITE);

  // set the function pointers
  buttonData->onOver = onOver;
  buttonData->onExit = onExit;
  buttonData->onEntered = onEntered;
  buttonData->onPressed = onPressed;
  buttonData->destroy = destroy;

  // set the sprite
  if (customSprite) {
    strcpy(buttonData->sprite.source, spriteSource);
    if (altSource)
      strcpy(buttonData->sprite.altSource, altSource);
  }
  else
    strcpy(buttonData->sprite.source, "blank");
  buttonSprite->source = buttonData->sprite.source;
  if (color)
    buttonSprite->color = *color;
  else
    vec4_set(&buttonSprite->color, 1.0f, 1.0f, 1.0f, 1.0f);
  buttonSprite->size.x = sizeX;
  buttonSprite->size.y = sizeY;

  // set the spritetext
  if (hasText) {
    VEC3 pos = { 0 };
    ENTITY *createdText = genericText_create(space, &pos, "customButtonText", font, text, textColor, xAlign, yAlign); 
    entity_attach(createdText, created); 
    buttonData->text = createdText;
  }

  return created;
}
