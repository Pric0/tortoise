#include "dbasecontroller.h"

DBaseController::DBaseController(QString folder, QObject *parent) : QObject(parent)
{
    m_folder = folder;

    DBase *worker = new DBase;
    worker->openDB(m_folder + "/index.db");

    worker->moveToThread(&thread);
    connect(&thread, &QThread::finished, worker, &QObject::deleteLater);
    connect(worker, &DBase::statusChanged, this, &DBaseController::setNewStatus);
    connect(this, &DBaseController::startScan, worker, &DBase::indexDir);
    connect(worker, &DBase::dataChanged, this, &DBaseController::setNewData);
    connect(worker, &DBase::artistsListChanged, this, &DBaseController::setArtistsData);
    connect(this, &DBaseController::search, worker, &DBase::updateData);
    thread.start();

    emit statusChanged("Поиск");
    emit search();
}

QString DBaseController::getName() const
{
    return m_folder.section('/', -1);
}

ItemTrack *DBaseController::itemAt(const int &row)
{
    if(m_data == nullptr)
        return new ItemTrack;

    if(!(m_data->isActive() && m_data->isSelect()))
        return new ItemTrack;

    if(buffer.contains(row))
        return buffer.value(row);

    m_data->seek(row);
    QUrl filepath;
    if(!m_folder.isEmpty())
        filepath = QUrl::fromLocalFile(
                    m_folder + '/' + m_data->value(5).toString()
                    );
    else
        filepath = QUrl::fromLocalFile(
                    m_data->value(5).toString()
                    );

    ItemTrack* track = new ItemTrack(m_data->value(0).toString(),
                         m_data->value(1).toString(),
                         m_data->value(2).toInt(),
                         m_data->value(3).toInt(),
                         m_data->value(4).toString(),
                         filepath,
                         m_data->value(6).toString(),
                         m_data->value(7).toInt(),
                         m_data->value(9).toInt(),
                         m_data->value(8).toString()
                         );

    orderList.push_back(row);
    if(orderList.size() > 340)
        buffer.remove(orderList.takeFirst());

    buffer.insert(row, track);

    return track;
}

int DBaseController::count() const
{
    return m_count;
}

ItemArtist *DBaseController::artistAt(const int &row) const
{
    if(m_artistsData == nullptr)
        return new ItemArtist("Error", -1);

    if(!(m_artistsData->isActive() && m_artistsData->isSelect()))
        return new ItemArtist("Error", -1);

    m_artistsData->seek(row);

    QString name;
    if(m_artistsData->value(0).isNull())
        name = "NULL";
    else
        name = m_artistsData->value(0).toString();

    return new ItemArtist(name, m_artistsData->value(1).toInt());
}

int DBaseController::artistsCount() const
{
    return m_artistsCount;
}

QString DBaseController::getFolder() const
{
    return m_folder;
}

void DBaseController::scanDir()
{
    emit statusChanged("Сканирую: " + m_folder);
    emit startScan(m_folder);
}

void DBaseController::updateData(const QString &searchFilter, const QString &artistFilter)
{
    m_searchFilter = searchFilter;
    m_artistFilter = artistFilter;

    buffer.clear();
    orderList.clear();

    emit search(searchFilter, artistFilter);
}

void DBaseController::setNewData(QSqlQuery *query, const int &count)
{
    m_count = count;
    m_data  = query;
    emit dataChanged();
}

void DBaseController::setArtistsData(QSqlQuery *query, const int &count)
{
    m_artistsCount = count;
    m_artistsData  = query;
    emit artistDataChanged();
}

QString DBaseController::getStatus() const
{
    return m_status;
}

QString DBaseController::getArtistFilter() const
{
    return m_artistFilter;
}

void DBaseController::setNewStatus(const QString &status)
{
    m_status = status;
    emit statusChanged(status);
}

QString DBaseController::getSearchFilter() const
{
    return m_searchFilter;
}

void DBaseController::setArtistFilter(const QString &artistFilter)
{
    m_artistFilter = artistFilter;

    buffer.clear();
    orderList.clear();

    emit search(m_searchFilter, m_artistFilter);
}

void DBaseController::setSearchFilter(const QString &searchFilter)
{
    m_searchFilter = searchFilter;

    buffer.clear();
    orderList.clear();

    emit search(m_searchFilter, m_artistFilter);
}
