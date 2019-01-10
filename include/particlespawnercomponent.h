#ifndef PARTICLESPAWNER_H
#define PARTICLESPAWNER_H

#include "component.h"
#include "particle.h"
#include "scene.h"
#include "magnetgravityreactorcomponent.h"
#include "magnetzipperreactorcomponent.h"

class Entity;

struct ParticleParameters
{
    int x = 0;
    int y = 0;
    float dx = 0;
    float dy = 0;
    int w = 0;
    int h = 0;
    int lifetime = 0;
};

class ParticleSpawnerComponent : public Component
{
public:
    ParticleSpawnerComponent(void (*particleRender)(QPainter* painter, Particle* particle), void (*particleUpdate)(Particle* particle), QVector<ParticleParameters> (*spawnCondition)(Entity *, int tick), QString particleSpawnerName);
    void spawn(int x, int y, float dx, float dy, int w, int h, int lifetime);

    void update() override;
    void onDisable() override;

private:
    void (*particleRender)(QPainter* painter, Particle* particle);
    void (*particleUpdate)(Particle* particle);
    QVector<ParticleParameters> (*spawnCondition)(Entity* entity, int tick);
    int particleIndex = 0;
    QVector<Particle*> particles;
};

#endif // PARTICLESPAWNER_H
