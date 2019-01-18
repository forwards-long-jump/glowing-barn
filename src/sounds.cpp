#include "sounds.h"


QMediaPlayer* Sounds::player;
QMap<QString, QSoundEffect*> Sounds::sounds;
int Sounds::fadeOutTick = 0;
int Sounds::fadeoutDuration = 0;
bool Sounds::muted = false;
QString Sounds::nextMusic = "";

SoundEffectThread* Sounds::magnetOn = new SoundEffectThread();
SoundEffectThread* Sounds::magnetOff = new SoundEffectThread();

/**
 * @brief Sounds::playMusic
 * @param path
 */
void Sounds::playMusic(QString path)
{
    player->setMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + path));
    player->play();
    player->setVolume(100);
}

/**
 * @brief Sounds::playSound
 * @param name
 */
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
    }
}

/**
 * @brief Sounds::fadeOut
 * @param duration_
 * @param nextMusic_
 */
void Sounds::fadeOut(int duration_, QString nextMusic_)
{
    nextMusic = nextMusic_;
    fadeoutDuration = duration_;
    fadeOutTick = duration_;
}

/**
 * @brief Sounds::setMediaPlayer
 * @param player_
 */
void Sounds::setMediaPlayer(QMediaPlayer *player_)
{
    player = player_;
}

/**
 * @brief Sounds::update
 */
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

/**
 * @brief Sounds::loadSounds
 */
void Sounds::loadSounds()
{
    // TODO: Load and unload sounds when they are required
    // TODO: Better loading system
    // Loading sounds multiple time will cause a memory leak
    magnetOn->init("/assets/sounds/magnetON.wav");
    magnetOff->init("/assets/sounds/magnetOFF.wav");
    /*QSoundEffect* sfx = new QSoundEffect();
    sfx->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/assets/sounds/magnetON.wav"));
    sounds.insert("magnetOn", sfx);

    sfx = new QSoundEffect();
    sfx->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/assets/sounds/magnetOFF.wav"));
    sounds.insert("magnetOff", sfx);

    sfx = new QSoundEffect();
    sfx->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/assets/sounds/lever-on.wav"));
    sounds.insert("leverOn", sfx);

    sfx = new QSoundEffect();
    sfx->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/assets/sounds/lever-on.wav"));
    sounds.insert("leverOff", sfx);

    sfx = new QSoundEffect();
    sfx->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/assets/sounds/slap.wav"));
    sounds.insert("crash", sfx);*/
}

/**
 * @brief Sounds::toggleMute
 */
void Sounds::toggleMute()
{
    muted = !muted;
    player->setMuted(muted);
}

/**
 * @brief Sounds::isMuted
 * @return
 */
bool Sounds::isMuted()
{
    return muted;
}
