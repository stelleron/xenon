#include "xenon.hpp"
#include "states/state_machine.hpp"

StateMachine::StateMachine() {
    state = nullptr;
}

StateMachine::~StateMachine() {
    if (state){
        state->finish();
        delete state;
    }
}

void StateMachine::init(StateMap& s_map) {
    this->s_map = s_map;
}

void StateMachine::update(Context& ctx) {
    if (state) state->update(ctx);
}

void StateMachine::render(Context& ctx) {
    if (state) state->render(ctx);
}

void StateMachine::change_state(Context& ctx, std::string s_name) {
    if (s_map.find(s_name) != s_map.end()) {
        if (state) {
            state->finish();
            delete state;
        }

        state = s_map[s_name](); 
        state->init(ctx);
    }
}