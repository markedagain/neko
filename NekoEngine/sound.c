/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "sound.h"

void sound_initialize(SOUNDSYSTEM *system, DICT *sounds) {
  FMOD_RESULT result;
  FMOD_CAPS caps;
  FMOD_SPEAKERMODE speakerMode;
  char name[80] = { 0 };
  system->sounds = sounds;
  system->musicChannel = NULL;
  system->volume.master = 1.0f;
  system->volume.sound = 1.0f;
  system->volume.music = 1.0f;
  result = FMOD_System_Create(&system->system);
  result = FMOD_System_GetDriverCaps(system->system, 0, &caps, 0, &speakerMode);
  result = FMOD_System_SetSpeakerMode(system->system, speakerMode);
  //result = FMOD_System_SetDSPBufferSize(system->system, 512, 10);
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

void sound_loadSoundFromFile(SOUNDSYSTEM *system, char *name, void *data) {
  SOUND *sound = (SOUND *)malloc(sizeof(SOUND));
  FMOD_System_CreateSound(system->system, name, FMOD_DEFAULT, NULL, &sound->data);
  dict_set(system->sounds, name, sound);
}

void sound_loadSoundFromMemory(SOUNDSYSTEM *system, char *name, const char *data, size_t size) {
  SOUND *sound = (SOUND *)malloc(sizeof(SOUND));
  FMOD_CREATESOUNDEXINFO audioInfo;
  memset(&audioInfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
  audioInfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
  audioInfo.length = size;
  strcpy(sound->filename, name);
  sound->size = size;
  FMOD_System_CreateSound(system->system, data, FMOD_OPENMEMORY, &audioInfo, &sound->data);
  dict_set(system->sounds, name, sound);
}

void sound_playSound(SOUNDSYSTEM *system, char *sound) {
  SOUND *snd = (SOUND *)dict_get(system->sounds, sound);
  FMOD_CHANNEL *channel;
  FMOD_System_PlaySound(system->system, FMOD_CHANNEL_FREE, snd->data, false, &channel);
  FMOD_Channel_SetVolume(channel, system->volume.sound * system->volume.master);
}

void sound_playSong(SOUNDSYSTEM *system, char *song) {
  SOUND *snd = (SOUND *)dict_get(system->sounds, song);
  if (system->musicChannel != NULL)
    sound_stopSong(system);
  FMOD_System_PlaySound(system->system, FMOD_CHANNEL_FREE, snd->data, false, &system->musicChannel);
  FMOD_Channel_SetVolume(system->musicChannel, system->volume.music * system->volume.master);
  FMOD_Channel_SetMode(system->musicChannel, FMOD_LOOP_NORMAL);
  FMOD_Channel_SetLoopCount(system->musicChannel, -1);
}

void sound_stopSong(SOUNDSYSTEM *system) {
  FMOD_Channel_Stop(system->musicChannel);
  system->musicChannel = NULL;
}

void sound_destroy(SOUNDSYSTEM *system) {
  FMOD_System_Release(system->system);
  // TODO: RELEASE SOUNDS TOO
}

void sound_update(SOUNDSYSTEM *system) {
  FMOD_System_Update(system->system);
}

void sound_setVolume_master(SOUNDSYSTEM *system, float volume) {
  system->volume.master = volume;
  if (system->musicChannel != NULL)
    FMOD_Channel_SetVolume(system->musicChannel, system->volume.music * system->volume.master);
}
void sound_setVolume_sound(SOUNDSYSTEM *system, float volume) {
  system->volume.sound = volume;
}
void sound_setVolume_music(SOUNDSYSTEM *system, float volume) {
  system->volume.music = volume;
  if (system->musicChannel != NULL)
    FMOD_Channel_SetVolume(system->musicChannel, system->volume.music * system->volume.master);
}