//
// Created by kedar on 7/4/24.
//

#ifndef PLANET_H
#define PLANET_H

#include <array>
#include <vector>

#include "raylib.h"

#define AU (149.6e6 * 1000)
#define G 6.67428e-11
#define TIMESTEP (60 * 60 * 24 * 2)
#define SCALE (200 / AU)

#define ORBIT_LENGTH 100

class Planet {
    Vector3 pos;
    Vector3 vel;
    float radius;
    float mass;
    std::array<Vector3, ORBIT_LENGTH> orbit;

    Color color;
public:
    Planet(Vector3 pos, float radius, Color color, float mass);
    void update_pos(const std::vector<Planet>& planets);
    Vector3 calculate_forces(Planet& p2);
    Vector3 attraction(Planet& p2) const;

    Vector3 get_pos() const;
    float get_radius() const;
    Color get_color() const;
};



#endif //PLANET_H
