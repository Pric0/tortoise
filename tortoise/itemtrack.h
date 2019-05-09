#ifndef ITEMTRACK_H
#define ITEMTRACK_H

#include <QObject>
#include <QUrl>
#include <QDir>

class ItemTrack : public QObject
{
    Q_OBJECT
public:
    explicit ItemTrack(const QString &artist,
                       const QString &album,
                       const int &id,
                       const int &num,
                       const QString &trackname,
                       const QUrl &filename,
                       const QString &genres,
                       const int &albumId,
                       const int &albumTrackCount,
                       const QString &cover,
                       QObject *parent = nullptr);
    ItemTrack(const QUrl &filename);
    ItemTrack();

    Q_PROPERTY(int id READ getId NOTIFY idChanged)
    int getId() const;

    Q_PROPERTY(int num READ getNum NOTIFY numChanged)
    int getNum() const;

    Q_PROPERTY(QString artist READ getArtist NOTIFY artistChanged)
    QString getArtist() const;

    Q_PROPERTY(QString album READ getAlbum NOTIFY albumChanged)
    QString getAlbum() const;

    Q_PROPERTY(QString trackname READ getTrackname NOTIFY tracknameChanged)
    QString getTrackname() const;

    Q_PROPERTY(QUrl filename READ getFilename NOTIFY filenameChanged)
    QUrl getFilename() const;

    Q_PROPERTY(QString genres READ getGenres NOTIFY genresChanged)
    QString getGenres() const;

    Q_PROPERTY(int albumId READ getAlbumId NOTIFY albumIdChanged)
    int getAlbumId() const;

    Q_PROPERTY(int albumTrackCount READ getAlbumTrackCount NOTIFY albumTrackCountChanged)
    int getAlbumTrackCount() const;

    Q_PROPERTY(bool isSelected READ getSelected NOTIFY selectedChanged)
    bool getSelected() const;
    void setSelected(bool selected);

    Q_PROPERTY(QUrl albumCover READ getAlbumCover NOTIFY albumCoverChanged)
    QUrl getAlbumCover() const;

signals:
    void idChanged();
    void numChanged();
    void artistChanged();
    void albumChanged();
    void tracknameChanged();
    void filenameChanged();
    void genresChanged();
    void selectedChanged();
    void albumIdChanged();
    void albumTrackCountChanged();
    void albumCoverChanged();

public slots:

private:
    QUrl    m_filename,
            m_albumCover;
    QString m_artist,
            m_album,
            m_trackname,
            m_genres;

    int     m_id = 0,
            m_num = 0,
            m_albumId = 0,
            m_albumTrackCount = 0;

    bool    m_selected = false;
};

#endif // ITEMTRACK_H
