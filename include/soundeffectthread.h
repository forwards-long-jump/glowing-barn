#ifndef SOUNDEFFECTTHREAD_H
#define SOUNDEFFECTTHREAD_H

#include <QThread>
#include <QSoundEffect>
#include <QCoreApplication>

/**
 * Thread whose purpose is to play a sound.
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class SoundEffectThread : public QThread
{

    Q_OBJECT

public:
    SoundEffectThread();
    ~SoundEffectThread();

    void init(QString);

private:
    void run() override;

private:
    QSoundEffect* sfx;
};

#endif // SOUNDEFFECTTHREAD_H
