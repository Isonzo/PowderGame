#include "include/raylib.h"
#include "include/particles.h"
#include "time.h"

#define FONT_SIZE 30


int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "SandSimulator");
    SetTargetFPS(60);
    int offset = MeasureText("SandSim", FONT_SIZE);

    float brushSize = 20.0f;

    Particle** particles = InitParticles();

    while (!WindowShouldClose())
    {
        Vector2 mousePos = GetMousePosition();

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsInBounds((int)mousePos.x, (int)mousePos.y))
        {
            
            PlaceParticle(particles, (int)mousePos.x, (int)mousePos.y, 1, brushSize);
        }
        else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && IsInBounds((int)mousePos.x, (int)mousePos.y))
        {
            PlaceParticle(particles, (int)mousePos.x, (int)mousePos.y, 2, brushSize);
        }

        brushSize += GetMouseWheelMove()*5;
        if (brushSize < 2) brushSize = 2;
        if (brushSize > 50) brushSize = 50;

        UpdateParticles(particles);


        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("SandSim", SCREEN_WIDTH/2 - offset/2, SCREEN_HEIGHT/2, FONT_SIZE, LIGHTGRAY);
        DrawParticles(particles);

        DrawCircleLines(GetMouseX(), GetMouseY(), brushSize, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

