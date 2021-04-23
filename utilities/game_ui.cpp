#include "game_ui.h"
#include "../main/config.h"

game_ui::game_ui() {
    const char* st_text = "Press any key to start...";
    int st_char_count = calculate_chars(st_text);
    int st_width = calculate_width(st_text, st_char_count);
    vector2d st_position{ g::width / 2 - st_width / 2, g::height / 2 - UI_FONT_HEIGHT };
    texts[START] = new text_t(st_text, st_char_count, st_width, st_position);

    const char* score_text = "Score: ";
    int score_char_count = calculate_chars(score_text);
    int score_width = calculate_width(score_text, score_char_count);
    vector2d score_position{ 0.0, g::height - UI_FONT_HEIGHT };
    texts[SCORE] = new text_t(score_text, score_char_count, score_width, score_position);

    const char* time_text = "Time elapsed: ";
    int time_char_count = calculate_chars(time_text);
    int time_width = calculate_width(time_text, time_char_count);
    vector2d time_position{ g::width, g::height - UI_FONT_HEIGHT };
    texts[TIME] = new text_t(time_text, time_char_count, time_width, time_position);

    const char* go_text = "Game over! Press any key to play again...";
    int go_char_count = calculate_chars(go_text);
    int go_width = calculate_width(go_text, go_char_count);
    vector2d go_position{ g::width / 2 - go_width / 2, g::height / 2 - UI_FONT_HEIGHT };
    texts[GAME_OVER] = new text_t(go_text, go_char_count, go_width, go_position);

    score = 0;
    time = 0;
    game_started = nullptr;
    game_running = nullptr;
    game_over = nullptr;
}

void game_ui::update() {
    texts[START]->position = { g::width / 2 - texts[START]->width / 2, g::height / 2 - UI_FONT_HEIGHT };
    texts[SCORE]->position = { 0.0, g::height - UI_FONT_HEIGHT };
    texts[TIME]->position = { g::width, g::height - UI_FONT_HEIGHT };
    texts[GAME_OVER]->position = { g::width / 2 - texts[GAME_OVER]->width / 2, g::height / 2 - UI_FONT_HEIGHT };
}

int game_ui::calculate_chars(const char* text) {
    int c = 0;
    while (text[c] != '\0') ++c;
    return c;
}

int game_ui::calculate_width(const char* text, int char_count) {
    int w = 0;
    for (int i = 0; i < char_count; ++i) w += glutBitmapWidth(UI_FONT, text[i]);
    return w;
}

string game_ui::format_time() {
    int minutes = time / 60;
    int seconds = time % 60;
    return (to_string(minutes) + "m " + to_string(seconds) + "s");
}

void game_ui::draw() {
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, g::width, 0.0, g::height, ORTHO_Z_NEAR, ORTHO_Z_FAR);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    for (int i = 0; i < 4; ++i) {
        text_t* t = texts[i];
        string text_str;
        int char_count;
        int width;

        glColor3d(c::sky_blue.r, c::sky_blue.g, c::sky_blue.b);
        glRasterPos2d(t->position.x, t->position.y);

        switch (i) {
        case START:
            if (!*game_started)
                for (int j = 0; j < t->char_count; ++j)
                    glutBitmapCharacter(UI_FONT, t->text[j]);
            break;
        case SCORE:
            if (*game_running) {
                text_str = t->text + to_string(score);
                char_count = calculate_chars(text_str.c_str());
                for (int j = 0; j < char_count; ++j)
                    glutBitmapCharacter(UI_FONT, text_str[j]);
            }
            break;
        case TIME:
            if (*game_running) {
                text_str = t->text + format_time();
                char_count = calculate_chars(text_str.c_str());
                width = calculate_width(text_str.c_str(), char_count);
                glRasterPos2d(t->position.x - width, t->position.y);
                for (int j = 0; j < char_count; ++j)
                    glutBitmapCharacter(UI_FONT, text_str[j]);
            }
            break;
        case GAME_OVER:
            if (*game_over)
                for (int j = 0; j < t->char_count; ++j)
                    glutBitmapCharacter(UI_FONT, t->text[j]);
            break;
        default:
            break;
        }
    }

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
    error_check("game_ui::draw");
}
