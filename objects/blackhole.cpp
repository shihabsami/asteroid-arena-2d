#include "blackhole.h"
#include "../main/config.h"
#include "../math/game_math.h"

blackhole::blackhole(const vector2d& position)
    : position(position), size(BLACKHOLE_MAX_SIZE), t(1.0), l_pulse_time(0.0) {
    radius = size / 2;
    lerp_ascending = false;
    points = get_circle_points(0.5, BLACKHOLE_SEGMENTS);
}

blackhole::~blackhole() {
    for (int i = 0; i < points.size(); ++i) {
        point2d* p = points.at(i);
        points.erase(points.begin() + i);
        delete p;
    }
    points.clear();
}

void blackhole::update() {
    // pulse mechanism
    if (lerp_ascending) {
        t += BLACKHOLE_PULSE_RATE;
        t = (t < 1.0) ? t : 1.0;
    } else {
        t -= BLACKHOLE_PULSE_RATE * 4;
        t = (t > 0.0) ? t : 0.0;
        if (t == 0.0) lerp_ascending = true;
    }

    if (g::c_time - l_pulse_time >= BLACKHOLE_INTERVAL) {
        lerp_ascending = false;
        l_pulse_time = g::c_time;
    }

    // update size and radius
    size = lerp(BLACKHOLE_MIN_SIZE, BLACKHOLE_MAX_SIZE, t);
    radius = size / 2;
}

void blackhole::draw() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    glTranslated(position.x, position.y, Z_MISC_LAYER);
    glScaled(size, size, Z_SCALE);

    // draw the fill polygon
    glColor3d (c::blackhole_fill.r, c::blackhole_fill.g, c::blackhole_fill.b);
    glBegin(GL_POLYGON);
    for (point2d* p : points) glVertex3d(p->x, p->y, 0.0);
    glEnd();

    glPopMatrix();
    error_check("blackhole::draw");
}
