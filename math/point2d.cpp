#include "point2d.h"

#include <math.h>

point2d::point2d()
    : x(), y()
{}

point2d::point2d(const double& x, const double& y)
    : x(x), y(y)
{}

double point2d::get_distance(const point2d& p)
{
    // distance between two points
    return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
}
