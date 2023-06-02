#ifndef XENON_APP_CONFIG
    #define XENON_APP_CONFIG
    // Includes
    #include <string>
    #include "utils/color.hpp"
    #include "utils/vector.hpp"

    namespace xenon {
        struct AppConfig {
            int width;
            int height;
            std::string title;
            Color background_color;

            // Window settings
            bool resizable; 
            bool maximized; 
            bool fullscreen;
            bool desktop_fullscreen;
            bool decorated;
            bool focused;
            bool halt_while_hidden; // Set whether the app will pause while hidden

            // Framerate cap
            int fps_cap;
            // Opacity
            float opacity;
            // Min to max size
            Vector2 min_size;
            Vector2 max_size;
            // Window position
            Vector2 window_pos;

            // Default constructor
            AppConfig();
        };
    }
#endif