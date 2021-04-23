#ifndef VECTOR_2D_H
#define VECTOR_2D_H

class vector2d
{
public:
    vector2d();

    vector2d(const double& x, const double& y);

    vector2d get_normalized();

    double get_distance(const vector2d& v);

    double get_distance_squared(const vector2d& v);

    double get_angle();

    vector2d operator+(const vector2d& v);

    vector2d operator-(const vector2d& v);

    vector2d operator*(const double& d);

    vector2d operator/(const double& d);

    double x;
    double y;
    double m;
};

#endif // !VECTOR_2D_H
