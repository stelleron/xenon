#pragma once
using namespace xenon;

#define PLAYER_SPEED 100
#define PLAYER_SIZE 20

class Player {
    private:
        Rectangle rect;
        Circle look_point;
    public:
        Player();
        ~Player();

        void init(Context& ctx);
        void update(Context& ctx);
        void render(Context& ctx);
        void finish();
};