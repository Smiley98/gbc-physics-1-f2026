#include "raylib.h"
#include "raymath.h"
#include "raygui.h"

#include <array>
#include <vector>
#include <cassert>

enum ColliderType
{
    COLLIDER_TYPE_NONE,
    COLLIDER_TYPE_CIRCLE
};

struct Collider
{
    ColliderType type;
    union
    {
        struct
        {
            float radius;
        };
    };
};

struct PhysicsBody
{
    Vector2 pos;
    Vector2 vel;
    Vector2 acc;

    float gravity_scale;
    float mass;
    float drag;

    Collider collider;
    bool collision;
};

constexpr Vector2 GRAVITY = { 0.0f, 100.0f };

bool HitTestCircles(Vector2 pos_a, float radius_a, Vector2 pos_b, float radius_b)
{
    // Lab Exercise 3 TODO -- complete this function, VERY similar to raylib's CheckCollisionCircles function!
    return false;
}

int main()
{
    Vector2 launch_position = { 100.0f, 700.0f };
    Vector2 launch_velocity = Vector2Zeros;
    float launch_angle = 0.0f;
    float launch_speed = 100.0f;
    float launch_drag = 1.0f;

    std::vector<PhysicsBody> bodies;
    {
        PhysicsBody body{};
        body.pos = { 400.0f, 400.0f };
        body.vel = Vector2Zeros;
        body.collider.type = COLLIDER_TYPE_CIRCLE;
        body.collider.radius = 20.0f;
        bodies.push_back(body);
    }

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

            body.gravity_scale = 1.0f;
            body.drag = launch_drag;
            body.mass = 1.0f;

            body.collider.type = COLLIDER_TYPE_CIRCLE;
            body.collider.radius = 20.0f;
            
            bodies.push_back(body);
        }

        for (PhysicsBody& body : bodies)
        {
            body.vel += body.acc * body.gravity_scale * dt;
            body.vel *= powf(body.drag, dt);
            body.pos += body.vel * dt;

            body.collision = false;
        }

        for (size_t i = 0; i < bodies.size(); i++)
        {
            for (size_t j = i + 1; j < bodies.size(); j++)
            {
                PhysicsBody& a = bodies[i];
                PhysicsBody& b = bodies[j];

                // Lab Exercise 3 TODO -- Replace CheckCollisionCircles with HitTestCircles, ensure the result is the same!
                //bool collision = CheckCollisionCircles(a.pos, a.collider.radius, b.pos, b.collider.radius);
                bool collision = HitTestCircles(a.pos, a.collider.radius, b.pos, b.collider.radius);
                a.collision |= collision;
                b.collision |= collision;
            }
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

            for (const PhysicsBody& body : bodies)
            {
                assert(body.collider.type != COLLIDER_TYPE_NONE);
                if (body.collider.type == COLLIDER_TYPE_CIRCLE)
                {
                    Color color = body.collision ? RED : GREEN;
                    DrawCircleV(body.pos, body.collider.radius, color);
                }
            }
            
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
