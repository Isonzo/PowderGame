#include "include/raylib.h"
#include <stdlib.h>
#include <stdbool.h>

#define SCREEN_HEIGHT 400
#define SCREEN_WIDTH 400
#define FONT_SIZE 30

typedef struct particle
{
    enum{Air, Sand} type;
}Particle;

Particle** InitParticles(void);
void UpdateParticles(Particle** particles);
void DrawParticles(Particle** particles);

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "SandSimulator");
    SetTargetFPS(60);

    Particle** particles = InitParticles();    

    while (!WindowShouldClose())
    {
        Vector2 mousePos = GetMousePosition();

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            particles[(int)mousePos.x][(int)mousePos.y].type = Sand;
        }

        UpdateParticles(particles);


        BeginDrawing();
        ClearBackground(RAYWHITE);
        int offset = MeasureText("SandSim", FONT_SIZE);

        DrawText("SandSim", SCREEN_WIDTH/2 - offset/2, SCREEN_HEIGHT/2, FONT_SIZE, LIGHTGRAY);
        DrawParticles(particles);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}


Particle** InitParticles(void)
{
    /*
    Makes a 2D matrix of particles, and sets the starting type for all particles as Air.
    */
    Particle** particles = malloc(SCREEN_WIDTH * sizeof(Particle*));
    for (int i = 0; i < SCREEN_WIDTH; ++i)
    {
        particles[i] = malloc(SCREEN_HEIGHT * sizeof(Particle));
        for (int j = 0; j < SCREEN_HEIGHT; ++j)
        {
            particles[i][j].type = Air;
        }
    }
    return particles;
}

void UpdateParticles(Particle** particles)
{
    for (int i = 0; i < SCREEN_WIDTH; ++i)
    {
        for (int j = 0; j < SCREEN_HEIGHT; ++j)
        {
            if (particles[i][j].type == Air) continue;

            if (particles[i][j].type == Sand)
            {
                if (particles[i][j+1].type == Air && j + 1 < SCREEN_HEIGHT)
                {
                    particles[i][j].type = Air;
                    particles[i][j+1].type = Sand;
                }
            }

        }
    }
}

void DrawParticles(Particle** particles)
{
    for (int i = 0; i < SCREEN_WIDTH; ++i)
    {
        for (int j = 0; j < SCREEN_HEIGHT; ++j)
        {
            if (particles[i][j].type == Sand)
            {
                DrawPixel(i, j, BEIGE);
            }
        }
    }
}