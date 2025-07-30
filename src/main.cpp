#include "xenon.hpp"
#include "window_surface.hpp"

using namespace xenon;

class UntitledGame : public Application{
    // For creating a smaller virtual surface
    WindowSurface virtual_surface;

    void config(AppConfig& config) {
        config.width = 1080;
        config.height = 720;
        config.resizable = false;
    }

    void init(Context& ctx) {
        virtual_surface.init(ctx);
    }

    void update(Context& ctx) {
        if (ctx.keyboard.is_pressed(Key::Escape)) {
            ctx.window.close();
        }
    }

    void render(Context& ctx) {
        virtual_surface.set(ctx);
            ctx.renderer.draw_circle(200, 150, 20, RED);
        virtual_surface.exit_and_render(ctx);
    }

    void finish() {

    }
};

int main() {
    UntitledGame game;
    build(game);
}
