#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include <vector>

class game_manager;

class object_register;

class collision_handler {
public:
    collision_handler(game_manager* manager);

    void update();

    void ship_against_wall();

    void ship_against_asteroid();

    void bullet_against_wall();

    void bullet_against_asteroid();

    void asteroid_against_wall();

    void asteroid_against_asteroid();

    void objects_against_blackhole();

    game_manager* manager;
    object_register* registry;
};

#endif // !COLLISION_HANDLER_H
