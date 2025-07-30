#pragma once
using namespace xenon;
#include "states/base_state.hpp"
#include <map>
#include <string>

typedef std::map<std::string, std::function<BaseState*()>> StateMap;

class StateMachine {
    private:
        BaseState* state;
        StateMap s_map;
    public:
        StateMachine();
        ~StateMachine();

        void init(StateMap& s_map);
        void update(Context& ctx);
        void render(Context& ctx);

        void change_state(Context& ctx, std::string s_name);        
};