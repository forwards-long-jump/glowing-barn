#ifndef SOUNDS_H
#define SOUNDS_H

#include <QMediaPlayer>
#include <QSoundEffect>
#include <QString>

// TODO: Use a ResourceLocator if times allows it
class Sounds
{
public:
    static void playMusic(QString path);
    static void playSound(QString name);
    static void init();
    static void fadeOut(int duration_, QString nextMusic = "");
    static void update();
    static void loadSounds();
private:
    static QMediaPlayer player;
    static int fadeOutTick;
    static int fadeoutDuration;
    static QString nextMusic;
    static QMap<QString, QSoundEffect*> sounds;
    // TODO: Preload music as well
};

#endif // SOUNDS_H
