#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include <Arduino.h>
#include "App.h"

// Functions
TaskHandle_t InitAudio();
void PlayNote(note_t note, uint8_t octave, uint32_t time);
void AudioEngineTask(void *parameter);

#endif