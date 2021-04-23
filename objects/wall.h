#ifndef WALL_H
#define WALL_H

#include "../math/point2d.h"
#include "../main/config.h"

class wall {
public:
    wall(const point2d& start, const point2d& end, const color_t& color);

    void draw();

    point2d start;
    point2d end;
    color_t color;
};

#endif // !WALL_H
