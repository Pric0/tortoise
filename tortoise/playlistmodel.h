#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractListModel>
#include <QObject>

#include <QDebug>

#include "itemtrack.h"

class PlaylistModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit PlaylistModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::UserRole) const override;

    ItemTrack* getCurrentItem() const;
    Q_INVOKABLE void clearModel();

    void setTrack(const QUrl &filename);

public slots:
    void playNext();
    void playPrev();
    void playTrack(const int &row);
    void appendTrack(const QList<ItemTrack*> &filename);
    void appendTrack(const QList<QUrl> &fileurl);

signals:
    void playCurrent();

private:
    QList<ItemTrack *> m_playlist;
    int currentTrack = -1;
    QList<int> m_selectedList;

    enum Roles {
        modelData     = Qt::UserRole,
        selectedRole  = Qt::UserRole + 1,
        currentRole   = Qt::UserRole + 2
    };
};

#endif // PLAYLISTMODEL_H
