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
        for (int j = SCREEN_HEIGHT; j >= 0; --j)
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
    else if (particles[x+1][y].state == Gas && IsInBounds(x+1, y))
    {
        MoveParticle(&particles[x][y], &particles[x+1][y]);
    }
    else if (particles[x-1][y].state == Gas && IsInBounds(x-1, y))
    {
        MoveParticle(&particles[x][y], &particles[x-1][y]);
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
    return ((x > 0 && x < SCREEN_WIDTH - 1) && (y > 0 && y < SCREEN_HEIGHT - 1));
}

void PlaceParticle(Particle** particles, int x, int y, int type, float radius)
{
    int chosenType, chosenState;
    switch (type)
    {
        case Sand:
            chosenType = Sand;
            chosenState = Solid;
            break;
        case Water:
            chosenType = Water;
            chosenState = Liquid;
            break;
        default:
            printf("No Particle :c\n");
    }
    
    int radiusSqr = (int)(radius * radius);
    for (int i = -(int)radius; i <= (int)radius; ++i)
    {
        for (int j = - (int)radius; j <= (int) radius; ++j)
        {
            int sqrSum = (i*i) + (j*j);
            if (sqrSum <= radiusSqr)
            {
                if (IsInBounds(i + x, j + y))
                {
                    particles[i+x][j+y].type = chosenType;
                    particles[i+x][j+y].state = chosenState;
                };
            }

        }
    }
}