#pragma once

std::function<BaseState*()> play_state_lambda = []() {
    return new PlayState();
};
