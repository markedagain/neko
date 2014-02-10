/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __SOUND_H__
#define __SOUND_H__

#include "neko.h"
#include "dictionary.h"
#include "../fmod/fmod.h"
#include "../fmod/fmod_errors.h"
#include "data.h"

#define SOUND_CHANNELS 8

typedef struct soundSystem_t {
  FMOD_SYSTEM *system;
  FMOD_SPEAKERMODE speakerMode;
  DICT *sounds;
} SOUNDSYSTEM;

NEKO_API void sound_initialize(SOUNDSYSTEM *system, DICT *sounds);

NEKO_API void sound_playSound(SOUNDSYSTEM *system, char *sound);

NEKO_API void sound_playSong(SOUNDSYSTEM *system, char *song);

NEKO_API void sound_destroy(SOUNDSYSTEM *system);

void sound_loadSoundFromMemory(SOUNDSYSTEM *system, char *name, const char *data, size_t size);

#endif