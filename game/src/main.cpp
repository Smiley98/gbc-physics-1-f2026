#include "raylib.h"
#include "raymath.h"
#include "raygui.h"

// NOTE - You do NOT need to make a PhysicsSimulation class.
// As long as you store gravity (within a class or a global variable), you will get full marks for step 2 of Lab Exercise 2).
int main()
{
    InitWindow(800, 800, "Physics-1");
    InitAudioDevice();
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float tt = GetTime();       // Total time - time since the window was initialized
        float dt = GetFrameTime();  // Frame (delta) time - time from start to end of previous frame (ideally 1.0f / 60.0f milliseconds)
        // float hz = 1.0f / 60.0f; <-- dt should be approximately this value since we called SetTargetFPS(60);

        BeginDrawing();
        ClearBackground(WHITE);
        DrawFPS(720, 10);
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
