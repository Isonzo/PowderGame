#ifndef PARTICLES_H
#define PARTICLES_H

#define SCREEN_HEIGHT 400
#define SCREEN_WIDTH 400

typedef struct particle Particle;

Particle** InitParticles(void);
void UpdateParticles(Particle** particles);
void MoveParticle(Particle* active , Particle* passive);
void UpdateSand(Particle** particles, int x, int y);
void DrawParticles(Particle** particles);
bool IsInBounds(int x, int y);
void PlaceParticle(Particle** particles, int x, int y);

#endif