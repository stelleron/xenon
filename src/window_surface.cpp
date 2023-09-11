#include "xenon.hpp"
#include "window_surface.hpp"
#include "constants.hpp"

WindowSurface::WindowSurface() {

}

WindowSurface::~WindowSurface() { 

}

void WindowSurface::init(Context& ctx) {
    surface.load(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
}

void WindowSurface::set(Context& ctx) {
    ctx.renderer.set_surface(surface);
    ctx.renderer.fill(BACKGROUND_COLOR);
}

void WindowSurface::exit(Context& ctx) {
    ctx.renderer.exit_surface();
}

void WindowSurface::exit_and_render(Context& ctx) {
    exit(ctx);
    Vector2 window_size = ctx.window.get_size();

    float v_width = VIRTUAL_WIDTH;
    float v_height = VIRTUAL_HEIGHT;
    
    float x_scale = window_size.x/v_width;
    float y_scale = window_size.y/v_height;

    ctx.renderer.draw(surface, {0.0, 0.0}, {x_scale, y_scale});
}