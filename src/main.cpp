#include "xenon.hpp"

using namespace xenon;

class UntitledGame : public Application{
    Font font;
    Shader shader;

    void config(AppConfig& config) {
        config.resizable = true;
        config.width = 800;
        config.height = 600;
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