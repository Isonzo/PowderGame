#include "include/raylib.h"

#define SCREEN_HEIGHT 400
#define SCREEN_WIDTH 400
#define FONT_SIZE 30

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "SandSimulator");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(RAYWHITE);
        int offset = MeasureText("SandSim", FONT_SIZE);

        DrawText("SandSim", SCREEN_WIDTH/2 - offset/2, SCREEN_HEIGHT/2, FONT_SIZE, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}