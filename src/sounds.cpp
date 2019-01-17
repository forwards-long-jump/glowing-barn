#include "sounds.h"


QMediaPlayer* Sounds::player;
QMap<QString, QSoundEffect*> Sounds::sounds;
int Sounds::fadeOutTick = 0;
int Sounds::fadeoutDuration = 0;
bool Sounds::muted = false;
QString Sounds::nextMusic = "";

SoundEffectThread* Sounds::magnetOn = new SoundEffectThread();
SoundEffectThread* Sounds::magnetOff = new SoundEffectThread();
SoundEffectThread* Sounds::leverOn = new SoundEffectThread();
SoundEffectThread* Sounds::leverOff = new SoundEffectThread();
SoundEffectThread* Sounds::crash = new SoundEffectThread();
SoundEffectThread* Sounds::demag = new SoundEffectThread();

void Sounds::playMusic(QString path)
{
    player->setMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + path));
    player->play();
    player->setVolume(100);
}

void Sounds::playSound(QString name)
{
    if(!muted)
    {
        if(name == "magnetOn")
        {
            magnetOn->start();
        }
        else if (name == "magnetOff")
        {
            magnetOff->start();
        }
        else if (name == "leverOn")
        {
            leverOn->start();
        }
        else if (name == "leverOff")
        {
            leverOff->start();
        }
        else if (name == "crash")
        {
            crash->start();
        }
        else if (name == "demag")
        {
            demag->start();
        }
    }
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
    magnetOn->init("/assets/sounds/magnet-on.wav");
    magnetOff->init("/assets/sounds/magnet-off.wav");
    leverOn->init("/assets/sounds/lever-on.wav");
    leverOff->init("/assets/sounds/lever-on.wav");
    crash->init("/assets/sounds/slap.wav");
    demag->init("/assets/sounds/demag-sound.wav");
}

void Sounds::toggleMute()
{
    muted = !muted;
    player->setMuted(muted);
}

bool Sounds::isMuted()
{
    return muted;
}
