#include "raylib.h"
#include "body.h"
#include "planet.h"

#include <json/json.h>
#include <fstream>

const int screenWidth = 1080;
const int screenHeight = 720;

std::vector<Planet> planets;

void loadPlanets();

int main() {
    InitWindow(screenWidth, screenHeight, "Planetarium");
    SetTargetFPS(60);

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 1000.0f, 1000.0f, 1000.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;
    DisableCursor();

    Body Sun("Sun", (Vector3){0, 0, 0}, 109*SCALE, YELLOW, 333000);

    

    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_FREE);


        if (IsKeyPressed('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };


        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();



        ClearBackground(RAYWHITE);

        BeginMode3D(camera);



        DrawGrid(10, 1.0f);

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
    std::ifstream planets_file("../planets.json", std::ifstream::binary);
    Json::Value planets_root;
    planets_file >> planets_root;

    for(auto planet: planets_root) {
        planets.push_back(Planet(planet["name"] ));
    }

}
