#ifndef GAME_UI_H
#define GAME_UI_H

#include <string>

#include "../math/vector2d.h"

using std::string;
using std::to_string;

struct text_t {
    text_t()
        : text(), char_count(), width(), position() {}

    text_t(const char* text, int char_count, int width, vector2d position)
        : text(text), char_count(char_count), width(width), position(position) {}

    const char* text;
    int char_count;
    int width;
    vector2d position;
};

enum text_label {
    START, SCORE, TIME, GAME_OVER
};

class game_ui {
public:
    game_ui();

    void draw();

    void update();

    int calculate_chars(const char* text);

    int calculate_width(const char* text, int char_count);

    string format_time();

    int score;
    int time;
    text_t* texts[4];

    bool* game_started;
    bool* game_running;
    bool* game_over;
};

#endif // !GAME_UI_H
