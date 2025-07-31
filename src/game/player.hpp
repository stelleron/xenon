#pragma once
using namespace xenon;

class Player {
    private:

    public:
        Player();
        ~Player();

        void init(Context& ctx);
        void update(Context& ctx);
        void render(Context& ctx);
        void finish();
};