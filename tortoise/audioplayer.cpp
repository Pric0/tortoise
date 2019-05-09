#include "audioplayer.h"

AudioPlayer::AudioPlayer(QObject *parent) : QObject(parent)
{
    process.setParent(this);
//    process.setProcessChannelMode(QProcess::MergedChannels);
    process.setReadChannel(QProcess::StandardError);

    playlist = new PlaylistModel(this);

    connect (&process, SIGNAL( readyReadStandardError()),
             this, SLOT(readyRead())
             );
    connect (&process, SIGNAL(stateChanged(QProcess::ProcessState)),
             this, SLOT(stateChanged(QProcess::ProcessState))
             );

    connect(this, SIGNAL(next()),
            playlist, SLOT(playNext())
            );
    connect(this, SIGNAL(prev()),
            playlist, SLOT(playPrev())
            );
    connect(playlist, SIGNAL(playCurrent()),
            this, SLOT(play())
            );
}

void AudioPlayer::play(const int &pos)
{
//    qDebug() << "play" << pos << duration << playlist->getCurrentFilename();

    if(process.state() != QProcess::NotRunning)
        stop();

    if(playlist->getCurrentItem()->getFilename().isEmpty())
        return;

    QString program = "ffplay";
    QStringList arguments;
    if(pos != 0) {
        setPosition(pos-1);
        arguments << "-ss" << QString::number(pos);
    } else {
        emit currentTrackChanged();
    }

    arguments << "-nodisp" /*<< "-autoexit"*/ << "-vn" << "-sn"
              << "-i" << playlist->getCurrentItem()->getFilename().toLocalFile();

    process.setParent(this);
    process.start(program, arguments, QIODevice::ReadOnly);
    process.waitForStarted(-1);
}

void AudioPlayer::unpause()
{
    play(position);
}

void AudioPlayer::stop()
{
    process.kill();
    process.waitForFinished(-1);
}

void AudioPlayer::readyRead()
{    
    QString out = process.readLine();
//    qDebug() << "AudioPlayer::readyRead" << out;

    if(out.count('\r') > 2)
        out = out.section('\r', -2,-2);
    else
        out = out.section('\r', 0, 0);

    while (out.startsWith(' '))
        out.remove(0,1);

    processData(out);

    if(process.bytesAvailable())
        emit readyRead();
}

void AudioPlayer::processData(const QString &out)
{
    if(out.contains("M-A")) {
        setPosition(out.left(out.indexOf('.')).toInt());
        return;
    }

    if(out.startsWith("Duration: ")) {
        int index = out.indexOf("Duration: ");
        QStringList durationList = out.mid(index+10, 11).split(':');
        int totalDuration = durationList[0].toInt() * 360 +
                            durationList[1].toInt() * 60 +
                            durationList[2].section('.',0,0).toInt();
        setDuration(totalDuration);
        return;
    }
}

void AudioPlayer::stateChanged(QProcess::ProcessState newState)
{
    switch (newState) {
    case QProcess::Running:
        setIsPlaying(true);
        break;
    case QProcess::NotRunning:
        setIsPlaying(false);
        break;
    default:
        break;
    }
}

QObject *AudioPlayer::getCurrentTrack() const
{
    return (QObject*)playlist->getCurrentItem();
}

int AudioPlayer::getPosition() const
{
    return position;
}

void AudioPlayer::setPosition(int value)
{
    if(value == position)
        return;

    if(value == 0) {
        position = value;
        return;
    }

    if( duration == value) {
        stop();
        setDuration(0);
        next();
        return;
    }

    position = value;
    emit positionChanged();
}

int AudioPlayer::getDuration() const
{
    return duration;
}

void AudioPlayer::setDuration(int value)
{
    if(value == 0) {
        position = 0;
        emit positionChanged();
    }

    duration = value;
    emit durationChanged();
}

bool AudioPlayer::getIsPlaying() const
{
    return isPlaying;
}

void AudioPlayer::setIsPlaying(bool value)
{
    isPlaying = value;
    emit isPlayingChanged();
}
