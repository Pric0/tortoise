#include "tortoise.h"

Tortoise::Tortoise(QQmlApplicationEngine *engine, QObject *parent) : QObject(parent)
{
    audioPlayer = new AudioPlayer(this);
    dbaseManager.setParent(this);

    this->engine = engine;
    this->engine->rootContext()->setContextProperty(
                "dbaseManager", &dbaseManager);
    this->engine->rootContext()->setContextProperty(
                "mainWin", this);

    viewerModel = new ViewerModel(this);
    viewerArtistModel = new ViewerArtistsModel(this);

    this->engine->rootContext()->setContextProperty(
                "viewerModel", viewerModel);
    this->engine->rootContext()->setContextProperty(
                "viewerArtistsModel", viewerArtistModel);

    connect(&dbaseManager, SIGNAL(dataChanged()),
            this, SLOT(changeModelData())
            );
    connect(&dbaseManager, SIGNAL(artistsDataChanged()),
            this, SLOT(changeArtistsModelData())
            );
    connect(&dbaseManager, SIGNAL(statusChanged(const QString&)),
            this, SLOT(setStatus(const QString&))
            );

    connect(viewerModel, SIGNAL(playFile(const QUrl&)),
            this, SLOT(playFile(const QUrl&))
            );
    connect(viewerModel, SIGNAL(appendToPlaylist(const QList<ItemTrack*> &)),
            audioPlayer->playlist, SLOT(appendTrack(const QList<ItemTrack*> &))
            );

    this->engine->rootContext()->setContextProperty(
                "audioPlayer", audioPlayer);
    this->engine->rootContext()->setContextProperty(
                "playlistModel", audioPlayer->playlist);
}

QString Tortoise::getStatus() const
{
    return m_status;
}

void Tortoise::setStatus(const QString &status)
{
    m_status = status;
    emit statusChanged();
}

void Tortoise::playFile(const QUrl &filename)
{
    audioPlayer->playlist->setTrack(filename);
    audioPlayer->play();
}

void Tortoise::changeModelData()
{
    viewerModel->setDataSource(
                dbaseManager.getSelectedController()
                );
}

void Tortoise::changeArtistsModelData()
{
    viewerArtistModel->setDataSource(
                dbaseManager.getSelectedController()
                );
}
