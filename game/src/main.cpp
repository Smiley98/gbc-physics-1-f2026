#include "raylib.h"
#include "raymath.h"
#include "raygui.h"

int main()
{
    InitWindow(800, 800, "Physics-1");
    InitAudioDevice();
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        DrawCircleV(GetMousePosition(), 20.0f, RED);
        DrawText("Connor Smiley 123456", 650, 750, 20, BLUE);
        // If you want to be very accurate with formatting, use the MeasureText function!
        //MeasureText("Connor Smiley 123456", 20);

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
