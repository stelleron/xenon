#include "xenon.hpp"

using namespace xenon;

class UntitledGame : public Application{
    void config(AppConfig& config) {
        config.resizable = true;
        config.background_color = Color::RGB(220, 220, 220);
    }

    void init(Context& ctx) {

    }

    void update(Context& ctx) {
        if (ctx.keyboard.is_pressed(Key::Escape)) {
            ctx.window.close();
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
