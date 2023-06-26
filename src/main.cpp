#include "xenon.hpp"

using namespace xenon;

class UntitledGame : public Application{
    
    Font font;

    void config(AppConfig& config) {
        config.vsync = true;
    }

    void init(Context& ctx) {
        font.load("build/font.ttf");
    }   

    void update(Context& ctx) {
        if (ctx.keyboard.is_pressed(Key::Escape)) {
            ctx.window.close();
        }
    }

    void render(Context& ctx) {
        std::string fps = std::to_string(ctx.timer.fps());
        fps += " FPS";
        ctx.renderer.print(font, fps, {20.0, 20.0}, {1.0, 1.0}, GREEN, 4);
    }

    void finish() {
    
    }
};

int main() {
    UntitledGame game;
    build(game);
}