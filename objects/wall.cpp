#include "wall.h"

wall::wall(const point2d& start, const point2d& end, const color_t& color)
    : start(start), end(end), color(color) {}

void wall::draw() {
    glColor3d(color.r, color.g, color.b);
    glLineWidth(ARENA_WALL_WIDTH);
    glBegin(GL_LINES);
    glVertex2d(start.x, start.y);
    glVertex2d(end.x, end.y);
    glEnd();

    error_check("wall::draw");
}