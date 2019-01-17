#include "include/soundeffectthread.h"

SoundEffectThread::SoundEffectThread()
{
    sfx = new QSoundEffect;
}

SoundEffectThread::~SoundEffectThread()
{
    delete sfx;
    sfx = nullptr;
}

void SoundEffectThread::init(QString fileName)
{
    sfx->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + fileName));
}

void SoundEffectThread::run()
{
    sfx->play();
}
