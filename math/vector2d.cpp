#include "vector2d.h"

#include <math.h>

vector2d::vector2d()
    : x(), y(), m()
{}

vector2d::vector2d(const double& x, const double& y) : x(x), y(y)
{
    m = sqrt(x * x + y * y);
}

// normalize the vector (magnitude of 1)
vector2d vector2d::get_normalized()
{
    return { x / m, y / m };
}

// the angle of the vector
double vector2d::get_angle()
{
    return atan2(y, x) * (180 / M_PI);
}

// distance between two vectors
double vector2d::get_distance(const vector2d& v)
{
    return sqrt((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y));
}

// removes the use of the expensive sqrt() function
double vector2d::get_distance_squared(const vector2d& v)
{
    return ((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y));
}

// operator overloads to do scalar operations
vector2d vector2d::operator+(const vector2d& v)
{
    return { x + v.x, y + v.y };
}

vector2d vector2d::operator-(const vector2d& v)
{
    return { x - v.x, y - v.y };
}

vector2d vector2d::operator*(const double& d)
{
    return { x * d, y * d };
}

vector2d vector2d::operator/(const double& d)
{
    return { x / d, y / d };
}
