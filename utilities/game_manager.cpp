#include "game_manager.h"

game_manager::game_manager() {
    start_time = 0.0;
    elapsed_time = 0.0;
    l_wave_time = 0.0;

    wave_number = 1;
    game_started = false;
    game_running = false;
    game_over = false;

    registry->ui = ui;
    ui->game_started = &game_started;
    ui->game_running = &game_running;
    ui->game_over = &game_over;
}

void game_manager::start_game() {
    registry->ui->score = 0;
    registry->ui->time = 0;
    wave_number = 1;

    start_time = g::c_time;
    l_wave_time = start_time;
    game_started = true;
    game_running = true;
    game_over = false;

    registry->delete_objects();
    registry->init_arena();
    registry->init_spaceship();
    registry->init_blackhole();
}

void game_manager::end_game() {
    game_running = false;
    game_over = true;

    registry->delete_arena();
    registry->delete_spaceship();
    registry->delete_blackhole();
}

void game_manager::display() {
    registry->ui->draw();
    c_handler->update();
    registry->draw_objects();

    if (game_running) {
        elapsed_time = g::c_time - start_time;
        registry->ui->time = static_cast<int>(elapsed_time / 1000);

        if (elapsed_time - l_wave_time >= WAVE_INTERVAL) {
            l_wave_time = elapsed_time;
            if (registry->asteroids.size() < MAX_ASTEROID_COUNT) {
                registry->generate_launch_positions(wave_number);
                for (int i = 0; i < wave_number; ++i) registry->add_asteroid();
                ++wave_number;
            }
        }
    }

    error_check("game_manager::display");
}
