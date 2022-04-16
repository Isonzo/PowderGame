#include "include/raylib.h"
#include "include/particles.h"

#define FONT_SIZE 30


int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "SandSimulator");
    SetTargetFPS(60);
    int offset = MeasureText("SandSim", FONT_SIZE);

    Particle** particles = InitParticles();    

    while (!WindowShouldClose())
    {
        Vector2 mousePos = GetMousePosition();

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsInBounds((int)mousePos.x, (int)mousePos.y))
        {
            PlaceParticle(particles, (int)mousePos.x, (int)mousePos.y);
        }

        UpdateParticles(particles);


        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("SandSim", SCREEN_WIDTH/2 - offset/2, SCREEN_HEIGHT/2, FONT_SIZE, LIGHTGRAY);
        DrawParticles(particles);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}