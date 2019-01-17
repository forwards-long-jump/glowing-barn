#ifndef SOUNDS_H
#define SOUNDS_H

#include <QMediaPlayer>
#include <QSoundEffect>
#include <QString>
#include <QCoreApplication>

#include "soundeffectthread.h"

/**
 * Handles sounds
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class Sounds
{
public:
    static void playMusic(QString path);
    static void playSound(QString name);

    static void fadeOut(int duration_, QString nextMusic = "");

    static void setMediaPlayer(QMediaPlayer* player);

    static void update();
    static void loadSounds();
    static void toggleMute();
    static bool isMuted();
private:
    static QMediaPlayer* player;
    static QMap<QString, QSoundEffect*> sounds;

    static SoundEffectThread* magnetOn;
    static SoundEffectThread* magnetOff;

    static int fadeOutTick;
    static int fadeoutDuration;
    static bool muted;

    static QString nextMusic;

};

#endif // SOUNDS_H
