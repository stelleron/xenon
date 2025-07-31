#include "xenon.hpp"
#include "constants.hpp"
#include "game/player.hpp"


Player::Player() {

}

Player::~Player() {

}

void Player::init(Context& ctx) {
    rect = Rectangle(
        (VIRTUAL_WIDTH - PLAYER_SIZE)/2,
        (VIRTUAL_HEIGHT - PLAYER_SIZE)/2,
        PLAYER_SIZE,
        PLAYER_SIZE
    );
    look_point = Circle(
        Vector2{VIRTUAL_WIDTH/2, VIRTUAL_HEIGHT/2},
        4
    );
}

void Player::update(Context& ctx) {
    // Vertical movement
    if (ctx.keyboard.is_held(xenon::Key::W)) {
        rect.pos.y -= PLAYER_SPEED * ctx.timer.dt();
        look_point.center = Vector2{rect.pos.x + PLAYER_SIZE/2, rect.pos.y};
    }
    else if (ctx.keyboard.is_held(xenon::Key::S)) {
        rect.pos.y += PLAYER_SPEED * ctx.timer.dt();
        look_point.center = Vector2{rect.pos.x + PLAYER_SIZE/2, rect.pos.y + PLAYER_SIZE};
    }

    // Horizontal movement
    if (ctx.keyboard.is_held(xenon::Key::A)) {
        rect.pos.x -= PLAYER_SPEED * ctx.timer.dt();
        look_point.center = Vector2{rect.pos.x, rect.pos.y + PLAYER_SIZE/2};
    }
    else if (ctx.keyboard.is_held(xenon::Key::D)) {
        rect.pos.x += PLAYER_SPEED * ctx.timer.dt();
        look_point.center = Vector2{rect.pos.x + PLAYER_SIZE, rect.pos.y + PLAYER_SIZE/2};
    }

    // Attack
    if (ctx.mouse.is_pressed(xenon::MouseButton::LeftButton)) {}
}

void Player::render(Context& ctx) {
    ctx.renderer.draw(drawable::make(rect, RED));
    ctx.renderer.draw(drawable::make(look_point, GREEN));
}

void Player::finish() {

}