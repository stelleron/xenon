#include "xenon.hpp"

using namespace xenon;

class UntitledGame : public Application{
    
    void config(AppConfig& config) {
        config.resizable = true;
        config.maximized = true;
        config.desktop_fullscreen = true;
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