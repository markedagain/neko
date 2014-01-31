/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "neko.h"
#include "dictionary.h"
#include "../fmod/fmod.h"
#include "../fmod/fmod_errors.h"
#include "data.h"

#define SOUND_CHANNELS 8

typedef struct {
  FMOD_SYSTEM *system;
  FMOD_SPEAKERMODE speakerMode;
  DICT *sounds;
} SOUND_SYSTEM;

NEKO_API void sound_initialize(SOUND_SYSTEM *system, DICT *sounds);

NEKO_API void sound_playSound(SOUND_SYSTEM *system, char *sound);

NEKO_API void sound_playSong(SOUND_SYSTEM *system, char *song);

NEKO_API void sound_destroy(SOUND_SYSTEM *system);