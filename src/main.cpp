#include "xenon.hpp"

using namespace xenon;

class UntitledGame : public Application{
    
    Font font;

    void config(AppConfig& config) {

    }

    void init(Context& ctx) {
        font.load("build/font.ttf", 16);
    }   

    void update(Context& ctx) {
        if (ctx.keyboard.is_pressed(Key::Escape)) {
            ctx.window.close();
        }
    }

    void render(Context& ctx) {
        ctx.renderer.print(font, "Hello World!", {0.0, 0.0}, {1.0, 1.0}, Color::RGB(0, 255, 0), 0);
        // ctx.renderer.draw(font.fontTex);
    }

    void finish() {
    
    }
};

int main() {
    UntitledGame game;
    build(game);
}