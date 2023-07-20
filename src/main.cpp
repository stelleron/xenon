#include "xenon.hpp"

using namespace xenon;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float DESIRED_ASPECT_RATIO = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT);


class UntitledGame : public Application{
    void config(AppConfig& config) {
        config.resizable = true;
        config.width = WINDOW_WIDTH;
        config.height = WINDOW_HEIGHT;
    }

    void init(Context& ctx) {

    }   

    void update(Context& ctx) {
        if (ctx.keyboard.is_pressed(Key::Escape)) {
            ctx.window.close();
        }
        else if (ctx.window.was_resized()) {
            Vector2 window_size = ctx.window.get_size();
            float currentAspectRatio = static_cast<float>(window_size.x) / static_cast<float>(window_size.y);

            if (currentAspectRatio != DESIRED_ASPECT_RATIO) {
                if (currentAspectRatio > DESIRED_ASPECT_RATIO) {
                    window_size.x = static_cast<int>(window_size.y * DESIRED_ASPECT_RATIO);
                } else {
                    window_size.y = static_cast<int>(window_size.x / DESIRED_ASPECT_RATIO);
                }

                ctx.window.set_size(window_size);
                LOG(window_size);
            }
        }
    }

    void render(Context& ctx) {

    }

    void finish() {
    
    }
};

int main() {
    UntitledGame game;
    build(game);
}