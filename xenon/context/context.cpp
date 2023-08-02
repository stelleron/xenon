#include "context/context.hpp"
#include "utils/logger.hpp"

#define INVOKE_RENDER_FUNC(args) if (is_locked) {ERROR("Error: Renderer cannot be accessed by any other function but the render() function")} else { renderer->args; }

namespace xenon {
    Context::Context() {
        window.set_event_data(events.get());
        mouse.set_event_data(events.get());
        keyboard.set_event_data(events.get());
    }

    Context::~Context() {

    }

    // Timer context impl.
    void Context::TimerContext::set(float dtime) {
        this->dtime = dtime;
        total_dt += dtime;
        dt_history.push(dtime);

        if (dt_history.size() > 25) {
            total_dt -= dt_history.front();
            dt_history.pop();
        }
    }

    int Context::TimerContext::fps() {
        float average_dt = total_dt/25;
        return (int)roundf(1.0f/average_dt);
    }

    // Render context impl.
    void Context::RenderContext::init(Renderer* renderer) {
        renderer->init();
        is_locked = true;
        this->renderer = renderer;
    }
    void Context::RenderContext::set_default_camera(Camera& camera) {
        INVOKE_RENDER_FUNC(set_default_camera(camera))
    }
    void Context::RenderContext::set_default_shader(Shader& shader) {
        INVOKE_RENDER_FUNC(set_default_shader(shader))
    }
    void Context::RenderContext::set_current_camera(Camera& camera) {
        INVOKE_RENDER_FUNC(set_current_camera(camera))
    }
    void Context::RenderContext::set_current_shader(Shader& shader) {
        INVOKE_RENDER_FUNC(set_current_shader(shader))
    }
    void Context::RenderContext::use_default_camera() {
        INVOKE_RENDER_FUNC(use_default_camera())
    }
    void Context::RenderContext::use_default_shader() {
        INVOKE_RENDER_FUNC(use_default_shader())
    }
    void Context::RenderContext::set_surface(Surface& surface) {
        INVOKE_RENDER_FUNC(set_surface(surface))
    }
    void Context::RenderContext::set_window(Window& window) {
        INVOKE_RENDER_FUNC(set_window(window));
    }
    void Context::RenderContext::exit_surface() {
        INVOKE_RENDER_FUNC(exit_surface())
    }
    void Context::RenderContext::fill(Color color) {
        INVOKE_RENDER_FUNC(fill(color))
    }
    void Context::RenderContext::draw(VertexArray& vArray) {
        INVOKE_RENDER_FUNC(draw(vArray))
    }
    void Context::RenderContext::draw_point(float x, float y, Color color) {
        INVOKE_RENDER_FUNC(draw_point(x, y, color))
    }
    void Context::RenderContext::draw_point(Vector2 pos, Color color) {
        INVOKE_RENDER_FUNC(draw_point(pos, color))
    }
    void Context::RenderContext::draw(const Point& point) {
        INVOKE_RENDER_FUNC(draw(point))
    }
    void Context::RenderContext::draw(const DrawPoint& point) {
        INVOKE_RENDER_FUNC(draw(point))
    }
    void Context::RenderContext::draw_line(float startX, float startY, float endX, float endY, Color color) {
        INVOKE_RENDER_FUNC(draw_line(startX, startY, endX, endY, color))
    }
    void Context::RenderContext::draw_line(Vector2 startPos, Vector2 endPos, Color color) {
        INVOKE_RENDER_FUNC(draw_line(startPos, endPos, color))
    }
    void Context::RenderContext::draw(const Line& line) {
        INVOKE_RENDER_FUNC(draw(line))
    }
    void Context::RenderContext::draw(const DrawLine& line) {
        INVOKE_RENDER_FUNC(draw(line))
    }
    void Context::RenderContext::draw_triangle(Vector2 point1, Vector2 point2, Vector2 point3, Color color) {
        INVOKE_RENDER_FUNC(draw_triangle(point1, point2, point3, color))
    }
    void Context::RenderContext::draw(const Triangle& triangle) {
        INVOKE_RENDER_FUNC(draw(triangle))
    }
    void Context::RenderContext::draw(const DrawTriangle& triangle)  {
        INVOKE_RENDER_FUNC(draw(triangle))
    }
    void Context::RenderContext::draw_square(float x, float y, float size, Color color) {
        INVOKE_RENDER_FUNC(draw_square(x, y, size, color))
    }
    void Context::RenderContext::draw_square(Vector2 pos, float size, Color color) {
        INVOKE_RENDER_FUNC(draw_square(pos, size, color))
    }
    void Context::RenderContext::draw_rect(float x, float y, float width, float height, Color color) {
        INVOKE_RENDER_FUNC(draw_rect(x, y, width, height, color))
    }
    void Context::RenderContext::draw_rect(Vector2 pos, float width, float height, Color color)  {
        INVOKE_RENDER_FUNC(draw_rect(pos, width, height, color))
    }
    void Context::RenderContext::draw_quad(Vector2 point1, Vector2 point2, Vector2 point3, Vector2 point4, Color color) {
        INVOKE_RENDER_FUNC(draw_quad(point1, point2, point3, point4, color))
    }
    void Context::RenderContext::draw(const Rectangle& rectangle) {
        INVOKE_RENDER_FUNC(draw(rectangle))
    }
    void Context::RenderContext::draw(const Quadrilateral& quad) {
        INVOKE_RENDER_FUNC(draw(quad))
    }
    void Context::RenderContext::draw(const DrawQuad& quad) {
        INVOKE_RENDER_FUNC(draw(quad))
    }
    void Context::RenderContext::draw_circle(float x, float y, float radius, Color color) {
        INVOKE_RENDER_FUNC(draw_circle(x, y, radius, color))
    }
    void Context::RenderContext::draw_circle(Vector2 pos, float radius, Color color) {
        INVOKE_RENDER_FUNC(draw_circle(pos, radius, color))
    }
    void Context::RenderContext::draw(const Circle& circle) {
        INVOKE_RENDER_FUNC(draw(circle))
    }
    void Context::RenderContext::draw(const DrawCircle& circle) {
        INVOKE_RENDER_FUNC(draw(circle))
    }
    void Context::RenderContext::draw(Sprite& sprite) {
        INVOKE_RENDER_FUNC(draw(sprite))
    }
    void Context::RenderContext::draw(Texture& tex, Vector2 pos, Vector2 scale, float rotation, Color color) {
        INVOKE_RENDER_FUNC(draw(tex, pos, scale, rotation, color))
    }
    void Context::RenderContext::draw(Texture& tex, Rectangle targetRect, Vector2 pos, Vector2 scale, float rotation, Color color) {
        INVOKE_RENDER_FUNC(draw(tex, targetRect, pos, scale, rotation, color))
    }
    void Context::RenderContext::draw(Surface& surface, Vector2 pos, Vector2 scale, float rotation, Color color) {
        INVOKE_RENDER_FUNC(draw(surface, pos, scale, rotation, color))
    }
    void Context::RenderContext::draw(Surface& surface, Rectangle targetRect, Vector2 pos, Vector2 scale, float rotation, Color color) {
        INVOKE_RENDER_FUNC(draw(surface, targetRect, pos, scale, rotation, color))
    }
    void Context::RenderContext::print(Font& font, std::string message, Vector2 pos, Vector2 scale, Color color, float spacing) {
        INVOKE_RENDER_FUNC(print(font, message, pos, scale, color, spacing))
    }
    void Context::RenderContext::draw_batch() {
        INVOKE_RENDER_FUNC(draw_batch())
    }

}