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
        font.load("font.ttf");
        
        size_t size;
        const char* v_shader = filesystem::load_file_text("shader.vs", size);
        const char* f_shader = filesystem::load_file_text("shader.fs", size);

        shader.load(v_shader, f_shader);
    }   

    void update(Context& ctx) {
        if (ctx.keyboard.is_pressed(Key::Escape)) {
            ctx.window.close();
        }
    }

    void render(Context& ctx) {
        shader.set_float("stuff", 0.6f);
        ctx.renderer.set_current_shader(shader);

        ctx.renderer.print(font, "Hello World", {2.0, 2.0}, {20.0/32.0, 20.0/32.0}, WHITE, 0.0f);
    }

    void finish() {
    
    }
};

int main() {
    UntitledGame game;
    build(game);
}