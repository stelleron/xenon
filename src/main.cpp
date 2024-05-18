#include "xenon.hpp"
#include "window_surface.hpp"
#include "constants.hpp"
#include <iostream>

using namespace xenon;

class UntitledGame : public Application{
    WindowSurface w_surface;
    Surface surface;

    Texture player;
    Texture enemy;
    Texture tile;
    Texture walls;

    void config(AppConfig& config) {
        config.resizable = true;
    }

    void init(Context& ctx) {
        w_surface.init(ctx);
        surface.load(160, 160);

        player.load("player.png");
        enemy.load("spr_guard.png");
        tile.load("tile.png");
        walls.load("walls.png");
    }   

    void update(Context& ctx) {
        if (ctx.keyboard.is_pressed(Key::Escape)) {
            ctx.window.close();
        }
    }

    void render(Context& ctx) {
        w_surface.set(ctx);
        w_surface.exit(ctx);

        ctx.renderer.set_surface(surface);
            for (int x = 0; x < 100; x++) {
                Vector2 board_pos = {floor(x/ROW_SIZE), x % COLUMN_SIZE};
                if (x == 0) {
                    ctx.renderer.draw(walls, (Rectangle){32.0f, 16.0f, 16.0f, 16.0f}, {board_pos.x * SQUARE_SIZE, board_pos.y * SQUARE_SIZE}, {1, 1});
                }
                else if (x > 0 && x < 9) {
                    ctx.renderer.draw(walls, (Rectangle){16.0f, 16.0f, 16.0f, 16.0f}, {board_pos.x * SQUARE_SIZE, board_pos.y * SQUARE_SIZE}, {1, 1});
                }
                else if (x == 9) {
                    ctx.renderer.draw(walls, (Rectangle){48.0f, 16.0f, 16.0f, 16.0f}, {board_pos.x * SQUARE_SIZE, board_pos.y * SQUARE_SIZE}, {1, 1});
                }
                else if (x == 90) {
                    ctx.renderer.draw(walls, (Rectangle){32.0f, 0.0f, 16.0f, 16.0f}, {board_pos.x * SQUARE_SIZE, board_pos.y * SQUARE_SIZE}, {1, 1});
                }
                else if (x > 90 && x < 99) {
                    ctx.renderer.draw(walls, (Rectangle){16.0f, 0.0f, 16.0f, 16.0f}, {board_pos.x * SQUARE_SIZE, board_pos.y * SQUARE_SIZE}, {1, 1});
                }
                else if (x == 99) {
                    ctx.renderer.draw(walls, (Rectangle){48.0f, 0.0f, 16.0f, 16.0f}, {board_pos.x * SQUARE_SIZE, board_pos.y * SQUARE_SIZE}, {1, 1});
                }
                else if (x % COLUMN_SIZE == 0) {
                    ctx.renderer.draw(walls, (Rectangle){0.0f, 0.0f, 16.0f, 16.0f}, {board_pos.x * SQUARE_SIZE, board_pos.y * SQUARE_SIZE}, {1, 1});
                }
                else if (x % COLUMN_SIZE == 9) {
                    ctx.renderer.draw(walls, (Rectangle){0.0f, 16.0f, 16.0f, 16.0f}, {board_pos.x * SQUARE_SIZE, board_pos.y * SQUARE_SIZE}, {1, 1});
                }
                else {
                    ctx.renderer.draw(tile, {board_pos.x * SQUARE_SIZE, board_pos.y * SQUARE_SIZE}, {1, 1});
                    if (x == 47) {
                        ctx.renderer.draw(player, {board_pos.x * SQUARE_SIZE, board_pos.y * SQUARE_SIZE}, {1, 1});
                    }
                }
            }
        ctx.renderer.exit_surface();

        w_surface.set(ctx);

        Vector2 gameboard_pos = {VIRTUAL_WIDTH/2 - (ROW_SIZE * SQUARE_SIZE)/2, VIRTUAL_HEIGHT/2 - (COLUMN_SIZE * SQUARE_SIZE)/2};
        ctx.renderer.draw(surface, gameboard_pos);

        w_surface.exit_and_render(ctx);
    }

    void finish() {
    
    }
};

int main() {
    UntitledGame game;
    build(game);
}