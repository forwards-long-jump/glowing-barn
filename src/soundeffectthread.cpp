#include "soundeffectthread.h"

/**
 * @brief SoundEffectThread::SoundEffectThread
 */
SoundEffectThread::SoundEffectThread()
{
    sfx = new QSoundEffect;
}

/**
 * @brief SoundEffectThread::~SoundEffectThread
 */
SoundEffectThread::~SoundEffectThread()
{
    delete sfx;
    sfx = nullptr;
}

/**
 * @brief SoundEffectThread::init
 * @param fileName
 */
void SoundEffectThread::init(QString fileName)
{
    sfx->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + fileName));
}

/**
 * @brief SoundEffectThread::run
 */
void SoundEffectThread::run()
{
    sfx->play();
}
