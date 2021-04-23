#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

namespace i {
    extern bool mouse_down;
    extern bool key_states[4];
}

enum key {
    W, A, D, ANY
};

class game_manager;

class input_handler {
public:
    input_handler(game_manager* manager);

    void on_mouseclick(int button, int state, __attribute__((unused)) int x, __attribute__((unused)) int y);

    void on_keydown(unsigned char key, __attribute__((unused)) int x, __attribute__((unused)) int y);

    void on_keyup(unsigned char key, __attribute__((unused)) int x, __attribute__((unused)) int y);

    game_manager* manager;
};

#endif // !INPUT_HANDLER_H
