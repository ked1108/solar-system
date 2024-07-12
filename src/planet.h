//
// Created by kedar on 7/7/2024.
//

#ifndef SOLAR_SYSTEM_PLANET_H
#define SOLAR_SYSTEM_PLANET_H

#include <memory>

#include "raylib.h"
#include "body.h"

class Planet : public Body {
    std::shared_ptr<Body> star;

public:
    Planet(std::string name, Vector3 pos, float radius, Color color, float mass, std::shared_ptr<Body> star);
};


#endif //SOLAR_SYSTEM_PLANET_H
