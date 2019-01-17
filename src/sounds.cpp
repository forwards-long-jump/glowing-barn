#include "sounds.h"


QMediaPlayer* Sounds::player;
QMap<QString, QSoundEffect*> Sounds::sounds;
int Sounds::fadeOutTick = 0;
int Sounds::fadeoutDuration = 0;
bool Sounds::muted = false;
QString Sounds::nextMusic = "";


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
        sounds[name]->play();
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
    // TODO: Load and unload sounds when they are required
    // TODO: Better loading system
    // Loading sounds multiple time will cause a memory leak
    QSoundEffect* sfx = new QSoundEffect();
    sfx->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/assets/sounds/magnet-on.wav"));
    sounds.insert("magnetOn", sfx);

    sfx = new QSoundEffect();
    sfx->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/assets/sounds/magnet-off.wav"));
    sounds.insert("magnetOff", sfx);

    sfx = new QSoundEffect();
    sfx->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/assets/sounds/lever.wav"));
    sounds.insert("leverOn", sfx);

    sfx = new QSoundEffect();
    sfx->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/assets/sounds/lever.wav"));
    sounds.insert("leverOff", sfx);

    sfx = new QSoundEffect();
    sfx->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/assets/sounds/slap.wav"));
    sounds.insert("crash", sfx);

    sfx = new QSoundEffect();
    sfx->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/assets/sounds/demag-sound.wav"));
    sounds.insert("demag", sfx);
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
