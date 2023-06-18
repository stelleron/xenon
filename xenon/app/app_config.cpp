#include "app/app_config.hpp"

namespace xenon {
    AppConfig::AppConfig() {
        width = 800;
        height = 600;
        title = "Untitled Game";
        background_color = Color::RGB(20, 20, 20);

        resizable = false;
        fullscreen = false;
        desktop_fullscreen = false;
        decorated = true;
        maximized = false;
        focused = true;
        halt_while_hidden = true;
        vsync = true;

        fps_cap = 60;
        opacity = 1.0f;
        min_size = Vector2(-1, -1);
        max_size = Vector2(-1, -1);
        window_pos = Vector2(-1, -1);
    }
}