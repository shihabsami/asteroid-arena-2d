#include "game_object.h"

game_object::game_object()
    : position(), direction(), scale(), v(), angle(), d_angle(), radius() {}

game_object::game_object(const vector2d& position, const vector2d& direction,
    const vector2d& scale,
    const double& v, const double& angle, const double& d_angle)
    : position(position), direction(direction), scale(scale), v(v),
    angle(angle), d_angle(d_angle), radius() {}
