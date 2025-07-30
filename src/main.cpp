#include "xenon.hpp"
#include "constants.hpp"
#include "window_surface.hpp"

#include "states/base_state.hpp"
#include "states/state_machine.hpp"
#include "states/play_state.hpp"
#include "states/state_lambda.hpp"

using namespace xenon;

class UntitledGame : public Application{
    // For creating a smaller virtual surface
    WindowSurface virtual_surface;
    // For managing scenes
    StateMap state_map;
    StateMachine state_machine;

    void config(AppConfig& config) {
        config.width = WND_WIDTH;
        config.height = WND_HEIGHT;
        config.resizable = false;
    }

    void init(Context& ctx) {
        virtual_surface.init(ctx);

        ctx.userdata.set_data("state_machine", (void*)&state_machine);

        state_map["play"] = play_state_lambda;

        state_machine.init(state_map);
        state_machine.change_state(ctx, "play");
    }

    void update(Context& ctx) {
        state_machine.update(ctx);
    }

    void render(Context& ctx) {
        virtual_surface.set(ctx);
            state_machine.render(ctx);
        virtual_surface.exit_and_render(ctx);
    }

    void finish() {

    }
};

int main() {
    UntitledGame game;
    build(game);
}
