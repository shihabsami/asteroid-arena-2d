#ifndef GAME_ARENA_H
#define GAME_ARENA_H

#include "wall.h"

enum wall_orientation {
    UP, DOWN, LEFT, RIGHT
};

class game_arena {
public:
    game_arena(const double& width, const double& height);

    ~game_arena();

    void init_walls();

    void draw();

    wall* walls[4];
};

#endif // !GAME_ARENA_H
