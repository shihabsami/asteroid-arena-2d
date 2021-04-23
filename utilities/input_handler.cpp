#include "input_handler.h"
#include "game_manager.h"

bool i::mouse_down = false;
bool i::key_states[]{ false };

input_handler::input_handler(game_manager* manager)
    : manager(manager) {}

void input_handler::on_mouseclick(int button, int state, __attribute__((unused)) int x, __attribute__((unused)) int y) {
    i::mouse_down = (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN);
}

void input_handler::on_keydown(unsigned char key, __attribute__((unused)) int x, __attribute__((unused)) int y) {
    if (key == 27) exit(EXIT_SUCCESS);
    i::key_states[ANY] = true;
    if (!manager->game_running && i::key_states[ANY]) manager->start_game();
    if (!manager->game_running) return;

    switch (key) {
    case 'w':
    case 'W':
        i::key_states[W] = true;
        break;
    case 'a':
    case 'A':
        i::key_states[A] = true;
        break;
    case 'd':
    case 'D':
        i::key_states[D] = true;
        break;
    default:
        break;
    }
}

void input_handler::on_keyup(unsigned char key, __attribute__((unused)) int x, __attribute__((unused)) int y) {
    i::key_states[ANY] = false;
    switch (key) {
    case 'w':
    case 'W':
        i::key_states[W] = false;
        break;
    case 'a':
    case 'A':
        i::key_states[A] = false;
        break;
    case 'd':
    case 'D':
        i::key_states[D] = false;
        break;
    default:
        break;
    }
}
