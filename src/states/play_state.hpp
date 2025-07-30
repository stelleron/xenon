#pragma once 
using namespace xenon;
#include "states/base_state.hpp"

class PlayState : public BaseState {
    private:

    public:
        PlayState();
        ~PlayState();

        void init(Context& ctx);
        void update(Context& ctx);
        void render(Context& ctx);
        void finish();
};