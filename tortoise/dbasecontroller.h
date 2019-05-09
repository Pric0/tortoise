#ifndef DBASECONTROLLER_H
#define DBASECONTROLLER_H

#include <QObject>
#include <QThread>
#include <QSqlQuery>
#include <QList>

#include "dbase.h"
#include "itemtrack.h"
#include "itemartist.h"

class DBaseController : public QObject
{
    Q_OBJECT
public:
    explicit DBaseController(QString folder, QObject *parent = nullptr);
    ~DBaseController() {
        thread.quit();
        thread.wait();
    }

    Q_PROPERTY(QString name READ getName NOTIFY nameChanged)

    QString getName() const;
    QString getFolder() const;

    ItemTrack *itemAt(const int &row);
    int count() const;

    ItemArtist *artistAt(const int &row) const;
    int artistsCount() const;

    void scanDir();
    void updateData(const QString &searchFilter = "", const QString &artistFilter = "");

    void setSearchFilter(const QString &searchFilter);
    void setArtistFilter(const QString &artistFilter);

    QString getSearchFilter() const;
    QString getArtistFilter() const;

    QString getStatus() const;

signals:
    void nameChanged();
    void statusChanged(const QString&);
    void startScan(const QString&);
    void search(const QString &searchFilter = "", const QString &artistFilter = "");
    void dataChanged();
    void artistDataChanged();

public slots:
    void setNewStatus(const QString& status);
    void setNewData(QSqlQuery *query, const int &count);
    void setArtistsData(QSqlQuery *query, const int &count);

private:
    QThread    thread;

    int        m_count = 0,
               m_artistsCount = 0;

    QSqlQuery *m_data           = nullptr,
              *m_artistsData    = nullptr;

    QString    m_folder,
               m_searchFilter,
               m_artistFilter,
               m_status;

    QMap<int, ItemTrack*> buffer;
    QList<int> orderList;
};

#endif // DBASECONTROLLER_H
