#include "particle.h"
#include "../math/game_math.h"

particle::particle(
    const vector2d& position, const vector2d& direction, const double& size, const double& depth, const double& v,
    const double& t, const double& decay_rate, const color_t& start_color, const color_t& end_color)
    : position(position), direction(direction), size(size), depth(depth), v(v), t(t), decay_rate(decay_rate),
    start_color(start_color), end_color(end_color) {
    lerp_ascending = (round(t) == 0);
}

void particle::update() {
    if (lerp_ascending) {
        t += decay_rate;
        t = (t < 1.0) ? t : 1.0;
    } else {
        t -= decay_rate;
        t = (t > 0.0) ? t : 0.0;
    }
}

void particle::movement() {
    position = position + (direction * v * g::d_time);
}

void particle::draw() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    glTranslated(position.x, position.y, Z_PARTICLE_LAYER + depth);

    // these calculations are to make the size relative to the viewport size
    double min_dimension = (g::width < g::height) ? g::width : g::height;
    double min_units = (g::x_units < g::y_units) ? g::x_units : g::y_units;
    double relative_size = static_cast<GLfloat>(lerp(1.0, size, t)) * (min_dimension / min_units);
    color_t color = lerp(end_color, start_color, t);

    glPointSize(relative_size);
    glColor3d(color.r, color.g, color.b);
    glBegin(GL_POINTS);
    glVertex2d(0.0, 0.0);
    glEnd();

    glPopMatrix();
    error_check("particle::draw");
}
