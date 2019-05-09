#include "itemtrack.h"
#include "tagsource.h"

#include <QDebug>

ItemTrack::ItemTrack(const QString &artist,
                     const QString &album,
                     const int &id,
                     const int &num,
                     const QString &trackname,
                     const QUrl &filename,
                     const QString &genres,
                     const int &albumId,
                     const int &albumTrackCount,
                     const QString &cover,
                     QObject *parent) : QObject(parent)
{
    m_artist    = artist;
    m_album     = album;
    m_id        = id;
    m_num       = num;
    m_trackname = trackname;
    m_filename  = filename;
    m_genres    = genres;
    m_albumId   = albumId;
    m_albumTrackCount = albumTrackCount;

    if(!cover.isEmpty()) {
        QDir dir("./buffered/");
        dir.makeAbsolute();
        m_albumCover = QUrl::fromLocalFile(dir.path() + '/' + cover);
    }
}

ItemTrack::ItemTrack(const QUrl &filename)
{
    QMap<QString, QVariant> tags = TagSource::getTagsFromFile(filename.toLocalFile());

    m_artist    = tags["artistName"].toString();
    m_album     = tags["albumTitle"].toString();
    m_num       = tags["trackNum"].toInt();
    m_trackname = tags["trackName"].toString();
    m_filename  = filename;
    m_genres    = tags["genres"].toString();

    if(tags.contains("cover")) {
        QDir dir("./buffered/");
        dir.makeAbsolute();
        m_albumCover= QUrl::fromLocalFile(dir.path() + '/' +tags["cover"].toString());
    }
}

ItemTrack::ItemTrack()
{
}

int ItemTrack::getId() const
{
    return m_id;
}

int ItemTrack::getNum() const

{
    return m_num;
}

bool ItemTrack::getSelected() const
{
    return m_selected;
}

void ItemTrack::setSelected(bool selected)
{
    m_selected = selected;
    emit selectedChanged();
}

QUrl ItemTrack::getAlbumCover() const
{
   return m_albumCover;
}

int ItemTrack::getAlbumId() const
{
    return m_albumId;
}

int ItemTrack::getAlbumTrackCount() const
{
    return m_albumTrackCount;
}

QString ItemTrack::getArtist() const
{
    return m_artist;
}

QString ItemTrack::getAlbum() const
{
    return m_album;
}

QString ItemTrack::getTrackname() const
{
    return m_trackname;
}

QUrl ItemTrack::getFilename() const
{
    return m_filename;
}

QString ItemTrack::getGenres() const
{
    return m_genres;
}
