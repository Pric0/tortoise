#include "playlistmodel.h"

PlaylistModel::PlaylistModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

QHash<int, QByteArray> PlaylistModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[modelData]    = "modelData";
    roles[selectedRole] = "isSelected";
    roles[currentRole]  = "isCurrent";
    return roles;
}

int PlaylistModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_playlist.count();
}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == modelData)
        return QVariant::fromValue(
                    m_playlist.at(index.row())
                    );

    if(role == selectedRole)
        return m_selectedList.contains(index.row());

    if(role == currentRole)
        return index.row() == currentTrack;

    return QVariant();
}

void PlaylistModel::appendTrack(const QList<ItemTrack *> &filename)
{
    beginInsertRows(QModelIndex(), m_playlist.count(), m_playlist.count()+filename.count()-1);
    for(auto item: filename)
        m_playlist.append(item);
    endInsertRows();

    if(m_playlist.count() == filename.count())
        playNext();
}

void PlaylistModel::appendTrack(const QList<QUrl> &fileurl)
{
    QList<ItemTrack *> list;
    for(auto url: fileurl)
        list << new ItemTrack(url);

    appendTrack(list);
}

ItemTrack *PlaylistModel::getCurrentItem() const
{
    if(!m_playlist.isEmpty())
        return m_playlist.at(currentTrack);
    else
        return new ItemTrack;
}

void PlaylistModel::clearModel()
{
    beginResetModel();
    currentTrack = -1;
    m_playlist.clear();
    endResetModel();
}

void PlaylistModel::setTrack(const QUrl &filename)
{
    clearModel();

    appendTrack(QList<ItemTrack*>() << new ItemTrack(filename));
}

void PlaylistModel::playNext()
{
    if( (currentTrack + 1) >= m_playlist.count() )
        return;

    currentTrack++;
    emit dataChanged(
                index(currentTrack-1),
                index(currentTrack),
                QVector<int>() << currentRole);

    emit playCurrent();
}

void PlaylistModel::playPrev()
{
    if( (currentTrack - 1) < 0 )
        return;

    currentTrack--;
    emit dataChanged(
                index(currentTrack),
                index(currentTrack+1),
                QVector<int>() << currentRole);

    emit playCurrent();
}

void PlaylistModel::playTrack(const int &row)
{
    int tmp = currentTrack;
    currentTrack = row;

    emit playCurrent();

    emit dataChanged(
                index(tmp),
                index(tmp),
                QVector<int>() << currentRole);
    emit dataChanged(
                index(currentTrack),
                index(currentTrack),
                QVector<int>() << currentRole);
}


