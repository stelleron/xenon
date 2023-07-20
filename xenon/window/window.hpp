#ifndef XENON_WINDOW
    #define XENON_WINDOW

    // Includes
    #include <SDL2/SDL.h>
    #include "app/app_config.hpp"

    namespace xenon {
        // Used to store a window
        class Window {
            private:
                SDL_Window* window;
                Color background_color;
                bool halt_while_hidden;
                bool should_window_close;

            public:
                Window();
                ~Window();

                void init(const AppConfig& config);
                void poll_events();
                void close();
                bool should_close();
                bool is_active();
                void fill();
                void swap_buffer();

                void set_data(void* ptr);
                void* get_data();

                void update_title(const char* title); 
                Vector2 get_window_size();
                Vector2 get_framebuffer_size();
                void set_min_size(Vector2 minDim);
                void set_max_size(Vector2 maxDim);
                void set_window_pos(Vector2 windowPos);
                void set_window_size(Vector2 windowSize);
                void restore();
                void minimize();
                void maximize();
            
        };
    }
#endif