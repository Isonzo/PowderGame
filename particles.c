#include <stdbool.h>
#include <stdlib.h>
#include "include/raylib.h"
#include "include/particles.h"
#include <stdio.h>

struct particle
{
    enum{Air, Sand, Water} type;
    enum{Gas, Liquid, Solid} state;
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
            switch (particles[i][j].type)
            {
                case Air:
                    continue;
                    break;
                case Sand:
                    UpdateSand(particles, i, j);
                    break;
                case Water:
                    UpdateWater(particles, i, j);
                    break;
            }
        }
    }
}

void MoveParticle(Particle* active , Particle* passive)
{
    int temp = active->type;
    int state = active->state;
    active->type = passive->type;
    active->state = passive->state;
    passive->type = temp;
    passive->state = state;
}

void UpdateSand(Particle** particles, int x, int y)
{
    if (particles[x][y+1].state != Solid && y + 1 < SCREEN_HEIGHT)
    {
        MoveParticle(&particles[x][y], &particles[x][y+1]);
    }
    else if (particles[x-1][y+1].state != Solid && IsInBounds(x-1, y+1))
    {
        MoveParticle(&particles[x][y], &particles[x-1][y+1]);
    }
    else if (particles[x+1][y+1].state != Solid && IsInBounds(x+1, y+1))
    {
        MoveParticle(&particles[x][y], &particles[x+1][y+1]);
    }   
}

void UpdateWater(Particle** particles, int x, int y)
{
    if (particles[x][y+1].state == Gas && IsInBounds(x, y+1))
    {
        MoveParticle(&particles[x][y], &particles[x][y+1]);
    }
    else if (particles[x-1][y+1].state == Gas && IsInBounds(x-1, y+1))
    {
        MoveParticle(&particles[x][y], &particles[x-1][y+1]);
    }
    else if (particles[x+1][y+1].state == Gas && IsInBounds(x+1, y+1))
    {
        MoveParticle(&particles[x][y], &particles[x+1][y+1]);
    }   
    else if (particles[x-1][y].state == Gas && IsInBounds(x-1, y))
    {
        MoveParticle(&particles[x][y], &particles[x-1][y]);
    }
    else if (particles[x+1][y].state == Gas && IsInBounds(x+1, y))
    {
        MoveParticle(&particles[x][y], &particles[x+1][y]);
    }
}

void DrawParticles(Particle** particles)
{
    for (int i = 0; i < SCREEN_WIDTH; ++i)
    {
        for (int j = 0; j < SCREEN_HEIGHT; ++j)
        {
            switch (particles[i][j].type)
            {
                case Air:
                    continue;
                    break;
                case Sand:
                    DrawPixel(i, j, BEIGE);
                    break;
                case Water:
                    DrawPixel(i, j, BLUE);
                    break;
            }
        }
    }
}

bool IsInBounds(int x, int y)
{
    return ((x > 0 && x < SCREEN_WIDTH) && (y > 0 && y < SCREEN_HEIGHT));
}

void PlaceParticle(Particle** particles, int x, int y, int type)
{
    switch (type)
    {
        case Sand:
            particles[x][y].type = Sand;
            particles[x][y].state = Solid;
            break;
        case Water:
            particles[x][y].type = Water;
            particles[x][y].state = Liquid;
            break;
        default:
            printf("No Particle :c\n");
    }
}