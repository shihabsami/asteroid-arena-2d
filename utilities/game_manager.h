#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "object_register.h"
#include "collision_handler.h"
#include "input_handler.h"

class game_manager {
public:
    game_manager();

    void start_game();

    void end_game();

    void display();

    object_register* registry = new object_register();
    collision_handler* c_handler = new collision_handler(this);
    input_handler* i_handler = new input_handler(this);
    game_ui* ui = new game_ui();

    double start_time;
    double elapsed_time;
    double l_wave_time;
    int wave_number;

    bool game_started;
    bool game_running;
    bool game_over;
};

#endif // !GAME_MANAGER_H
