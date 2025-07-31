#pragma once
using namespace xenon;

enum LookDir {
    Left,
    Right,
    Down,
    Up
};

enum CharType {
    TypePlayer,
    TypeEnemy
};

// Player's sword attack
#define PSwA_WIDTH 30
#define PSwA_HEIGHT 12

struct PlayerSwordAttack {
    Rectangle area;
    int lifespan;

    PlayerSwordAttack();

    void start(LookDir dir, Vector2 p);
    void update();
    void render(Context& ctx);
    bool active();
};