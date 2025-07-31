#include "xenon.hpp"
#include "game/attacks.hpp"

// Player's sword attack
PlayerSwordAttack::PlayerSwordAttack() {
    lifespan = 0;
}

void PlayerSwordAttack::start(LookDir dir, Vector2 p) {
    lifespan = 20;
    switch (dir) {
        case LookDir::Up    : area = Rectangle(p.x - PSwA_WIDTH/2, p.y - PSwA_HEIGHT/2, PSwA_WIDTH, PSwA_HEIGHT); break;
        case LookDir::Down  : area = Rectangle(p.x - PSwA_WIDTH/2, p.y, PSwA_WIDTH, PSwA_HEIGHT); break;
        case LookDir::Left  : area = Rectangle(p.x - PSwA_HEIGHT/2, p.y - PSwA_WIDTH/2, PSwA_HEIGHT, PSwA_WIDTH); break;
        case LookDir::Right : area = Rectangle(p.x, p.y - PSwA_WIDTH/2, PSwA_HEIGHT, PSwA_WIDTH); break;
        default: break;
    }
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