#include "spaceship.h"
#include "../utilities/input_handler.h"
#include "../math/game_math.h"

void spaceship::init() {
    radius = scale.x / 2;
    t = 0.0;
    is_moving = false;
}

void spaceship::movement() {
    /*
     * gradual speed up/down using linear interpolation
     * for well balanced gameplay, slows down twice as fast as speeding up
     * and speeds up at half the usual rate when steering
     */
    if (i::key_states[W]) {
        t = (t < 1.0)
            ? t + ((i::key_states[A] || i::key_states[D])
                ? SPACESHIP_SPEED_UP_RATE / 2
                : SPACESHIP_SPEED_UP_RATE)
            : 1.0;
    } else t = (t > 0.0) ? (t - SPACESHIP_SPEED_UP_RATE * 2) : 0.0;

    // steering
    if (i::key_states[A]) angle = fmod(angle + d_angle * g::d_time, 360.0);
    if (i::key_states[D]) angle = fmod(angle - d_angle * g::d_time, 360.0);

    double current_v = lerp(0.0, v, t);
    position = position + (direction * current_v * g::d_time);
    direction = { cos(to_radians(angle)), sin(to_radians(angle)) };
    is_moving = current_v != 0.0 || i::key_states[A] || i::key_states[D];
}

void spaceship::draw() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    // transformations
    glTranslated(position.x, position.y, Z_MODEL_LAYER);
    glRotated(angle, 0.0, 0.0, Z_ROTATION);
    glScaled(scale.x, scale.y, Z_SCALE);

    // draw the outline
    glColor3d(
        c::spaceship_outline.r,
        c::spaceship_outline.g,
        c::spaceship_outline.b);
    glLineWidth(SPACESHIP_LINE_WIDTH);
    glBegin(GL_LINE_LOOP);
    glVertex2d(ORIGIN_X + 0.5, ORIGIN_Y);
    glVertex2d(ORIGIN_X - 0.5, ORIGIN_Y - 0.4);
    glVertex2d(ORIGIN_X - 0.3, ORIGIN_Y);
    glVertex2d(ORIGIN_X - 0.5, ORIGIN_Y + 0.4);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(ORIGIN_X + 0.5, ORIGIN_Y);
    glVertex2d(ORIGIN_X - 0.3, ORIGIN_Y);
    glEnd();

    // draw the fill polygon
    glColor3d(
        c::spaceship_fill.r,
        c::spaceship_fill.g,
        c::spaceship_fill.b);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2d(ORIGIN_X - 0.5, ORIGIN_Y - 0.4);
    glVertex2d(ORIGIN_X + 0.5, ORIGIN_Y);
    glVertex2d(ORIGIN_X - 0.3, ORIGIN_Y);
    glVertex2d(ORIGIN_X - 0.5, ORIGIN_Y + 0.4);
    glEnd();

    glPopMatrix();
    error_check("spaceship::draw");
}
