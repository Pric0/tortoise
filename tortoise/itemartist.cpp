#include "itemartist.h"

ItemArtist::ItemArtist(QString name, int albumcount, QObject *parent) : QObject(parent)
{
    m_name = name;
    m_albumcount = albumcount;
}

QString ItemArtist::getName() const
{
    return m_name;
}

int ItemArtist::getAlbums() const
{
    return m_albumcount;
}
