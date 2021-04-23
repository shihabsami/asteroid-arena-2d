#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include <vector>

#include "../math/point2d.h"
#include "../math/vector2d.h"

class blackhole {
public:
    blackhole(const vector2d& position);

    ~blackhole();

    void update();

    void draw();

    vector2d position;
    double size;
    double radius;
    double t;
    bool lerp_ascending;
    double l_pulse_time;
    std::vector<point2d*> points;
};

#endif // !BLACKHOLE_H
