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
    look_dir = LookDir::Up;
}

void Player::update(Context& ctx) {
    // If ATTACKING, just tick down attack
    if (sword_attack.active()) {
        sword_attack.update();
        return;
    }
    // ELSE, can process new moves or attacks
    // Vertical movement
    if (ctx.keyboard.is_held(xenon::Key::W)) {
        rect.pos.y -= PLAYER_SPEED * ctx.timer.dt();
        look_dir = LookDir::Up;
    }
    else if (ctx.keyboard.is_held(xenon::Key::S)) {
        rect.pos.y += PLAYER_SPEED * ctx.timer.dt();
        look_dir = LookDir::Down;
    }

    // Horizontal movement
    if (ctx.keyboard.is_held(xenon::Key::A)) {
        rect.pos.x -= PLAYER_SPEED * ctx.timer.dt();
        look_dir = LookDir::Left;
    }
    else if (ctx.keyboard.is_held(xenon::Key::D)) {
        rect.pos.x += PLAYER_SPEED * ctx.timer.dt();
        look_dir = LookDir::Right;
    }

    // Attack
    if (ctx.mouse.is_pressed(xenon::MouseButton::LeftButton)) {
        switch (look_dir) {
            case LookDir::Up : sword_attack.start(look_dir, {rect.pos.x + PLAYER_SIZE/2, rect.pos.y}); break;
            case LookDir::Down : sword_attack.start(look_dir, {rect.pos.x + PLAYER_SIZE/2, rect.pos.y + PLAYER_SIZE}); break;
            case LookDir::Left : sword_attack.start(look_dir, {rect.pos.x, rect.pos.y + PLAYER_SIZE/2}); break;
            case LookDir::Right : sword_attack.start(look_dir, {rect.pos.x + PLAYER_SIZE, rect.pos.y + PLAYER_SIZE/2}); break;
            default: break;
        }
    }
}

void Player::render(Context& ctx) {
    ctx.renderer.draw(drawable::make(rect, RED));

    if (sword_attack.active()) {sword_attack.render(ctx);}
}

void Player::finish() {

}