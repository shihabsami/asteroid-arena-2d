#include "config.h"

// this file only contains definition of global variables
double g::width;
double g::height;
double g::x_units;
double g::y_units;
double g::d_time;
double g::c_time;
double g::arena_x_min;
double g::arena_x_max;
double g::arena_y_min;
double g::arena_y_max;

color_t c::white{ 1.0, 1.0, 1.0 };
color_t c::black{ 0.0, 0.0, 0.0 };
color_t c::gray{ 0.25, 0.25, 0.25 };
color_t c::sky_blue{ 0.0, 0.5, 1.0 };
color_t c::red{ 1.0, 0.0, 0.0 };

color_t c::arena_fill{ c::black };
color_t c::arena_wall{ 0.76, 0.99, 1.0 };
color_t c::spaceship_outline{ 0.14, 0.22, 0.35 };
color_t c::spaceship_fill{ c::sky_blue };
color_t c::asteroid_fills[]{
    { 0.93, 0.94, 0.95 },
    { 0.72, 0.73, 0.71 },
    { 0.66, 0.6, 0.62 },
    { 0.61, 0.5, 0.51 },
    { 0.41, 0.46, 0.47 }};
color_t c::asteroid_outline{ 0.22, 0.24, 0.25 };
color_t c::bullet_fill{ 0.8, 0.3, 0.3 };
color_t c::blackhole_fill{ c::black };

color_t c::exhaust_start{ 0.04, 0.82, 1.0 };
color_t c::exhaust_end{ 0.9, 0.05, 0.2 };
color_t c::explosion_start{ 0.8, 0.0, 0.0 };
color_t c::explosion_end{ 1.0, 1.0, 0.5 };
color_t c::bullet_particle_start{ 1.0, 0.3, 0.3 };
color_t c::bullet_particle_end{ 0.8, 0.8, 0.8 };

// checks errors with the help of opengl functions
void error_check(const char* location) {
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
        printf("%s: %s\n", location, gluErrorString(error));
}
