#ifndef OBJECT_REGISTER_H
#define OBJECT_REGISTER_H

#include <vector>

#include "../math/game_math.h"
#include "../objects/game_object.h"
#include "../objects/game_arena.h"
#include "../objects/spaceship.h"
#include "../objects/blackhole.h"
#include "../objects/asteroid.h"
#include "../objects/bullet.h"
#include "particle_system.h"
#include "game_ui.h"

class object_register {
public:
    object_register();

    bool ready();

    void init_arena();

    void delete_arena();

    void init_spaceship();

    void delete_spaceship();

    void init_blackhole();

    void delete_blackhole();

    void add_asteroid();

    void split_asteroid(int i);

    void delete_asteroid(int i);

    void add_bullet();

    void delete_bullet(int i);

    vector2d next_launch_position();

    void generate_launch_positions(int n);

    void draw_objects();

    void delete_objects();

    game_ui* ui;
    game_arena* arena;
    spaceship* ship;
    blackhole* bh;
    std::vector<asteroid*> asteroids;
    std::vector<bullet*> bullets;
    std::vector<vector2d> launch_positions;
    particle_system* ps;
    double l_fire_time;
};

#endif // !OBJECT_REGISTER_H
