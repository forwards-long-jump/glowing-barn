#include "particlespawnercomponent.h"

ParticleSpawnerComponent::ParticleSpawnerComponent(void (*particleRender)(QPainter *, Particle *),
                                                   void (*particleUpdate)(Particle* particle),
                                                   QVector<ParticleParameters> (*spawnCondition)(Entity* entity, int tick),
                                                   QString particleSpawnerName):
    Component(particleSpawnerName),
    particleRender(particleRender),
    spawnCondition(spawnCondition),
    particleUpdate(particleUpdate) {}

void ParticleSpawnerComponent::spawn(int x, int y, float dx, float dy, int w, int h, int lifetime)
{
    Particle* p = new Particle(dx, dy, w, h, lifetime, this->particleRender, particleIndex++);
    p->setZValue(-1);
    p->setPos(x, y);
    static_cast<Scene*>(getParent()->scene())->getGame()->addEntityLater(p, this->parent->parentItem());
    //p->setParentItem(this->parent->parentItem());
    particles.append(p);
}

void ParticleSpawnerComponent::update()
{
    QVector<ParticleParameters> parameters = spawnCondition(getParent(), static_cast<Scene*>(getParent()->scene())->getGame()->getTick());

    for(int i = 0; i < parameters.length(); ++i)
    {
        spawn(parameters[i].x, parameters[i].y, parameters[i].dx, parameters[i].dy, parameters[i].w, parameters[i].h, parameters[i].lifetime);
    }

    for(int i = 0; i < particles.length(); ++i)
    {
        Particle* particle = particles[i];
        particleUpdate(particle);

        // Handle particle lifetime>
        particle->decrementLifetime();
        if(particle->getLifetime() < 1)
        {
           particle->deleteLater();
           particles.removeAt(i);
           i--;
        }
    }
}

void ParticleSpawnerComponent::onDisable()
{
    for(Particle* particle : particles)
    {
        particle->deleteLater();
    }
    particles.clear();
}
