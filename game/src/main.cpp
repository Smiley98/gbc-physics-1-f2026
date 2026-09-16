#include "raylib.h"
#include "raymath.h"
#include "raygui.h"

int main()
{
    InitWindow(800, 800, "Physics-1");
    InitAudioDevice();
    SetTargetFPS(60);

    Vector2 launch_position = { 100.0f, 700.0f };
    float launch_angle = 0.0f;
    float launch_speed = 100.0f;

    // Note that since raylib is an RHS, positive rotations are CLOCKWISE
    // You will most likely want to negate the launch angle so that your launch_velocity vector points upwards
    Vector2 example_position = { 400.0f, 400.0f };
    Vector2 example_direction = Vector2Rotate(Vector2UnitX, 30.0f * DEG2RAD);

    while (!WindowShouldClose())
    {
        // 1. Calculate launch_direction Vector2 by using the Vector2Rotate function
        // 2. Calculate launch_velocity Vector2 by multiplying launch_direction by launch_speed
        // 3. Render launch_velocity as a line from launch_position to launch_position + launch_velocity

        BeginDrawing();
        ClearBackground(WHITE);

        DrawCircleV(launch_position, 20.0f, GRAY);

        // An example illustration of a rotated vector
        DrawLineEx(example_position, example_position + example_direction * 100.0f, 4.0f, ORANGE);

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
