#include "game_arena.h"

game_arena::game_arena(const double& width, const double& height) {
    g::arena_x_min = -width / 2;
    g::arena_y_min = -height / 2;
    g::arena_x_max = width / 2;
    g::arena_y_max = height / 2;

    init_walls();
}

game_arena::~game_arena() {
    for (int i = 0; i < 4; ++i) delete walls[i];
}

void game_arena::init_walls() {
    walls[UP] = new wall
        (
            { g::arena_x_min, g::arena_y_max },
            { g::arena_x_max, g::arena_y_max }, c::arena_wall
        );
    walls[DOWN] = new wall
        (
            { g::arena_x_min, g::arena_y_min },
            { g::arena_x_max, g::arena_y_min }, c::arena_wall
        );
    walls[LEFT] = new wall
        (
            { g::arena_x_min, g::arena_y_min },
            { g::arena_x_min, g::arena_y_max }, c::arena_wall
        );
    walls[RIGHT] = new wall
        (
            { g::arena_x_max, g::arena_y_min },
            { g::arena_x_max, g::arena_y_max }, c::arena_wall
        );
}

void game_arena::draw() {
    for (wall* w : walls) w->draw();
    error_check("game_arena::draw");
}
