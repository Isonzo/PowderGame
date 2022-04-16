#include <stdbool.h>
#include <stdlib.h>
#include "include/raylib.h"
#include "include/particles.h"

struct particle
{
    enum{Air, Sand} type;
};

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
                UpdateSand(particles, i, j);
            }
            
        }
    }
}

void MoveParticle(Particle* active , Particle* passive)
{
    int temp = active->type;
    active->type = passive->type;
    passive->type = temp;
}

void UpdateSand(Particle** particles, int x, int y)
{
    if (particles[x][y+1].type == Air && y + 1 < SCREEN_HEIGHT)
    {
        MoveParticle(&particles[x][y], &particles[x][y+1]);
    }
    else if (particles[x-1][y+1].type == Air && IsInBounds(x-1, y+1))
    {
        MoveParticle(&particles[x][y], &particles[x-1][y+1]);
    }
    else if (particles[x+1][y+1].type == Air && IsInBounds(x+1, y+1))
    {
        MoveParticle(&particles[x][y], &particles[x+1][y+1]);
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

bool IsInBounds(int x, int y)
{
    return ((x > 0 && x < SCREEN_WIDTH) && (y > 0 && y < SCREEN_HEIGHT));
}

void PlaceParticle(Particle** particles, int x, int y)
{
    particles[x][y].type = Sand;
}