#include "xenon.hpp"

using namespace xenon;

class UntitledGame : public Application{
    int a = 0;

    void config(AppConfig& config) {
        config.resizable = false;
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