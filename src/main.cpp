#include "xenon.hpp"

using namespace xenon;

class UntitledGame : public Application{
    
    Font font;

    void config(AppConfig& config) {

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
        ctx.renderer.print(font, "Hello World!", {20.0, 20.0}, {1.0, 1.0}, GREEN, 0);
    }

    void finish() {
    
    }
};

int main() {
    UntitledGame game;
    build(game);
}