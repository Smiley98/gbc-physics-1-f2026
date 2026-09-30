#include "raylib.h"
#include "raymath.h"
#include "raygui.h"

#include <array>
#include <vector>
#include <cstdio>

int main()
{
    InitWindow(800, 800, "Physics-1");
    InitAudioDevice();
    SetTargetFPS(60);

    int test_ints[] = { 1, 2, 3, 4, 5 };
    float test_floats[] = { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f };

    // In order to save as text, we need to convert our memory (arrays of ints and floats) to text!
    char buffer[4096];
    int offset = 0;
    sprintf(buffer, "%i,%i,%i,%i,%i\n", test_ints[0], test_ints[1], test_ints[2], test_ints[3], test_ints[4]);
    bool result = SaveFileText("./test.txt", "Example text");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(WHITE);
            DrawFPS(720, 10);
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
