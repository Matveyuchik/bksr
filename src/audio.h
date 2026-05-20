#ifndef BKSR_AUDIO_H
#define BKSR_AUDIO_H

#include <stdbool.h>
#include "miniaudio.h"

bool play_sound(const char* filename);
void uninit_audio(void);

#endif