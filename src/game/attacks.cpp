#include "xenon.hpp"
#include "game/attacks.hpp"

// Player's sword attack
PlayerSwordAttack::PlayerSwordAttack() {
    lifespan = 0;
}

void PlayerSwordAttack::start(LookDir dir, Vector2 p) {
    lifespan = 20;
    area = Rectangle(p, 5, 20);
    LOG("Attacking!");
}

void PlayerSwordAttack::update() {
    if (active()) {lifespan -= 1;}
}

void PlayerSwordAttack::render(Context& ctx) {
    ctx.renderer.draw(drawable::make(area, GRAY));
}

bool PlayerSwordAttack::active() {
    return lifespan != 0;
}