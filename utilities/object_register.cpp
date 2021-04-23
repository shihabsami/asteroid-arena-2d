#include "object_register.h"
#include "input_handler.h"

object_register::object_register()
{
    // initialise objects as empty
    ui = nullptr;
    arena = nullptr;
    ship = nullptr;
    bh = nullptr;
    ps = new particle_system(this);
    l_fire_time = 0.0;
}

void object_register::init_arena()
{
    this->arena = new game_arena(ARENA_WIDTH, ARENA_HEIGHT);
}

void object_register::delete_arena()
{
    delete arena;
    arena = nullptr;
}

void object_register::init_spaceship()
{
    // spaceship is positioned at the corner of the arena
    vector2d position{
        g::arena_x_min + 2 * SPACESHIP_WIDTH,
        g::arena_y_min + 2 * SPACESHIP_HEIGHT };

    // facing the top right corner
    vector2d direction = vector2d(
        g::arena_x_max - position.x,
        g::arena_y_max - position.y).get_normalized();

    vector2d scale{ SPACESHIP_WIDTH, SPACESHIP_HEIGHT };
    spaceship* s = new spaceship(position, direction, scale,
        SPACESHIP_VELOCITY, direction.get_angle(), SPACESHIP_ROTATION_SPEED);

    s->init();
    this->ship = s;
}

void object_register::delete_spaceship()
{
    delete ship;
    ship = nullptr;
}

void object_register::init_blackhole()
{
    // line equation to spawn the blackhole randomly on a line
    double r = get_random(0.0, 1.0);
    double x1 = g::arena_x_min + 2 * BLACKHOLE_MAX_SIZE;
    double y1 = g::arena_y_max - 2 * BLACKHOLE_MAX_SIZE;
    double x2 = g::arena_x_max - 2 * BLACKHOLE_MAX_SIZE;
    double y2 = g::arena_y_min + 2 * BLACKHOLE_MAX_SIZE;
    double slope = (y2 - y1) / (x2 - x1);
    double x = (x2 - x1) * r + x1;
    double y = (x - x1) * slope + y1;

    this->bh = new blackhole({ x, y });
}

void object_register::delete_blackhole()
{
    delete bh;
    bh = nullptr;
}

void object_register::add_asteroid()
{
    // position on the launchpad and coming towards the spaceship
    vector2d position = next_launch_position();
    vector2d direction = (ship->position - position).get_normalized();
    double radius = get_random(ASTEROID_MIN_RADIUS, ASTEROID_MAX_RADIUS);
    vector2d scale{ radius * 2, radius * 2 };

    // random velocity, starting angle
    double v = get_random(ASTEROID_MIN_VELOCITY, ASTEROID_MAX_VELOCITY);
    double angle = get_random(0.0, MAX_ANGLE);

    // randomly chosen delta angle and rotation direction
    double d_angle = get_random
        (
            -(ASTEROID_MAX_ROTATION - ASTEROID_MIN_ROTATION),
            (ASTEROID_MAX_ROTATION - ASTEROID_MIN_ROTATION)
        );
    d_angle += d_angle > 0 ? ASTEROID_MIN_ROTATION : -ASTEROID_MIN_ROTATION;
    asteroid* a = new asteroid(position, direction, scale, v, angle, d_angle);

    a->init();
    asteroids.push_back(a);
}

void object_register::split_asteroid(int i)
{
    asteroid* a = asteroids.at(i);

    // split asteroids shall have base asteroid direction +-45 degrees
    double radius = a->radius / 2;
    vector2d a1_tangent{ -a->direction.y, a->direction.x };
    vector2d a2_tangent{ a->direction.y, -a->direction.x };
    vector2d a1_position = a->position + (a1_tangent * radius);
    vector2d a2_position = a->position + (a2_tangent * radius);
    vector2d a1_direction = (a->direction + a1_tangent).get_normalized();
    vector2d a2_direction = (a->direction + a2_tangent).get_normalized();
    vector2d scale{ radius * 2, radius * 2 };

    // random velocity, starting angle and delta angle
    double v = get_random(ASTEROID_MIN_VELOCITY, ASTEROID_MAX_VELOCITY);
    double angle = get_random(0.0, MAX_ANGLE);
    double d_angle = get_random
        (
            -(ASTEROID_MAX_ROTATION - ASTEROID_MIN_ROTATION),
            (ASTEROID_MAX_ROTATION - ASTEROID_MIN_ROTATION)
        );
    d_angle += d_angle > 0 ? ASTEROID_MIN_ROTATION : -ASTEROID_MIN_ROTATION;

    asteroid* a1 = new asteroid(a1_position, a1_direction, scale, v,
        angle, d_angle);
    asteroid* a2 = new asteroid(a2_position, a2_direction, scale, v,
        angle, d_angle);

    a1->init();
    a2->init();
    a1->can_split = false;
    a2->can_split = false;
    asteroids.push_back(a1);
    asteroids.push_back(a2);
}

void object_register::delete_asteroid(int i)
{
    asteroid* a = asteroids.at(i);
    ps->init_explosion_particles(a);
    asteroids.erase(asteroids.begin() + i);
    delete a;
}

void object_register::add_bullet()
{
    vector2d position = ship->position + (ship->direction * ship->radius);
    bullets.push_back(new bullet(
        position, ship->direction, BULLET_SIZE, -0.1, ship->v * 1.5f, 1.0,
        0.0, c::bullet_fill, c::bullet_fill));
}

void object_register::delete_bullet(int i)
{
    bullet* b = bullets.at(i);
    ps->init_bullet_particles(b);
    bullets.erase(bullets.begin() + i);
    delete b;
}

vector2d object_register::next_launch_position()
{
    vector2d position = launch_positions.at(launch_positions.size() - 1);
    launch_positions.pop_back();
    return position;
}

void object_register::generate_launch_positions(int n)
{
    launch_positions.clear();

    double start_angle = get_random(0.0, 360.0);
    double diagonal_length = sqrt(
        g::x_units / 2 * g::x_units / 2 + g::y_units / 2 * g::y_units / 2);
    double launchpad_radius = diagonal_length / 2 + 2 * ASTEROID_MAX_RADIUS;

    for (int i = 0; i < n; ++i)
    {
        launch_positions.push_back
            (
                {
                    cos(to_radians(start_angle)) * launchpad_radius,
                    sin(to_radians(start_angle)) * launchpad_radius
                }
            );
        start_angle = fmod(start_angle + 360.0f / n, 360);
    }
}

void object_register::draw_objects()
{
    ps->update();

    if (ready())
    {
        arena->draw();
        ship->movement();
        ship->draw();
        bh->update();
        bh->draw();
        ps->draw();

        if ((g::c_time - l_fire_time >= FIRING_INTERVAL) && i::mouse_down)
        {
            add_bullet();
            l_fire_time = g::c_time;
        }
    }

    for (bullet* b : bullets)
    {
        b->movement();
        b->draw();
    }

    for (asteroid* a : asteroids)
    {
        a->movement();
        a->draw();
    }

    error_check("object_register::draw_objects");
}

bool object_register::ready()
{
    return (arena != nullptr && ship != nullptr && bh != nullptr);
}

void object_register::delete_objects()
{
    for (int i = 0; i < asteroids.size(); ++i) delete_asteroid(i);
    for (int i = 0; i < bullets.size(); ++i) delete_bullet(i);

    asteroids.clear();
    bullets.clear();
    ps->clear();
}
