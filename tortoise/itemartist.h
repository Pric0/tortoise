#ifndef ITEMARTIST_H
#define ITEMARTIST_H

#include <QObject>

class ItemArtist : public QObject
{
    Q_OBJECT
public:
    explicit ItemArtist(QString name, int albumcount, QObject *parent = nullptr);

    Q_PROPERTY(QString name READ getName NOTIFY nameChanged)
    QString getName() const;

    Q_PROPERTY(int albums READ getAlbums NOTIFY albumsChanged)
    int getAlbums() const;

signals:
    void nameChanged();
    void albumsChanged();

public slots:

private:
    QString m_name;
    int m_albumcount;
};

#endif // ITEMARTIST_H
