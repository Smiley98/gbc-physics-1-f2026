#include "raylib.h"
#include "raymath.h"
#include "raygui.h"

#include <array>
#include <vector>
#include <cassert>

enum ColliderType
{
    COLLIDER_TYPE_NONE,
    COLLIDER_TYPE_CIRCLE,
    COLLIDER_TYPE_PLANE
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
        struct
        {
            Vector2 normal;
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

bool HitTestCirclePlane(Vector2 pos_circle, float radius, Vector2 pos_plane, Vector2 normal)
{
    // Lab Exercise 4 TODO -- complete this function
    return false;
}

void InitBodies(std::vector<PhysicsBody>* bodies);

int main()
{
    std::vector<PhysicsBody> bodies;
    InitBodies(&bodies);

    InitWindow(800, 800, "Physics-1");
    InitAudioDevice();
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        for (PhysicsBody& body : bodies)
        {
            body.acc = GRAVITY;
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

                // Lab Exercise 4 TODO -- ensure HitTestCirclePlane works correctly!
                bool collision = HitTestCirclePlane(a.pos, a.collider.radius, b.pos, b.collider.normal);
                a.collision |= collision;
                b.collision |= collision;
            }
        }

        BeginDrawing();
            ClearBackground(WHITE);
            DrawFPS(720, 10);

            for (const PhysicsBody& body : bodies)
            {
                Color color = body.collision ? RED : GREEN;
                const Collider& collider = body.collider;
                if (collider.type == COLLIDER_TYPE_CIRCLE)
                {
                    DrawCircleV(body.pos, collider.radius, color);
                }
                if (collider.type == COLLIDER_TYPE_PLANE)
                {
                    Vector2 perp = { collider.normal.y, -collider.normal.x };
                    DrawLineEx(body.pos - perp * 100.0f, body.pos + perp * 100.0f, 4.0f, color);
                    DrawLineEx(body.pos, body.pos + collider.normal * 50.0f, 2.0f, ORANGE);
                }
            }
            
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}

void InitBodies(std::vector<PhysicsBody>* bodies)
{
    {
        PhysicsBody circle{};
        circle.pos = { 400.0f, 400.0f };
        circle.vel = Vector2Zeros;
        circle.gravity_scale = 1.0f;
        circle.collider.type = COLLIDER_TYPE_CIRCLE;
        circle.collider.radius = 20.0f;
        bodies->push_back(circle);
    }

    {
        PhysicsBody plane{};
        plane.pos = { 400.0f, 600.0f };
        plane.vel = Vector2Zeros;
        plane.gravity_scale = 0.0f;
        plane.collider.type = COLLIDER_TYPE_PLANE;
        plane.collider.normal = Vector2UnitY * -1.0f;
        bodies->push_back(plane);
    }

    for (const PhysicsBody& body : *bodies)
    {
        // Ensure data is valid before first body update
        assert(body.collider.type != COLLIDER_TYPE_NONE);
    }
}
