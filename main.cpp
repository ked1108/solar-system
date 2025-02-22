#include "raylib.h"
#include "body.h"
#include "planet.h"

#include <json/json.h>
#include <fstream>
#include <cmath>

#include <iostream>

const int screenWidth = 1080;
const int screenHeight = 720;

std::vector<Planet> planets;
std::shared_ptr<Body> Sun(new Body("Sun", (Vector3) {0, 0, 0},
                                   30 * SCALE*pow(10,8), YELLOW, 333000));

void loadPlanets();

int main() {
    InitWindow(screenWidth, screenHeight, "Planetarium");
    SetTargetFPS(60);

    Camera3D camera = { 0 };
    camera.position = (Vector3){ static_cast<float>(30.0f*SCALE*pow(10,8)+10.0f), 5.0f, static_cast<float>(30.0f*SCALE*pow(10,8) + 10.0f) }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;
    DisableCursor();

    loadPlanets();
    int p = 0;
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_FREE);


        if (IsKeyPressed('Z')){
            camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        }
        if (IsKeyPressed('N')) {
            camera.target = planets[p].get_pos();
            camera.position = {planets[p].get_radius()+10.0f, 5.0f, planets[p].get_radius() + 10.0f};
            p = ((p + 1)%8 + 8)%8;

        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();



        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        // std::cout << Sun->get_radius() <<", " << ColorToInt(Sun->get_color()) << std::endl;
        DrawSphere(Sun->get_pos(), Sun->get_radius(), Sun->get_color());

        DrawGrid(10000, 50);

        for(Planet planet: planets)
            DrawSphere(planet.get_pos(), planet.get_radius(), planet.get_color());

        // DrawGrid(10, 1.0f);

        EndMode3D();

        DrawRectangle( 10, 10, 320, 93, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines( 10, 10, 320, 93, BLUE);

        DrawText("Free camera default controls:", 20, 20, 10, BLACK);
        DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
        DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
        DrawText("- Z to zoom to (0, 0, 0)", 40, 80, 10, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;

}

void loadPlanets() {
    std::ifstream planets_file("../data/planets.json", std::ifstream::binary);
    Json::Value planets_root;
    planets_file >> planets_root;

    for(Json::Value::ArrayIndex i = 0; i != planets_root.size(); i++) {
        planets.emplace_back(planets_root[i]["name"].asString(),
                             (Vector3){static_cast<float>(planets_root[i]["semi_major_axis"].asFloat()*AU), 0, 0},
                             planets_root[i]["equatorial_diameter"].asFloat()/2.0f*SCALE*pow(10,9),
                             RED,
                             planets_root[i]["mass"].asFloat(),
                             Sun);
    }

}
