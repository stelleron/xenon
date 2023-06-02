#ifndef XENON_AUDIO
    #define XENON_AUDIO
    #include "soloud/soloud.h"
    #include "soloud/soloud_wav.h"
    #include "soloud/soloud_wavstream.h"
    
    namespace xenon {
        class Sound {
            private:
                SoLoud::Wav wave;
                bool is_init;
                int handle;
            public:
                // Properties
                float volume;
                float pan;

                // Base functions
                Sound();
                Sound(const char* path);
                Sound(unsigned char* data, size_t size);
                ~Sound();

                void load(const char* path);
                void load(unsigned char* data, size_t size);

                // Getters
                bool is_loaded() {return is_init;}
                SoLoud::Wav* get_wave();
                void set_handle(int handle) {this->handle = handle;}
                int get_handle() {return handle;}                
        };

        class Music {
            private:
                SoLoud::WavStream stream;
                bool is_init;
                int handle;
            public: 
                // Properties
                float volume;
                float pan;

                // Base functions
                Music();
                Music(const char* path);
                Music(unsigned char* data, size_t size);
                ~Music();

                void load(const char* path);
                void load(unsigned char* data, size_t size);

                // Getters
                bool is_loaded() {return is_init;}
                SoLoud::WavStream* get_stream() {return &stream;}
                void set_handle(int handle) {this->handle = handle;}
                int get_handle() {return handle;}  

        };

        class AudioContext {
            private:
                SoLoud::Soloud a_engine;
                float master_volume;
            public:
                AudioContext();
                ~AudioContext();

                // Master volume
                float get_master_volume();
                void set_master_volume(float volume); 

                int get_active_sounds();

                // Sound functions
                void play(Sound& sound);
                void stop(Sound& sound);
                void pause(Sound& sound);
                void resume(Sound& sound);
                bool is_playing(Sound& sound);
                void update(Sound& sound);

                // Music functions
                void play(Music& music);
                void stop(Music& music);
                void pause(Music& music);
                void resume(Music& music);
                bool is_playing(Music& music);
                void update(Music& music);
        };
    }   
#endif