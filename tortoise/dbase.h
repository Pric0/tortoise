#ifndef DBASEMANAGER_H
#define DBASEMANAGER_H

#include <QObject>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

#include "tagsource.h"

#include <QDebug>
#include <QtDebug>

#include <QFile>

class DBase : public QObject
{
    Q_OBJECT
public:
    explicit DBase(QObject *parent = nullptr);
    ~DBase() {
        closeDB();
    }

    void closeDB();

    static bool makeDB(const QString &filename, const bool deleteExist);
    void addFile(const QString &parameter, const QStringList &verifyList, const QSqlDatabase &dbase);
    static void removeFile(const QList<int> &list, const QSqlDatabase &dbase);

    void addFile(const QString &parameter, const QStringList &fileList);

signals:
    void statusChanged(const QString &status);
    void dataChanged(QSqlQuery *query, const int &count);
    void artistsListChanged(QSqlQuery *query, const int &count);

public slots:
    void openDB(const QString &filename);
    void indexDir(const QString &parameter);
    void updateData(const QString &searchFilter = "", const QString &artistFilter = "");
    void updateArtistsList();

private:
    bool firstSearch = true,
         block = false;
    QSqlDatabase m_dbase;
    QSqlQuery m_currentQuery;

};

#endif // DBASEMANAGER_H
