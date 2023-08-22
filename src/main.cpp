#include "xenon.hpp"

using namespace xenon;

class UntitledGame : public Application{
    Texture tex;
    float x = 1.0f;

    void config(AppConfig& config) {
        config.resizable = true;
        config.width = 800;
        config.height = 600;
    }

    void init(Context& ctx) {
        tex.load("player.png");
    }   

    void update(Context& ctx) {
        if (ctx.keyboard.is_pressed(Key::Escape)) {
            ctx.window.close();
        }
    }

    void render(Context& ctx) {
        ctx.renderer.draw(tex, {20.0, 20.0}, {x, x}, 0.0f);
        x += 0.01f;
    }

    void finish() {
    
    }
};

int main() {
    UntitledGame game;
    build(game);
}