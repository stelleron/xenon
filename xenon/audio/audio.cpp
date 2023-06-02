#include "audio/audio.hpp"
#include "utils/logger.hpp"
#include "res/filesystem.hpp"

namespace xenon {
    // Audio context impl.
    AudioContext::AudioContext() {
        a_engine.init();
        master_volume = a_engine.getGlobalVolume();
    }
    AudioContext::~AudioContext() {
        a_engine.deinit();
    }

    void AudioContext::set_master_volume(float volume) {
        master_volume = volume;
        a_engine.setGlobalVolume(volume);
    }

    float AudioContext::get_master_volume() {
        return master_volume;
    }

    int AudioContext::get_active_sounds() {
        return a_engine.getActiveVoiceCount();
    }

    void AudioContext::play(Sound& sound) {
        int h;
        if (sound.is_loaded()) {
            int h = a_engine.play(*sound.get_wave(), sound.volume, sound.pan);
            sound.set_handle(h);
        }
    }

    void AudioContext::stop(Sound& sound) {
        int handle = sound.get_handle();
        if (sound.is_loaded() && handle != 0) {
            sound.set_handle(0);
        }
    }

    void AudioContext::pause(Sound& sound) {
        int handle = sound.get_handle();
        if (sound.is_loaded() && handle != 0) {
            a_engine.setPause(handle, 1);
        }
    }

    void AudioContext::resume(Sound& sound) {
        int handle = sound.get_handle();
        if (sound.is_loaded() && handle != 0) {
            a_engine.setPause(handle, 0);
        }
    }

    bool AudioContext::is_playing(Sound& sound) {
        int handle = sound.get_handle();
        if (sound.is_loaded() && handle != 0) {
            return a_engine.isValidVoiceHandle(handle);
        }
        else {
            return false;
        }
    }

    void AudioContext::update(Sound& sound) {
        int handle = sound.get_handle();
        if (is_playing(sound)) {
            a_engine.setVolume(handle, sound.volume);
            a_engine.setPan(handle, sound.pan);
        }
    }

    void AudioContext::play(Music& music) {
        int h;
        if (music.is_loaded()) {
            int h = a_engine.play(*music.get_stream(), music.volume, music.pan);
            music.set_handle(h);
        }
    }

    void AudioContext::stop(Music& music) {
        int handle = music.get_handle();
        if (music.is_loaded() && handle != 0) {
            music.set_handle(0);
        }
    }

    void AudioContext::pause(Music& music) {
        int handle = music.get_handle();
        if (music.is_loaded() && handle != 0) {
            a_engine.setPause(handle, 1);
        }
    }

    void AudioContext::resume(Music& music) {
        int handle = music.get_handle();
        if (music.is_loaded() && handle != 0) {
            a_engine.setPause(handle, 0);
        }
    }

    bool AudioContext::is_playing(Music& music) {
        int handle = music.get_handle();
        if (music.is_loaded() && handle != 0) {
            return a_engine.isValidVoiceHandle(handle);
        }
        else {
            return false;
        }
    }

    void AudioContext::update(Music& music) {
        int handle = music.get_handle();
        if (is_playing(music)) {
            a_engine.setVolume(handle, music.volume);
            a_engine.setPan(handle, music.pan);
        }
    }

    // Sound impl.
    Sound::Sound() {
        is_init = false;
        handle = 0;
        volume = 1.0f;
        pan = 0.0f;
    }

    Sound::Sound(const char* path) {
        load(path);
    }

    Sound::Sound(unsigned char* data, size_t size) {
        load(data, size);
    }

    void Sound::load(const char* path) {
        size_t fsize;
        unsigned char* data = filesystem::load_file_data(path, fsize);
        load(data, fsize);
    }

    void Sound::load(unsigned char* data, size_t size) {
        wave.loadMem(data, size);
        is_init = true;
    }

    SoLoud::Wav* Sound::get_wave() {
        return &wave;
    }

    Sound::~Sound() {
        
    }
    // Music impl.
    Music::Music() {
        is_init = false;
        handle = 0;
        volume = 1.0f;
        pan = 0.0f;
    }

    Music::Music(const char* path) {
        load(path);
    }

    Music::Music(unsigned char* data, size_t size) {
        load(data, size);
    }

    void Music::load(const char* path) {
        size_t fsize;
        unsigned char* data = filesystem::load_file_data(path, fsize);
        load(data, fsize);
    }

    void Music::load(unsigned char* data, size_t size) {
        stream.loadMem(data, size);
        is_init = true;
    }


    Music::~Music() {

    }
}
