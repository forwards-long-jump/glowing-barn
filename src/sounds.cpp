#include "sounds.h"


QMediaPlayer* Sounds::player;
QMap<QString, QSoundEffect*> Sounds::sounds;
int Sounds::fadeOutTick = 0;
int Sounds::fadeoutDuration = 0;
QString Sounds::nextMusic = "";



void Sounds::playMusic(QString path)
{
    player->setMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + path));
    player->play();
    player->setVolume(100);
}

void Sounds::playSound(QString name)
{
    sounds[name]->play();
}

void Sounds::fadeOut(int duration_, QString nextMusic_)
{
    nextMusic = nextMusic_;
    fadeoutDuration = duration_;
    fadeOutTick = duration_;
}

void Sounds::setMediaPlayer(QMediaPlayer *player_)
{
    player = player_;
}

void Sounds::update()
{
    if(player->state() == QMediaPlayer::StoppedState)
    {
        player->play();
    }
    if(fadeOutTick > 0)
    {
        fadeOutTick--;
        player->setVolume(100 * (static_cast<float>(fadeOutTick) / fadeoutDuration));
    }
    else
    {
        if(fadeOutTick == 0)
        {
            fadeOutTick--;
            if(nextMusic != "")
            {
                Sounds::playMusic(nextMusic);
            }
        }
    }
}

void Sounds::loadSounds()
{
    // TODO: Load and unload sounds when they are required
    // TODO: Better loading system
    // Loading sounds multiple time will cause a memory leak
    QSoundEffect* sfx = new QSoundEffect();
    sfx->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/assets/sounds/UI_Quirky27.wav"));
    sounds.insert("magnetOn", sfx);

    sfx = new QSoundEffect();
    sfx->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/assets/sounds/UI_Quirky28.wav"));
    sounds.insert("magnetOff", sfx);

    sfx = new QSoundEffect();
    sfx->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/assets/sounds/UI_Quirky27.wav"));
    sounds.insert("leverOn", sfx);

    sfx = new QSoundEffect();
    sfx->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/assets/sounds/UI_Quirky28.wav"));
    sounds.insert("leverOff", sfx);

    sfx = new QSoundEffect();
    sfx->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/assets/sounds/slap.wav"));
    sounds.insert("crash", sfx);
}
