#ifndef BULLET_H
#define BULLET_H

#include "particle.h"

class bullet : public particle {
public:
    using particle::particle;

    void update() override {};
};

#endif // !BULLET_H
