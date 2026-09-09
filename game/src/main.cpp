#include "raylib.h"
#include "raymath.h"
#include "raygui.h"

int main()
{
    InitWindow(800, 800, "Physics-1");
    InitAudioDevice();
    SetTargetFPS(60);

    float x = 400.0f;
    float y = 400.0f;
    float a = 10.0f;    // amplitude (radius of movement)
    float b = 4.0f;     // frequency (rate of movement)

    Vector2 pos = { 100.0f, 400.0f };

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        float t = GetTime();
        //printf("%f\n", time); <-- need to include cstdio if you want printf, or iostream if you like std::cout <<
        //TraceLog(LOG_INFO, "%f", time); // raylib uses tracelog to output to the console
        //TraceLog(LOG_INFO, "%f", dt);

        // Simple animation
        pos += Vector2UnitX * 100.0f * dt;

        BeginDrawing();
            ClearBackground(WHITE);

            DrawCircleV(pos, 20.0f, RED);

            DrawCircle(50, 100, 25.0f, GREEN);
            DrawCircle(150, 200, 25.0f, DARKGREEN);
            DrawLine(50, 100, 150, 200, LIME);

            // TODO -- replace with your name and student number!
            DrawCircleV(GetMousePosition(), 20.0f, RED);
            DrawText("Connor Smiley 123456", 650, 750, 20, BLUE);
            // If you want to be very accurate with formatting, use the MeasureText function!
            //MeasureText("Connor Smiley 123456", 20);

            // Use TextFormat to convert data (like int or float) to const char* (text)!
            // TextFormat follows C-style formatting: https://cplusplus.com/reference/cstdio/printf/
            float a = 42.123f;
            int b = 5;
            const char* text = TextFormat("Number A: %f, Number B: %i.", a, b);
            DrawText(text, 200, 600, 20, BLUE);
            // TODO -- replace with time

            // TODO -- animate this based on equation in lab document week 1!
            DrawCircle(x, y, 25.0f, PURPLE);

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
