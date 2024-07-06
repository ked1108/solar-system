//
// Created by kedar on 7/7/2024.
//

#include <memory>
#include "raylib.h"
#include "planet.h"

Planet::Planet(std::string name, Vector3 pos, float radius, Color color, float mass, std::shared_ptr<Body> star) : Body(name, pos, radius, color, mass) {
    this->star = std::move(star);
}
