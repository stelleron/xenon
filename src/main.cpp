#include "xenon.hpp"

using namespace xenon;

class UntitledGame : public Application{
    Texture background;
    Texture ground;
    Font font;
    Color color;
    float x = 2.5f;

    std::string message = "Hello World!";
    Vector2 vec;

    void config(AppConfig& config) {

    }

    void init(Context& ctx) {
        font.load("build/font.ttf");
        color = Color::RGB(0, 255, 0);

        background.load("background.png");
        ground.load("ground.png");

        vec = Font::get_text_size(font, message , 32, 1.0f);
    }   

    void update(Context& ctx) {
        if (ctx.keyboard.is_pressed(Key::Escape)) {
            ctx.window.close();
        }
    }

    void render(Context& ctx) {
        ctx.renderer.draw_rect({400.0 - vec.x/2, 0.0}, vec.x, vec.y, GREEN);
        ctx.renderer.print(font, message, {400.0 - vec.x/2, 0.0f}, {1.0f, 1.0f}, WHITE, 1.0f);
        ctx.renderer.draw_line(400.0, 0.0, 400.0, 600.0, RED);
    }

    void finish() {
    
    }
};

int main() {
    UntitledGame game;
    build(game);
}