#include "particlespawnercomponent.h"

ParticleSpawnerComponent::ParticleSpawnerComponent(void (*particleRender)(QPainter *, Particle *),
                                                   void (*particleUpdate)(Particle* particle),
                                                   QString particleSpawnerName) :
    Component(particleSpawnerName),
    particleRender(particleRender),
    particleUpdate(particleUpdate) {}

void ParticleSpawnerComponent::spawn(int x, int y, float dx, float dy, int w, int h, int lifetime)
{
    Particle* p = new Particle(dx, dy, w, h, lifetime, this->particleRender, particleIndex++);
    p->setPos(x, y);
    particles.append(p);
    getParent()->scene()->addItem(p);
}

void ParticleSpawnerComponent::update()
{
    for(int i = 0; i < particles.length(); ++i)
    {
        Particle* particle = particles[i];
        particleUpdate(particle);

        // Handle particle lifetime
        particle->decrementLifetime();
        if(particle->getLifetime() < 0)
        {
            delete particle;
            particles.removeAt(i);
            i--;
        }
    }
}

void ParticleSpawnerComponent::onDisable()
{
    for(Particle* particle : particles)
    {
        delete particle;
    }
    particles.clear();
}

ParticleSpawnerComponent::~ParticleSpawnerComponent()
{
    onDisable();
}
