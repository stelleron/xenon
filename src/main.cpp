#include "xenon.hpp"

using namespace xenon;

class UntitledGame : public Application{
    Texture background;
    Texture ground;
    Texture tex;
    Font font;
    Color color;
    float x = 0.0f;

    Vector2 vec;

    void config(AppConfig& config) {

    }

    void init(Context& ctx) {
        font.load("build/font.ttf");
        color = Color::RGB(0, 255, 0);

        background.load("background.png");
        ground.load("ground.png");
        tex.load("gliscor.png");

        vec = Font::get_text_size(font, "Hello World!" , 64, 1.0f);
    }   

    void update(Context& ctx) {
        if (ctx.keyboard.is_pressed(Key::Escape)) {
            ctx.window.close();
        }

        x += 1.0f;
    }

    void render(Context& ctx) {
        ctx.renderer.draw(tex, (Rectangle){{0.0, 0.0}, (float)tex.width, (float)tex.height}, {100.0, 100.0}, {1.0, 1.0}, x, WHITE);
    }

    void finish() {
    
    }
};

int main() {
    UntitledGame game;
    build(game);
}