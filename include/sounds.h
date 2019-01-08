#ifndef SOUNDS_H
#define SOUNDS_H

#include <QMediaPlayer>
#include <QSoundEffect>
#include <QString>
#include <QCoreApplication>

// TODO: Use a ResourceLocator if times allows it
class Sounds
{
public:
    static void playMusic(QString path);
    static void playSound(QString name);

    static void fadeOut(int duration_, QString nextMusic = "");

    static void setMediaPlayer(QMediaPlayer* player);

    static void update();
    static void loadSounds();
private:
    static QMediaPlayer* player;
    static QMap<QString, QSoundEffect*> sounds;

    static int fadeOutTick;
    static int fadeoutDuration;

    static QString nextMusic;
};

#endif // SOUNDS_H
