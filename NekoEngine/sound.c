/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

// http://katyscode.wordpress.com/2012/10/05/cutting-your-teeth-on-fmod-part-1-build-environment-initialization-and-playing-sounds/

#include "sound.h"

void sound_initialize(SOUND_SYSTEM *system, DICT *sounds) {
  FMOD_RESULT result;
  FMOD_CAPS caps;
  FMOD_SPEAKERMODE speakerMode;
  char name[80] = { 0 };
  result = FMOD_System_Create(&system->system);
  result = FMOD_System_GetDriverCaps(system->system, 0, &caps, 0, &speakerMode);
  result = FMOD_System_SetSpeakerMode(system->system, speakerMode);
  result = FMOD_System_SetDSPBufferSize(system->system, 1024, 10);
  result = FMOD_System_GetDriverInfo(system->system, 0, name, 256, 0);
  if (strstr(name, "SigmaTel")) {
    result = FMOD_System_SetSoftwareFormat(system->system, 48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, FMOD_DSP_RESAMPLER_LINEAR);
  }
  result = FMOD_System_Init(system->system, SOUND_CHANNELS, FMOD_INIT_NORMAL, NULL);
  if (result == FMOD_ERR_OUTPUT_CREATEBUFFER) {
    result = FMOD_System_SetSpeakerMode(system->system, FMOD_SPEAKERMODE_STEREO);
    result = FMOD_System_Init(system->system, SOUND_CHANNELS, FMOD_INIT_NORMAL, 0);
  }
}

void sound_loadSoundFromFile(SOUND_SYSTEM *system, char *name, void *data) {
  SOUND *sound = (SOUND *)malloc(sizeof(SOUND));
  FMOD_System_CreateSound(system->system, name, FMOD_DEFAULT, NULL, &sound->data);
  dict_set(system->sounds, name, sound);
}

void sound_loadSoundFromMemory(SOUND_SYSTEM *system, char *name, void *data) {
  SOUND *sound = (SOUND *)malloc(sizeof(SOUND));
  FMOD_System_CreateSound(system->system, name, FMOD_HARDWARE | FMOD_OPENMEMORY, NULL, &sound->data);
  dict_set(system->sounds, name, sound);
}

void sound_playSound(SOUND_SYSTEM *system, char *sound) {
  SOUND *snd = (SOUND *)dict_get(system->sounds, sound);
  FMOD_System_PlaySound(system->system, FMOD_CHANNEL_FREE, snd->data, false, NULL);
}

void sound_destroy(SOUND_SYSTEM *system) {
}

void sound_update(SOUND_SYSTEM *system) {
  FMOD_System_Update(system->system);
}