#include "xenon.hpp"
#include "constants.hpp"
#include "window_surface.hpp"
#include "states/play_state.hpp"
#include "states/state_machine.hpp"

PlayState::PlayState() {

}

PlayState::~PlayState() {
    
}

void PlayState::init(Context& ctx) {
    player.init(ctx);
}

void PlayState::update(Context& ctx) {
    player.update(ctx);
}

void PlayState::render(Context& ctx) {
    player.render(ctx);
}

void PlayState::finish() {

}