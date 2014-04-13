/******************************************************************************
Filename: sound.h

Project Name: Game School Simulator 2015

Author: Adam Rezich

All content � 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


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
  //FMOD_CHANNEL *channels.music;
  struct {
    FMOD_CHANNEL *music;
    FMOD_CHANNEL *ambient1;
    FMOD_CHANNEL *ambient2;
  } channels;
  struct {
    float master;
    float music;
    float sound;
    float ambient;
    float ambient1;
    float ambient2;
  } volume;
  /*
  0 - title (non-loop)
  1 - funky (non-loop)
  2 - lame (non-loop)
  */
} SOUNDSYSTEM;

NEKO_API void sound_initialize(SOUNDSYSTEM *system, DICT *sounds);

NEKO_API void sound_playSound(SOUNDSYSTEM *system, char *sound);

NEKO_API void sound_playSong(SOUNDSYSTEM *system, char *song);
NEKO_API void sound_playSongLooped(SOUNDSYSTEM *system, char *song);
NEKO_API void sound_stopSong(SOUNDSYSTEM *system);
NEKO_API void sound_playAmbient(SOUNDSYSTEM *system, char *ambient, char *ambient2);

NEKO_API void sound_destroy(SOUNDSYSTEM *system);

NEKO_API void sound_setVolume_master(SOUNDSYSTEM *system, float volume);
NEKO_API void sound_setVolume_sound(SOUNDSYSTEM *system, float volume);
NEKO_API void sound_setVolume_music(SOUNDSYSTEM *system, float volume);
NEKO_API void sound_setVolume_ambient(SOUNDSYSTEM *system, float volume, float volume1, float volume2);

NEKO_API void sound_update(SOUNDSYSTEM *system);

void sound_loadSoundFromMemory(SOUNDSYSTEM *system, char *name, const char *data, size_t size);

#endif