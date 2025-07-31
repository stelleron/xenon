#include "xenon.hpp"
#include "constants.hpp"
#include "game/player.hpp"


Player::Player() {

}

Player::~Player() {

}

void Player::init(Context& ctx) {
    rect = Rectangle(VIRTUAL_WIDTH/2 - 10, VIRTUAL_HEIGHT/2 - 10, 20, 20);
}

void Player::update(Context& ctx) {
    if (ctx.keyboard.is_held(xenon::Key::W)) {rect.pos.y -= PLAYER_SPEED * ctx.timer.dt();}
    if (ctx.keyboard.is_held(xenon::Key::S)) {rect.pos.y += PLAYER_SPEED * ctx.timer.dt();}

    if (ctx.keyboard.is_held(xenon::Key::A)) {rect.pos.x -= PLAYER_SPEED * ctx.timer.dt();}
    if (ctx.keyboard.is_held(xenon::Key::D)) {rect.pos.x += PLAYER_SPEED * ctx.timer.dt();}
}

void Player::render(Context& ctx) {
    ctx.renderer.draw(drawable::make(rect, RED));
}

void Player::finish() {

}