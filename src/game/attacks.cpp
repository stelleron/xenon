#include "xenon.hpp"
#include "game/attacks.hpp"

// Player's sword attack
PlayerSwordAttack::PlayerSwordAttack() {
    lifespan = 0;
}

void PlayerSwordAttack::start(LookDir dir, Vector2 p) {
    lifespan = 20;
    switch (dir) {
        case LookDir::Up    : area = Rectangle(p.x - 12.5, p.y - 5, 25, 5); break;
        case LookDir::Down  : area = Rectangle(p.x - 12.5, p.y, 25, 5); break;
        case LookDir::Left  : area = Rectangle(p.x - 5, p.y - 12.5, 5, 25); break;
        case LookDir::Right : area = Rectangle(p.x, p.y - 12.5, 5, 25); break;
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