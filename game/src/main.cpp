#include "raylib.h"
#include "raymath.h"
#include "raygui.h"

// NOTE - You do NOT need to make a PhysicsSimulation class.
// As long as you store gravity (within a class or a global variable), you will get full marks for step 2 of Lab Exercise 2).
int main()
{
    Vector2 launch_position = { 100.0f, 700.0f };
    Vector2 launch_velocity = Vector2Zeros;
    float launch_angle = 0.0f;
    float launch_speed = 100.0f;

    InitWindow(800, 800, "Physics-1");
    InitAudioDevice();
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float tt = GetTime();       // Total time - time since the window was initialized
        float dt = GetFrameTime();  // Frame (delta) time - time from start to end of previous frame (ideally 1.0f / 60.0f milliseconds)
        // float hz = 1.0f / 60.0f; <-- dt should be approximately this value since we called SetTargetFPS(60);

        launch_velocity = Vector2Rotate(Vector2UnitX, -launch_angle * DEG2RAD) * launch_speed;

        BeginDrawing();
            ClearBackground(WHITE);
            DrawFPS(720, 10);

            DrawCircleV(launch_position, 20.0f, RED);
            DrawLineEx(launch_position, launch_position + launch_velocity, 4.0f, ORANGE);

            DrawText(TextFormat("Launch Angle %2.1f", launch_angle), 10, 10, 20, DARKGRAY);
            DrawText(TextFormat("Launch Speed %2.1f", launch_speed), 10, 140, 20, DARKGRAY);
            DrawText(TextFormat("Launch Position X %2.1f", launch_speed), 10, 260, 20, DARKGRAY);
            DrawText(TextFormat("Launch Position Y %2.1f", launch_speed), 10, 380, 20, DARKGRAY);

            GuiSlider({ 10.0f, 50.0f, 160.0f, 80.0f }, "0", "90", &launch_angle, 0.0f, 90.0f);
            GuiSlider({ 10.0f, 170.0f, 160.0f, 80.0f }, "10", "300", &launch_speed, 10.0f, 300.0f);
            GuiSlider({ 10.0f, 290.0f, 160.0f, 80.0f }, "0", "800", &launch_position.x, 0.0f, GetScreenWidth());
            GuiSlider({ 10.0f, 410.0f, 160.0f, 80.0f }, "0", "800", &launch_position.y, 0.0f, GetScreenHeight());
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
