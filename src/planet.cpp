//
// Created by kedar on 7/4/24.
//

#include "planet.h"

#include "raymath.h"

Planet::Planet(Vector3 pos, float radius, Color color, float mass) {
    this->pos = pos;
    this->vel = {0.0f, 0.0f};

    this->radius = radius;
    this->color = color;

    this->mass = mass;
}

Vector3 Planet::attraction(Planet &p2) {
    float distance_sqr = Vector3DistanceSqr(this->pos, p2.pos);
    if(distance_sqr == 0) return (Vector3){0.0f, 0.0f, 0.0f};

    Vector3 force;

    float force_mag = G * this->mass * p2.mass / distance_sqr;
    float theta = atan2f(p2.pos.y = this->pos.y, p2.pos.x - this->pos.x);
    float phi = atan2f(p2.pos.y = this->pos.y, p2.pos.z - this->pos.z);

    force.x = cos(theta)*force_mag;
    force.y = sin(theta)*force_mag;
    force.z = cos(phi)*force_mag;

    return force;
}

void Planet::update_pos(const std::vector<Planet>& planets) {
    static int pos = 0;
    Vector3 total = {0.0f, 0.0f, 0.0f};
    for(Planet p: planets) {
        Vector3Add(total, this->attraction(p));
    }
    this->vel.x = total.x / this->mass * TIMESTEP;
    this->vel.y = total.y / this->mass * TIMESTEP;
    this->vel.z = total.z / this->mass * TIMESTEP;

    this->pos.x = this->vel.x*TIMESTEP;
    this->pos.y = this->vel.y*TIMESTEP;
    this->pos.z = this->vel.z*TIMESTEP;

    this->orbit[pos++ % ORBIT_LENGTH] = this->pos;
}


