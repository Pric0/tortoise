#ifndef TORTOISE_H
#define TORTOISE_H

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QObject>
#include <QThread>
#include <QUrl>


#include <QDebug>

#include "dbasemanager.h"
#include "viewermodel.h"
#include "viewerartistsmodel.h"
#include "audioplayer.h"

class Tortoise : public QObject
{
    Q_OBJECT
public:
    explicit Tortoise(QQmlApplicationEngine *engine, QObject *parent = nullptr);
    ~Tortoise() {
    }

    Q_PROPERTY(QString status READ getStatus NOTIFY statusChanged)
    QString getStatus() const;

signals:
    void statusChanged();

public slots:
    void changeModelData();
    void changeArtistsModelData();
    void setStatus(const QString &status);
    void playFile(const QUrl &filename);

private:
    QQmlApplicationEngine *engine;
    DBaseManager dbaseManager;
    ViewerModel *viewerModel;
    ViewerArtistsModel * viewerArtistModel;

    AudioPlayer *audioPlayer;

    QString m_status = "Запущено";
};

#endif // TORTOISE_H
