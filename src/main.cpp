#include "xenon.hpp"

using namespace xenon;

class UntitledGame : public Application{
    Texture background;
    Texture ground;
    Font font;
    Color color;
    float x = 2.5f;

    void config(AppConfig& config) {

    }

    void init(Context& ctx) {
        font.load("build/font.ttf", 16);
        color = Color::RGB(0, 255, 0);

        background.load("background.png");
        ground.load("ground.png");
    }   

    void update(Context& ctx) {
        if (ctx.keyboard.is_pressed(Key::Escape)) {
            ctx.window.close();
        }
    }

    void render(Context& ctx) {
        ctx.renderer.draw(background);
        ctx.renderer.draw(ground, {0, ctx.window.get_size().y - 16});
    }

    void finish() {
    
    }
};

int main() {
    UntitledGame game;
    build(game);
}