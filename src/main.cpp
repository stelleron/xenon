#include "xenon.hpp"

using namespace xenon;

class UntitledGame : public Application{
    
    Font font;
    Color color;
    float x = 2.5f;

    void config(AppConfig& config) {

    }

    void init(Context& ctx) {
        font.load("build/font.ttf", 16);
        color = Color::RGB(0, 255, 0);
    }   

    void update(Context& ctx) {
        if (ctx.keyboard.is_pressed(Key::Escape)) {
            ctx.window.close();
        }
    }

    void render(Context& ctx) {
        ctx.renderer.print(font, "Hello World", {20.0f, 20.0f}, {x, x}, Color::RGB(255, 255, 255), 0.0f);
    }

    void finish() {
    
    }
};

int main() {
    UntitledGame game;
    build(game);
}