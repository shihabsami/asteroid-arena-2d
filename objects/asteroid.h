#ifndef ASTEROID_H
#define ASTEROID_H

#include <vector>

#include "game_object.h"
#include "../math/game_math.h"

class asteroid : public game_object {
public:
    using game_object::game_object;

    ~asteroid();

    void init() override;

    void movement() override;

    void draw() override;

    int hp;
    int hit_count;
    bool can_bounce;
    bool can_split;
    color_t color;
    std::vector<point2d*> points;
};

#endif // !ASTEROID_H
