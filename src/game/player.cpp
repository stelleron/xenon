#include "xenon.hpp"
#include "game/player.hpp"


Player::Player() {

}

Player::~Player() {

}

void Player::init(Context& ctx) {

}

void Player::update(Context& ctx) {

}

void Player::render(Context& ctx) {
    ctx.renderer.draw_rect(50, 50, 20, 20, RED);
}

void Player::finish() {

}