#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../math/vector2d.h"

/*
 * an abstract class for game objects to inherit from
 * methods except the constructors are made pure virtual
 * to ensure they are defined by the subclasses
 */

class game_object {
public:
    // construct game object with default parameters
    game_object();

    // construct game object with specified parameters
    game_object(
        const vector2d& position, const vector2d& direction,
        const vector2d& scale, const double& v,
        const double& angle, const double& d_angle);

    // initialise the game object
    virtual void init() = 0;

    // calculate the current position/direction of the game object
    virtual void movement() = 0;

    // draw the game object
    virtual void draw() = 0;

    // position of the game object
    vector2d position;

    // direction of the game object as an unit vector
    vector2d direction;

    // scale of the game object
    vector2d scale;

    // velocity of the game object in world coordinates
    double v;

    // angle of the game object in degrees
    double angle;

    // delta angle of the game object, for rotation/movement
    double d_angle;

    // the radius that encircles the game object
    double radius;
};

#endif // !GAME_OBJECT_H
