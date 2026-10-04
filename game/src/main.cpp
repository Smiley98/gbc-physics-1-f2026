#include "raylib.h"
#include "raymath.h"
#include "raygui.h"

#include <array>
#include <vector>

struct PhysicsBody
{
    Vector2 pos;
    Vector2 vel;
    Vector2 acc;

    float mass;
    float drag;

    Color color;
};

constexpr Vector2 GRAVITY = { 0.0f, 100.0f };

int main()
{
    Vector2 launch_position = { 100.0f, 700.0f };
    Vector2 launch_velocity = Vector2Zeros;
    float launch_angle = 0.0f;
    float launch_speed = 100.0f;
    float launch_drag = 1.0f;

    std::vector<PhysicsBody> bodies;

    InitWindow(800, 800, "Physics-1");
    InitAudioDevice();
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        launch_velocity = Vector2Rotate(Vector2UnitX, -launch_angle * DEG2RAD) * launch_speed;

        if (IsKeyPressed(KEY_SPACE))
        {
            PhysicsBody body{};
            body.pos = launch_position;
            body.vel = launch_velocity;
            body.acc = GRAVITY;
            body.drag = launch_drag;
            body.color = RED;
            bodies.push_back(body);
        }

        for (PhysicsBody& body : bodies)
        {
            body.vel += body.acc * dt;
            body.vel *= powf(body.drag, dt);
            body.pos += body.vel * dt;
        }

        BeginDrawing();
            ClearBackground(WHITE);
            DrawFPS(720, 10);

            DrawCircleV(launch_position, 20.0f, RED);
            DrawLineEx(launch_position, launch_position + launch_velocity, 4.0f, ORANGE);

            DrawText(TextFormat("Launch Angle %2.1f", launch_angle), 10, 10, 20, DARKGRAY);
            DrawText(TextFormat("Launch Speed %2.1f", launch_speed), 10, 140, 20, DARKGRAY);
            DrawText(TextFormat("Launch Position X %2.1f", launch_speed), 10, 260, 20, DARKGRAY);
            DrawText(TextFormat("Launch Position Y %2.1f", launch_speed), 10, 380, 20, DARKGRAY);
            DrawText(TextFormat("Launch Drag %2.1f", launch_drag), 10, 500, 20, DARKGRAY);

            GuiSlider({ 10.0f, 50.0f, 160.0f, 80.0f }, "0", "90", &launch_angle, 0.0f, 90.0f);
            GuiSlider({ 10.0f, 170.0f, 160.0f, 80.0f }, "10", "300", &launch_speed, 10.0f, 300.0f);
            GuiSlider({ 10.0f, 290.0f, 160.0f, 80.0f }, "0", "800", &launch_position.x, 0.0f, GetScreenWidth());
            GuiSlider({ 10.0f, 410.0f, 160.0f, 80.0f }, "0", "800", &launch_position.y, 0.0f, GetScreenHeight());
            GuiSlider({ 10.0f, 530.0f, 160.0f, 80.0f }, "0.0", "1.0", &launch_drag, 0.0f, 1.0f);

            for (PhysicsBody& body : bodies)
                DrawCircleV(body.pos, 20.0f, body.color);
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
