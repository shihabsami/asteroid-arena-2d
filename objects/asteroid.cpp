#include "asteroid.h"

asteroid::~asteroid() {
    for (int i = 0; i < points.size(); ++i) {
        point2d* p = points.at(i);
        points.erase(points.begin() + i);
        delete p;
    }
    points.clear();
}

void asteroid::init() {
    radius = scale.x / 2;
    hp = static_cast<int>(radius / ASTEROID_HP_MODIFIER) + 1;
    hit_count = 0;
    can_bounce = false;
    can_split = true;
    color = c::asteroid_fills[rand() % ASTEROID_COLOR_COUNT];

    // add some distortion to the perfect cirlce to get jagged asteroids
    points = get_circle_points(0.5, ASTEROID_SEGMENTS);
    for (point2d* p : points) {
        double distort = get_random(-0.1, 0.1);
        p->x += distort;
        p->y += distort;
    }
}

void asteroid::movement() {
    angle = fmod(angle + d_angle * g::d_time, 360.0);
    position = position + (direction * v * g::d_time);
}

void asteroid::draw() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    // transformations
    glTranslated(position.x, position.y, Z_MODEL_LAYER);
    glRotated(angle, 0.0, 0.0, Z_ROTATION);
    glScaled(scale.x, scale.y, Z_SCALE);

    // draw the fill polygon
    glColor3d(color.r, color.g, color.b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(0.0, 0.0);
    for (point2d* p : points) glVertex2d(p->x, p->y);
    glVertex2d(points.at(0)->x, points.at(0)->y);
    glEnd();

    // draw the outline
    glColor3d
        (c::asteroid_outline.r, c::asteroid_outline.g, c::asteroid_outline.b);
    glLineWidth(ASTEROID_LINE_WIDTH);
    glBegin(GL_LINE_LOOP);
    for (point2d* p : points) glVertex2d(p->x, p->y);
    glEnd();

    glPopMatrix();
    error_check("asteroid::draw");
}
