#include "raylib.h"
#include "raymath.h"
#include "raygui.h"

#include <array>
#include <vector>

// NOTE - You do NOT need to make a PhysicsSimulation class.
// LE2 step 2 has been done for you!

struct PhysicsBody
{
    Vector2 position;
    // Add velocity, drag, and mass to complete LE2 step 1
    // (Mass and drag will NOT be used in this lab exercise)
};

constexpr Vector2 GRAVITY = { 0.0f, 9.81f };

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

        if (IsKeyPressed(KEY_SPACE))
        {
            // LE2 step 3 - Add the ability to instantiate a physics body and launch it from launch_position at launch_velocity
        }
        
        // Ensure motion is applied to physics bodies frame-after-frame using kinematics (position, velocity, and acceleration). Hint:
        // acc = gravity * dt
        // vel += acc * dt
        // pos += vel * dt

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
