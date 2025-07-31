#pragma once
using namespace xenon;

#include "game/attacks.hpp"

#define PLAYER_SPEED 100
#define PLAYER_SIZE 20

class Player {
    private:
        Rectangle rect;
        LookDir look_dir;

        PlayerSwordAttack sword_attack;
    public:
        Player();
        ~Player();

        void init(Context& ctx);
        void update(Context& ctx);
        void render(Context& ctx);
        void finish();
};