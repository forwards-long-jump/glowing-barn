#ifndef PARTICLESPAWNER_H
#define PARTICLESPAWNER_H

#include "component.h"
#include "particle.h"

class ParticleSpawnerComponent : public Component
{
public:
    ParticleSpawnerComponent(void (*particleRender)(QPainter* painter, Particle* particle), void (*particleUpdate)(Particle* particle), QString particleSpawnerName);
    void spawn(int x, int y, float dx, float dy, int w, int h, int lifetime);

    void update() override;
    void onDisable() override;

    ~ParticleSpawnerComponent();

private:
    void (*particleRender)(QPainter* painter, Particle* particle);
    void (*particleUpdate)(Particle* particle);
    int particleIndex = 0;
    QVector<Particle*> particles;
};

#endif // PARTICLESPAWNER_H
