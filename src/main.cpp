#include "xenon.hpp"

using namespace xenon;

class UntitledGame : public Application{
    Font font;

    void config(AppConfig& config) {
        config.resizable = true;
    }

    void init(Context& ctx) {
        font.load("font.ttf");
    }   

    void update(Context& ctx) {
        if (ctx.keyboard.is_pressed(Key::Escape)) {
            ctx.window.close();
        }
    }

    void render(Context& ctx) {
        ctx.renderer.print(font, "Hello World", {20.0, 20.0}, {20.0/32.0, 20.0/32.0});
    }

    void finish() {
    
    }
};

int main() {
    UntitledGame game;
    build(game);
}