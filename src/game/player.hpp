#pragma once
using namespace xenon;

#define PLAYER_SPEED 100

class Player {
    private:
        Rectangle rect;
    public:
        Player();
        ~Player();

        void init(Context& ctx);
        void update(Context& ctx);
        void render(Context& ctx);
        void finish();
};