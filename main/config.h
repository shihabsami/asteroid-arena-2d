#ifndef CONFIG_H
#define CONFIG_H

#if _WIN32
    #include <windows.h>
#endif

#if __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glut.h>
#endif

#include <iostream>
#include <ctime>

// initial configurations
#define GAME_TITLE      "Asteroid Arena"
#define INIT_WIDTH      1280
#define INIT_HEIGHT     720
#define IS_FULLSCREEN   true

// constants used in transformations
#define ORIGIN_X       0
#define ORIGIN_Y       0
#define Z_ROTATION     1.0
#define Z_SCALE        1.0
#define ORTHO_Z_NEAR  -1.0
#define ORTHO_Z_FAR    1.0

// the layers since depth buffer is enabled
#define Z_MODEL_LAYER      0.0
#define Z_PARTICLE_LAYER   0.5
#define Z_MISC_LAYER      -0.5

/*
 * the total number of units in one axis when aspect ratio is 1.0
 * spans from (-ve) to (+ve) with 0.0, 0.0 as center
 */
#define TOTAL_UNITS   1000
#define MAX_ANGLE   360

/*
 * arena width should ideally be within TOTAL_UNITS else it shall exceed
 * the coordinate system's maximum size and shall not be fully visible
 */
#define ARENA_WIDTH                800
#define ARENA_HEIGHT               800
#define ARENA_WALL_WIDTH           4.0
#define WALL_COLLISION_THRESHOLD   100

// spaceship configurations
#define SPACESHIP_WIDTH            30
#define SPACESHIP_HEIGHT           30
#define SPACESHIP_VELOCITY         300.0
#define SPACESHIP_ROTATION_SPEED   180.0
#define SPACESHIP_LINE_WIDTH       1.0
#define SPACESHIP_SPEED_UP_RATE    0.01

// asteroid configurations
#define ASTEROID_MIN_RADIUS     15
#define ASTEROID_MAX_RADIUS     20
#define ASTEROID_MIN_VELOCITY   50
#define ASTEROID_MAX_VELOCITY   100
#define ASTEROID_MIN_ROTATION   10
#define ASTEROID_MAX_ROTATION   30
#define ASTEROID_LINE_WIDTH     3.0
#define ASTEROID_SEGMENTS       20
#define ASTEROID_COLOR_COUNT    5
#define ASTEROID_HP_MODIFIER    5

// blackhole configurations
#define BLACKHOLE_MIN_SIZE        25
#define BLACKHOLE_MAX_SIZE        100
#define BLACKHOLE_SEGMENTS        20
#define BLACKHOLE_PULL_MODIFIER   300
#define BLACKHOLE_INTERVAL        5000
#define BLACKHOLE_PULSE_RATE      0.005

// time between waves and the maximum number of asteroids in the arena
#define WAVE_INTERVAL        1000.0
#define MAX_ASTEROID_COUNT   20

// bullet point size and time between each shot
#define BULLET_SIZE       1.0
#define FIRING_INTERVAL   100

// particle system configurations
#define EXHAUST_PARTICLE_SIZE           10
#define EXHAUST_PARTICLE_DECAY_RATE     0.25
#define EXHAUST_PARTICLE_INTERVAL       10

#define EXPLOSION_PARTICLE_SIZE         15
#define EXPLOSION_PARTICLE_DECAY_RATE   0.01
#define EXPLOSION_PARTICLE_COUNT        30

#define BULLET_PARTICLE_SIZE            10
#define BULLET_PARTICLE_DECAY_RATE      0.05
#define BULLET_PARTICLE_COUNT           5

#define BLACKHOLE_PARTICLE_SIZE         1.0
#define BLACKHOLE_PARTICLE_DECAY_RATE   0.005
#define BLACKHOLE_PARTICLE_INTERVAL     50
#define BLACKHOLE_PARTICLE_PULL         100

#define STAR_PARTICLE_COUNT             250
#define STAR_PARTICLE_SIZE              1.0
#define STAR_PARTICLE_DECAY_RATE        0.05

// ui configurations
#define UI_FONT          GLUT_BITMAP_HELVETICA_18
#define UI_FONT_HEIGHT   18

// global namespace containing all global variables used
namespace g
{
    extern double width;
    extern double height;
    extern double x_units;
    extern double y_units;
    extern double d_time;
    extern double c_time;
    extern double arena_x_min;
    extern double arena_x_max;
    extern double arena_y_min;
    extern double arena_y_max;
}

struct color_t
{
    GLdouble r, g, b;
};

// color namespace, containing all the colors used
namespace c
{
    extern color_t white;
    extern color_t black;
    extern color_t gray;
    extern color_t red;
    extern color_t sky_blue;

    extern color_t arena_fill;
    extern color_t arena_wall;
    extern color_t spaceship_outline;
    extern color_t spaceship_fill;
    extern color_t asteroid_fills[ASTEROID_COLOR_COUNT];
    extern color_t asteroid_outline;
    extern color_t bullet_fill;
    extern color_t blackhole_fill;

    extern color_t exhaust_start;
    extern color_t exhaust_end;
    extern color_t explosion_start;
    extern color_t explosion_end;
    extern color_t bullet_particle_start;
    extern color_t bullet_particle_end;
}

// function to check errors
extern void error_check(const char* location);

#endif // !CONFIG_H
