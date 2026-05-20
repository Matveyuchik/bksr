#define MINIAUDIO_IMPLEMENTATION
#include "audio.h"

static ma_engine engine;
static ma_sound sound;
static bool audio_initialized = false;
static bool sound_loaded = false;

bool play_sound(const char* filename)
{
    if (!audio_initialized) {
        if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
            fprintf(stderr, "Failed to initialize audio engine.\n");
            return false;
        }
        audio_initialized = true;
    }

    if (!sound_loaded) {
        if (ma_sound_init_from_file(&engine, filename, 0, NULL, NULL, &sound) != MA_SUCCESS) {
            fprintf(stderr, "Failed to load sound file: %s\n", filename);
            return false;
        }
        sound_loaded = true;
    }

    if (ma_sound_start(&sound) != MA_SUCCESS) {
        fprintf(stderr, "Failed to start sound.\n");
        return false;
    }

    return true;
}

void uninit_audio(void)
{
    if (sound_loaded) {
        ma_sound_uninit(&sound);
        sound_loaded = false;
    }

    if (audio_initialized) {
        ma_engine_uninit(&engine);
        audio_initialized = false;
    }
}
