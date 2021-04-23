#include <algorithm>
#include "collision_handler.h"
#include "game_manager.h"

collision_handler::collision_handler(game_manager* manager)
    : manager(manager), registry(manager->registry) {}

void collision_handler::update() {
    try {
        ship_against_wall();
        // ship_against_asteroid();
        asteroid_against_wall();
        bullet_against_wall();
        // objects_against_blackhole();
        bullet_against_asteroid();
        asteroid_against_asteroid();
    } catch(std::exception exception) {
        printf("%s", exception.what());
    }

    error_check("collision_handler::update");
}

void collision_handler::ship_against_wall() {
    if (!registry->ready()) return;
    spaceship* ship = registry->ship;
    game_arena* arena = registry->arena;

    // update arena wall color if spaceship is close
    arena->walls[UP]->color =
        ship->position.y + ship->radius + WALL_COLLISION_THRESHOLD >= g::arena_y_max ? c::red : c::white;
    arena->walls[DOWN]->color =
        ship->position.y - ship->radius - WALL_COLLISION_THRESHOLD <= g::arena_y_min ? c::red : c::white;
    arena->walls[LEFT]->color =
        ship->position.x - ship->radius - WALL_COLLISION_THRESHOLD <= g::arena_x_min ? c::red : c::white;
    arena->walls[RIGHT]->color =
        ship->position.x + ship->radius + WALL_COLLISION_THRESHOLD >= g::arena_x_max ? c::red : c::white;

    // end game if spaceship collides with arena
    if (ship->position.y + ship->radius >= g::arena_y_max || ship->position.y - ship->radius <= g::arena_y_min ||
        ship->position.x - ship->radius <= g::arena_x_min || ship->position.x + ship->radius >= g::arena_x_max)
        manager->end_game();
}

void collision_handler::ship_against_asteroid() {
    if (!registry->ready()) return;
    spaceship* ship = registry->ship;

    for (int i = 0; i < registry->asteroids.size(); ++i) {
        asteroid* a = registry->asteroids.at(i);
        double distance_sqr = ship->position.get_distance_squared(a->position);
        double sum_of_radius_sqr = (ship->radius + a->radius) * (ship->radius + a->radius);

        // end game if ship collides with an asteroid
        if (distance_sqr <= sum_of_radius_sqr) manager->end_game();
    }
}

void collision_handler::asteroid_against_wall() {
    if (!registry->ready()) return;

    for (int i = 0; i < registry->asteroids.size(); ++i) {
        asteroid* a = registry->asteroids.at(i);

        // only allow bouncing once asteroid is fully inside the arena
        if (a->position.y + a->radius < g::arena_y_max && a->position.y - a->radius > g::arena_y_min &&
            a->position.x - a->radius > g::arena_x_min && a->position.x + a->radius < g::arena_x_max)
            a->can_bounce = true;

        if (!a->can_bounce) continue;

        // if asteroid collides with the arena walls
        if (a->position.y + a->radius >= g::arena_y_max) {
            // move asteroid away to prevent multiple collisions
            vector2d normal{ 0.0, -1.0 };
            double move_distance = (a->position.y + a->radius) - g::arena_y_max;
            a->position = a->position + (normal * move_distance);
            a->direction = (a->direction + normal * 2).get_normalized();
        }
        if (a->position.y - a->radius <= g::arena_y_min) {
            vector2d normal{ 0.0, 1.0 };
            double move_distance = g::arena_y_min - (a->position.y - a->radius);
            a->position = a->position + (normal * move_distance);
            a->direction = (a->direction + normal * 2).get_normalized();
        }
        if (a->position.x - a->radius <= g::arena_x_min) {
            vector2d normal{ 1.0, 0.0 };
            double move_distance = g::arena_x_min - (a->position.x - a->radius);
            a->position = a->position + (normal * move_distance);
            a->direction = (a->direction + normal * 2).get_normalized();
        }
        if (a->position.x + a->radius >= g::arena_x_max) {
            vector2d normal{ -1.0, 0.0 };
            double move_distance = (a->position.x + a->radius) - g::arena_x_max;
            a->position = a->position + (normal * move_distance);
            a->direction = (a->direction + normal * 2).get_normalized();
        }
    }
}

void collision_handler::bullet_against_wall() {
    if (!registry->ready()) return;

    if (!registry->bullets.empty()) {
        for (int i = registry->bullets.size() - 1; i >= 0; --i) {
            bullet* b = registry->bullets.at(i);

            // if bullet collides with arena
            if (b->position.y + BULLET_SIZE >= g::arena_y_max || b->position.y - BULLET_SIZE <= g::arena_y_min ||
                b->position.x - BULLET_SIZE <= g::arena_x_min || b->position.x + BULLET_SIZE >= g::arena_x_max)
                registry->delete_bullet(i);
        }
    }
}

void collision_handler::bullet_against_asteroid() {
    if (!registry->bullets.empty() && !registry->asteroids.empty()) {
        for (int i = registry->bullets.size() - 1; i >= 0; --i) {
            bullet* b = registry->bullets.at(i);
            for (int j = registry->asteroids.size() - 1; j >= 0; --j) {
                asteroid* a = registry->asteroids.at(j);

                // if bullet collides with asteroid
                double distance_sqr = a->position.get_distance_squared(b->position);
                double radius_sqr = a->radius * a->radius;
                if (distance_sqr <= radius_sqr) {
                    registry->delete_bullet(i);

                    if (++a->hit_count == a->hp) {
                        if (a->can_split) registry->split_asteroid(j);
                        registry->delete_asteroid(j);
                        ++registry->ui->score;
                    }
                }
            }
        }
    }
}

void collision_handler::asteroid_against_asteroid() {
    if (!registry->asteroids.empty()) {
        for (int i = registry->asteroids.size() - 1; i >= 0; --i) {
            asteroid* a1 = registry->asteroids.at(i);
            if (registry->ready() && !a1->can_bounce) continue;

            for (int j = registry->asteroids.size() - 1; j >= 0; --j) {
                if (j == i) continue;

                asteroid* a2 = registry->asteroids.at(j);
                if (registry->ready() && !a2->can_bounce) continue;

                double distance_sqr = a1->position.get_distance_squared(a2->position);
                double sum_of_radius_sqr = (a1->radius + a2->radius) * (a1->radius + a2->radius);
                if (distance_sqr <= sum_of_radius_sqr) {
                    vector2d a1_normal = vector2d(a2->position - a1->position).get_normalized();
                    vector2d a2_normal = vector2d(a1->position - a2->position).get_normalized();

                    // move asteroids apart to prevent multiple collisions
                    double move_distance = sqrt(sum_of_radius_sqr) - sqrt(distance_sqr);
                    a1->position = a1->position - (a1_normal * move_distance / 2);
                    a2->position = a2->position - (a2_normal * move_distance / 2);

                    a1->direction = (a1->direction - a1_normal * 2).get_normalized();
                    a2->direction = (a2->direction - a2_normal * 2).get_normalized();
                }
            }
        }
    }
}

void collision_handler::objects_against_blackhole() {
    if (!registry->ready()) return;

    blackhole* bh = registry->bh;
    spaceship* ship = registry->ship;
    double distance_sqr = ship->position.get_distance_squared(bh->position);
    double sum_of_radius_sqr = (ship->radius + bh->radius) * (ship->radius + bh->radius);

    // end game if ship collides with an asteroid
    if (distance_sqr <= sum_of_radius_sqr) manager->end_game();
    else {
        // modify direction to create pull towards blackhole
        double distance = sqrt(distance_sqr);
        vector2d towards = (bh->position - ship->position).get_normalized();
        ship->position = ship->position + (towards / sqrt(distance) * BLACKHOLE_PULL_MODIFIER * g::d_time);
        ship->direction = (ship->direction + (towards / distance / 2)).get_normalized();
        ship->angle = ship->direction.get_angle();
    }

    for (int i = 0; i < registry->bullets.size(); ++i) {
        bullet* b = registry->bullets.at(i);

        // if bullet collides with blackhole
        if (b->position.y + BULLET_SIZE >= bh->position.y - bh->radius &&
            b->position.y - BULLET_SIZE <= bh->position.y + bh->radius &&
            b->position.x - BULLET_SIZE <= bh->position.x + bh->radius &&
            b->position.x + BULLET_SIZE >= bh->position.x - bh->radius) {
            registry->bullets.erase(registry->bullets.begin() + i);
            delete b;
        } else {
            // modify direction to create pull towards blackhole
            double distance = bh->position.get_distance(b->position);
            vector2d towards = (bh->position - b->position).get_normalized();
            b->direction = (b->direction + (towards / distance / 2)).get_normalized();
        }
    }

    for (int i = 0; i < registry->asteroids.size(); ++i) {
        asteroid* a = registry->asteroids.at(i);

        // if asteroid collides with blackhole
        if (a->position.y + a->radius >= bh->position.y - bh->radius &&
            a->position.y - a->radius <= bh->position.y + bh->radius &&
            a->position.x - a->radius <= bh->position.x + bh->radius &&
            a->position.x + a->radius >= bh->position.x - bh->radius)
            registry->delete_asteroid(i);
        else {
            // modify direction to create pull towards blackhole
            double distance = bh->position.get_distance(a->position);
            vector2d towards = (bh->position - a->position).get_normalized();
            a->direction = (a->direction + (towards / distance / 2)).get_normalized();
        }
    }
}
