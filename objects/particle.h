#ifndef PARTICLE_H
#define PARTICLE_H

#include "../main/config.h"
#include "../math/vector2d.h"

class particle {
public:
    particle(
        const vector2d& position, const vector2d& direction, const double& size,
        const double& depth, const double& v, const double& t,
        const double& decay_rate, const color_t& start_color,
        const color_t& end_color);

    virtual void update();

    virtual void movement();

    virtual void draw();

    vector2d position;
    vector2d direction;
    double size;
    double depth;
    double v;
    double t;
    double decay_rate;
    bool lerp_ascending;
    color_t start_color;
    color_t end_color;
};

#endif // !PARTICLE_H
