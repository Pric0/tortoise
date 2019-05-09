#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>
#include <QProcess>
#include <QUrl>

#include "playlistmodel.h"

#include <QDebug>

class AudioPlayer : public QObject
{
    Q_OBJECT
public:
    explicit AudioPlayer(QObject *parent = nullptr);
    ~AudioPlayer() {
        stop();
    }

    Q_INVOKABLE void unpause();
    Q_INVOKABLE void stop();

    Q_PROPERTY(bool isPlaying READ getIsPlaying WRITE setIsPlaying NOTIFY isPlayingChanged)
    bool getIsPlaying() const;
    void setIsPlaying(bool value);

    Q_PROPERTY(int duration READ getDuration NOTIFY durationChanged)
    int getDuration() const;
    void setDuration(int value);

    Q_PROPERTY(int position READ getPosition NOTIFY positionChanged)
    int getPosition() const;
    void setPosition(int value);

    Q_PROPERTY(QObject* currentTrack READ getCurrentTrack NOTIFY currentTrackChanged)
    QObject* getCurrentTrack() const;

    PlaylistModel *playlist;

signals:
    void isPlayingChanged();
    void durationChanged();
    void positionChanged();
    void filenameChanged();
    void artistChanged();
    void titleChanged();
    void currentTrackChanged();

    void next();
    void prev();

public slots:
    void play(const int &pos = 0);
    void readyRead();
    void stateChanged(QProcess::ProcessState newState);

private:
    QProcess process;
    bool isPlaying = false,
         autoNext = false;
    int duration = 0,
        position = 0;

    void processData(const QString &out);

    QString title, artist;
};

#endif // AUDIOPLAYER_H
