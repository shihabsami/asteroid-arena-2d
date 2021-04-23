#ifndef GAME_MATH_H
#define GAME_MATH_H

#include <math.h>
#include <vector>

#include "point2d.h"
#include "../main/config.h"

// this header contains definitions of static functions used all throughout

static double to_radians(const double& degrees)
{
    return (degrees * M_PI) / 180;
}

static double to_degrees(const double& radians)
{
    return radians * (180 / M_PI);
}

// generate double random numbers
static double get_random(double min, double max)
{
    return min + (rand() / (RAND_MAX / (max - min)));
}

// linear interpolation for double numbers
static double lerp(const double& start, const double& end, const double& t)
{
    return start + (end - start) * t;
}

// linear interpolation for color_t values
static color_t lerp(const color_t& start, const color_t& end, const double& t)
{
    return
        {
            lerp(start.r, end.r, t),
            lerp(start.g, end.g, t),
            lerp(start.b, end.b, t)
        };
}

// draw a debug circle
static void draw_circle(const double& radius, const int& segments)
{
    glBegin(GL_LINE_LOOP);

    double circle_angle = 0.0;
    for (int i = 0; i < segments; ++i)
    {
        circle_angle += 360.0 / segments;
        double circle_x = cos(to_radians(circle_angle)) * radius;
        double circle_y = sin(to_radians(circle_angle)) * radius;
        glVertex2d(circle_x, circle_y);
    }

    glEnd();
}

// get pre-calculated points for a circle of the provided radius and segments
static std::vector<point2d*> get_circle_points
    (const double& radius, const int& segments)
{
    std::vector<point2d*> points;

    double circle_angle = 0.0;
    for (int i = 0; i < segments; ++i)
    {
        double circle_x = cos(to_radians(circle_angle)) * radius;
        double circle_y = sin(to_radians(circle_angle)) * radius;
        points.push_back(new point2d(circle_x, circle_y));
        circle_angle += 360.0 / segments;
    }

    return points;
}

#endif // !GAME_MATH_H
