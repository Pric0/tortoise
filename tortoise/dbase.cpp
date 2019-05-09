#include "dbase.h"
#include <QMultiMap>

DBase::DBase(QObject *parent) : QObject(parent)
{
}

bool DBase::makeDB(const QString &filename, const bool deleteExist)
{
    if(QFile::exists(filename)) {
        if(deleteExist) {
            QFile::remove(filename);
        } else {
            qCritical("File '%s' already exists!", qUtf8Printable(filename));
            return false;
        }
    }

    // Создание файла для БД
    QFile sqliteFile(filename);
    if(!sqliteFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qCritical("File '%s' does not open!", qUtf8Printable(filename));
        return false;
    }
    sqliteFile.write("");
    sqliteFile.close();


    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE", "newDB");
    dbase.setDatabaseName(filename);
    if (!dbase.open()) {
        qCritical("Database '%s' does not open!", qUtf8Printable(filename));
        dbase.close();
        QSqlDatabase::removeDatabase("newDB");
        return false;
    }

    QFile sqlScheme(":/schema.sql");
    sqlScheme.open(QIODevice::ReadOnly | QIODevice::Text);
    QString str = sqlScheme.readAll().replace('\n', ' ');
    sqlScheme.close();

    // DDL query
    for(int i = 0; i < str.count(';'); ++i) {
        if ( !QSqlQuery(dbase).exec(str.section(';', i, i)) ) {
            qCritical("Can't make new Table in Database.");
            dbase.close();
            QSqlDatabase::removeDatabase(dbase.connectionName());
            return false;
        }
    }

    dbase.close();
    QSqlDatabase::removeDatabase(dbase.connectionName());
    return true;

}

void DBase::openDB(const QString &filename)
{
    if(m_dbase.isOpen())
        return;

    m_dbase = QSqlDatabase::addDatabase("QSQLITE", filename);

    m_dbase.setDatabaseName(filename);

    if (!m_dbase.open()) {
        qCritical("Database '%s' does not open!", qUtf8Printable(filename));
        closeDB();
        return;
    }

    if(QFile(filename).size() == 0) {
        qDebug() << "!!!!!!!!!!!!!!" << filename.section('/', 0, -2);
//        emit indexDir(filename.section('/', 0, -2));
    }

}

void DBase::closeDB()
{
    m_currentQuery.clear();

    if(m_dbase.isOpen())
        m_dbase.close();

    if(QSqlDatabase::contains(m_dbase.connectionName()))
        QSqlDatabase::removeDatabase(m_dbase.connectionName());
}

void DBase::addFile(const QString &parameter, const QStringList &verifyList, const QSqlDatabase &dbase)
{
    if(!dbase.isOpen())
        return;

    QSqlQuery query(dbase);
    QMap<int, int> insertedTracksAlbumIds,
                   updatedArtistIds;
    QHash<QString, QMap<QString, QVariant>> dataList;

    // Считывание тегов
    for(auto track : verifyList) {
        dataList[track] = TagSource::getTagsFromFile(parameter + track);
        dataList[track]["artistId"] = -1;
        dataList[track]["albumId"] = -1;
        dataList[track]["genreId"] = 1;
    }

    emit statusChanged("Поиск новых артистов в БД");

    // Поиск новых артистов в БД
    // -----------------------------------------------------------------
    {
        QStringList artistsName;

        for(auto track : verifyList) {
            const QString artistName = dataList[track]["artistName"].toString();
            if(!artistName.isEmpty()) {
                query.exec("SELECT Id FROM artists WHERE Name = '" +
                           artistName + "';");

                if(query.first())
                    dataList[track]["artistId"] = query.value(0);
                else
                    if(!artistsName.contains(artistName))
                        artistsName << artistName;
            } else {
                dataList[track]["artistId"] = 1;
            }

        }

        if(!artistsName.isEmpty()) {
            QString insertQuery = "INSERT INTO artists(Name) VALUES";
            for(auto artistName: artistsName) {
                if(artistName.contains('\''))
                    artistName = artistName.replace("'", "\\'");

                insertQuery.append(" (\"" + artistName + "\"),");
            }

            query.exec(insertQuery.chopped(1).append(';'));
            qDebug() << insertQuery.chopped(1).append(';');

        }

        for(auto track : verifyList) {
            if(dataList[track]["artistId"].toInt() < 0) {
                query.exec("SELECT Id FROM artists WHERE Name = \"" +
                           dataList[track]["artistName"].toString() + "\";");

                if(query.first())
                    dataList[track]["artistId"] = query.value(0);
                else
                    dataList[track]["artistId"] = 1;
            }

        }

    }

    emit statusChanged("Поиск альбома у артиста");

    // Поиск альбома у артиста
    // -----------------------------------------------------------------
    {
        QMultiMap<QString, QString> albumsTitle;

        for(auto track : verifyList) {
            QString albumTitle = dataList[track]["albumTitle"].toString();
            if(!albumTitle.isEmpty()) {
                const QString artistId = QString::number(dataList[track]["artistId"].toInt());
                query.exec("SELECT Id FROM albums WHERE Title = '" +
                           albumTitle + "' AND "
                           "ArtistId = " + artistId + ";");

                if(query.first()) {
                    dataList[track]["albumId"] = query.value(0);
                } else {
                    if(!albumsTitle.contains(artistId, albumTitle))
                        albumsTitle.insert(artistId, albumTitle);
                    if(!updatedArtistIds.contains(dataList[track]["artistId"].toInt()))
                        updatedArtistIds.insert(dataList[track]["artistId"].toInt(), 0);
                }
            } else {
                dataList[track]["albumId"] = 1;
            }

        }

        if(!albumsTitle.isEmpty()) {
            QString insertQuery = "INSERT INTO albums(ArtistId, Title) VALUES";
            QMultiMap<QString, QString>::iterator i = albumsTitle.begin();
            while (i != albumsTitle.end()) {
                insertQuery.append(" ('" + i.key() + "', '" + i.value()+ "'),");
                ++i;
            }

            query.exec(insertQuery.chopped(1).append(';'));

        }

        for(auto track : verifyList) {
            if(dataList[track]["albumId"].toInt() < 0) {
                query.exec("SELECT Id FROM albums WHERE "
                           "Title = '" + dataList[track]["albumTitle"].toString() + "' AND "
                           "ArtistId = " + QString::number(dataList[track]["artistId"].toInt()) + ";");

                if(query.first())
                    dataList[track]["albumId"] = query.value(0);
                else
                    dataList[track]["albumId"] = 1;
            }
        }
    }

    emit statusChanged("Поиск жанра в БД");
    // Поиск жанра в БД
    // -----------------------------------------------------------------
    {

    }

    emit statusChanged("Добавление треков в БД");
    // Добавление треков в БД
    // -----------------------------------------------------------------
    {
        QString insertQuery = "INSERT INTO"
                             " tracks (Num, Name, AlbumId, GenreId, Filename, CoverFile) "
                             "VALUES";
        const QString valuesTemplate = " (%1, \"%2\", %3, %4, \"%5\", \"%6\"),";

        auto i = dataList.constBegin();
        while (i != dataList.constEnd()) {
            if(!insertedTracksAlbumIds.contains( (i.value()["albumId"]).toInt() )) {
                insertedTracksAlbumIds.insert( (i.value()["albumId"]).toInt(), 0 );
            }

            insertQuery.append(valuesTemplate
                               .arg((i.value()["trackNum"]).toInt())
                               .arg((i.value()["trackName"]).toString())
                               .arg((i.value()["albumId"]).toInt())
                               .arg((i.value()["genreId"]).toInt())
                               .arg(i.key()) // filename
                               .arg((i.value()["cover"]).toString())
                              );
            ++i;
        }

        query.exec(insertQuery.chopped(1).append(';'));

    }

    emit statusChanged("Обновление информации albums::TracksCount");
    // Обновление информации albums::TracksCount
    // -----------------------------------------------------------------
    {
        auto i = insertedTracksAlbumIds.begin();
        while (i != insertedTracksAlbumIds.end()) {
            query.exec("SELECT COUNT(Id) FROM tracks"
                       " WHERE AlbumId = " + QString::number(i.key()) + ";");

            if(query.first())
                *i = query.value(0).toInt(); // :)

            ++i;
        }

        i = insertedTracksAlbumIds.begin();
        while (i != insertedTracksAlbumIds.end()) {
            query.exec("UPDATE albums"
                       " SET TracksCount = " + QString::number(i.value()) +
                       " WHERE Id = " + QString::number(i.key()) + ";");

            ++i;
        }
    }

    emit statusChanged("Обновление информации artists::AlbumsCount");
    // Обновление информации artists::AlbumsCount
    // -----------------------------------------------------------------
    {
        auto i = updatedArtistIds.begin();
        while (i != updatedArtistIds.end()) {
            query.exec("SELECT COUNT(Id) FROM albums WHERE ArtistId = " +
                       QString::number(i.key()));

            if(query.first())
                *i = query.value(0).toInt(); // :)

            ++i;
        }

        i = updatedArtistIds.begin();
        while (i != updatedArtistIds.end()) {
            query.exec("UPDATE artists"
                       " SET AlbumsCount = " + QString::number(i.value()) +
                       " WHERE Id = " + QString::number(i.key()) + ";");

            ++i;
        }
    }

    emit statusChanged("Добавлено" + QString::number(verifyList.count()));

    return;
}

void DBase::removeFile(const QList<int> &list, const QSqlDatabase &dbase)
{
    if(!dbase.isOpen())
        return;

    QSqlQuery query(dbase);
    QList<int> albumIds, genreIds, artistIds;

    for(auto trackId : list) {
        query.exec("SELECT AlbumId, GenreId FROM tracks WHERE Id = " +
                   QString::number(trackId) + ";");

        query.first();
        if(!albumIds.contains( query.value(0).toInt() ))
            albumIds << query.value(0).toInt();
        if(!genreIds.contains( query.value(1).toInt() ))
            genreIds << query.value(1).toInt();

        // DDL query
        if ( !QSqlQuery(dbase).exec("DELETE FROM tracks WHERE Id = " +
                                      QString::number(trackId) + ";") ) {
            qCritical("Can't remove from Database!");
            return;
        }
    }

    for(auto genreId: genreIds) {
        if(genreId == 1)
            continue;

        query.exec("SELECT COUNT(Id) FROM tracks WHERE GenreId = " +
                   QString::number(genreId) + ";");

        query.first();
        if(query.value(0).toInt() <= 0) {
            query.exec("DELETE FROM genres WHERE Id = " +
                       QString::number(genreId) + ";");
        }

    }

    for(auto albumId: albumIds) {
        if(albumId == 1)
            continue;

        query.exec("SELECT ArtistId FROM albums WHERE Id = " +
                   QString::number(albumId) + ";");
        query.first();
        if(!artistIds.contains(query.value(0).toInt()))
            artistIds << query.value(0).toInt();

        query.exec("SELECT COUNT(Id) FROM tracks WHERE AlbumId = " +
                   QString::number(albumId) + ";");

        query.first();
        int tracksCount = query.value(0).toInt();

        if(tracksCount <= 0) {
            query.exec("DELETE FROM albums WHERE Id = " +
                       QString::number(albumId) + ";");
        } else {
            query.exec("UPDATE albums"
                        " SET TracksCount = " + QString::number(tracksCount) +
                        " WHERE Id = " + QString::number(albumId) + ";");
        }

    }

    for(auto artistId: artistIds) {
        if(artistId == 1)
            continue;

        query.exec("SELECT COUNT(Id) FROM albums WHERE ArtistId = " +
                   QString::number(artistId) + ";");

        query.first();

        int albumsCount = query.value(0).toInt();
        if(albumsCount <= 0) {
            query.exec("DELETE FROM artists WHERE Id = " +
                       QString::number(artistId) + ";");
        } else {
            query.exec("UPDATE artists"
                        " SET AlbumsCount = " + QString::number(albumsCount) +
                        " WHERE Id = " + QString::number(artistId) + ";");
        }
    }

    return;
}

void DBase::addFile(const QString &parameter, const QStringList &fileList)
{
    if(!m_dbase.isOpen())
        return;

    addFile(parameter, fileList, m_dbase);
    updateArtistsList();
}

void DBase::indexDir(const QString &parameter)
{
    block = true;
    emit dataChanged(nullptr, 0);
    emit artistsListChanged(nullptr, 0);

    QStringList *filelist = new QStringList;

    closeDB();
    makeDB(parameter + "/index.db", true);
    openDB(parameter + "/index.db");

    QStringList nameFilters;
    nameFilters << "*.mp3";

    emit statusChanged("Поиск в каталоге: " + parameter);
    int totalCount = 0,
        filesCount = 0;
    QStringList folders, files;
    folders << parameter;

    while (!folders.isEmpty()) {
        QString folder = folders.takeLast();
        QDir currentDir(folder);

        files = currentDir.entryList(nameFilters, QDir::Files);
        for(auto file: files) {
            QString relativepath = folder + '/' + file;
            relativepath = relativepath.remove(0, parameter.length() + 1);
            filelist->append(relativepath);
        }
        filesCount += files.count();
        files.clear();

        QStringList curFolderList =
                currentDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

        for(auto childFolder: curFolderList) {
            folders << folder + '/' + childFolder;
        }

        emit statusChanged( QString("Найдено: %1 файлов").arg(totalCount + filesCount) );
        if(filesCount >= 500) {
            emit statusChanged( QString("Добавляю в БД (%1): %2 файлов")
                                .arg(totalCount).arg(filesCount) );
            if(filesCount > 600) {
                QStringList *tmpList = new QStringList;
                int tmpCount = 0;
                for(auto filename: *filelist) {
                    tmpList->append(filename);
                    tmpCount++;
                    if(tmpCount >= 500) {
                        addFile(parameter+'/', *tmpList, m_dbase);
                        tmpCount = 0;
                        tmpList->clear();
                    }
                }
            } else {
                addFile(parameter+'/', *filelist, m_dbase);
            }
            filelist->clear();
            totalCount += filesCount;
            filesCount = 0;

            firstSearch = true;
            updateData();
        }
    }

    addFile(parameter+'/', *filelist, m_dbase);

    block = false;
    firstSearch = true;
    updateData();

    delete filelist;
}

void DBase::updateData(const QString &searchFilter, const QString &artistFilter)
{
    if(!m_dbase.isOpen())
        return;

    if(block)
        return;

    int count;
    QSqlQuery *query   = new QSqlQuery(m_dbase);

    QString select = "";
    if( (!searchFilter.isEmpty()) || (!artistFilter.isEmpty()) )
        select.append(" WHERE");

    if(!searchFilter.isEmpty()) {
        select.append( " (album LIKE '%" + searchFilter + "%'"
                       " OR trackname LIKE '%" + searchFilter + "%')"
                       );
        if(!artistFilter.isEmpty())
            select.append(" AND");
        else
            select.append(" OR artist LIKE '%" + searchFilter + "%'");
    }

    if(!artistFilter.isEmpty()) {
        if(artistFilter == "NULL")
            select.append( " artist IS NULL" );
        else
            select.append( " artist = '" + artistFilter + "'" );
    }

    if ( !(query->exec("SELECT COUNT(trackid) FROM TracksView" + select + ";")) ) {
        qCritical("Can't get count from Database!");
        return;
    }

    query->first();
    count = query->value(0).toInt();

    if(count < 1) {
        emit dataChanged(nullptr, 0);
//        emit artistsListChanged(nullptr, 0);
        return;
    } else {
        if ( !query->exec("SELECT * FROM TracksView" + select + " ORDER BY artist, album, tracknum;") ) {
            qCritical("Can't get list from Database!");
            return;
        }

        emit dataChanged(query, count);
    }

    // ------------ARTISTS-----------------
    if(!firstSearch)
        return;

    firstSearch = false;
    updateArtistsList();

}

void DBase::updateArtistsList()
{
    QSqlQuery *artists = new QSqlQuery(m_dbase);
    if ( !(artists->exec("SELECT COUNT(Id) FROM artists;")) ) {
        qCritical("Can't get count from Database!");
        return;
    }

    artists->first();
    int count = artists->value(0).toInt();

    if(count < 1) {
        emit artistsListChanged(nullptr, 0);
        return;
    } else {
        if ( !artists->exec("SELECT Name, AlbumsCount FROM artists ORDER BY Name;") ) {
            emit artistsListChanged(nullptr, 0);
            return;
        }

        emit artistsListChanged(artists, count);
    }
}
