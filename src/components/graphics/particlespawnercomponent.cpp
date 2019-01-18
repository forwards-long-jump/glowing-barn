#include "particlespawnercomponent.h"

/**
 * @brief ParticleSpawnerComponent::ParticleSpawnerComponent
 * @param particleRender Lambda rendering function for the particles
 * @param particleUpdate Lambda update function for the particles
 * @param spawnCondition Parameters for the spawning of particles
 * @param particleSpawnerName
 */
ParticleSpawnerComponent::ParticleSpawnerComponent(void (*particleRender)(QPainter *, Particle *),
                                                   void (*particleUpdate)(Particle* particle),
                                                   QVector<ParticleParameters> (*spawnCondition)(Entity* entity, int tick),
                                                   QString particleSpawnerName)
    : Component(particleSpawnerName),
    particleRender(particleRender),
    spawnCondition(spawnCondition),
    particleUpdate(particleUpdate)
{

}

/**
 * @brief ParticleSpawnerComponent::spawn
 * @param x
 * @param y
 * @param dx
 * @param dy
 * @param width
 * @param height
 * @param lifetime
 * @param affectedByMagnets
 */
void ParticleSpawnerComponent::spawn(int x, int y, float dx, float dy, int w, int h, int lifetime, bool affectedByMagnets)
{
    Particle* p = new Particle(dx, dy, w, h, lifetime, this->particleRender, particleIndex++);
    if(affectedByMagnets)
    {
        p->addComponent(new PhysicsComponent(100, 100, 0, -10, 0, 100));
        p->addComponent(new MagnetGravityReactorComponent);
        p->addComponent(new MagnetZipperReactorComponent);
    }
    p->setZValue(-1);
    p->setPos(x, y);
    static_cast<Scene*>(getParent()->scene())->getGame()->addEntityLater(p, static_cast<Entity*>(this->parent->parentItem()));
    //p->setParentItem(this->parent->parentItem());
    particles.append(p);
}

/**
 * @brief ParticleSpawnerComponent::update
 */
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

/**
 * @brief ParticleSpawnerComponent::onDisable
 */
void ParticleSpawnerComponent::onDisable()
{
    for(Particle* particle : particles)
    {
        particle->deleteLater();
    }
    particles.clear();
}
