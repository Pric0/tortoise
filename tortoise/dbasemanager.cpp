#include "dbasemanager.h"

DBaseManager::DBaseManager(QObject *parent) : QObject(parent)
{
    loadDBPreset();

    if(m_dbaseList.count() > 0)
        select(0);
}

QList<QObject *> DBaseManager::getDbaseList() const
{
    QList<QObject *> dbaseList;
    dbaseList.reserve(m_dbaseList.count());
    for(auto i : m_dbaseList)
        dbaseList.append(i);
    return dbaseList;
}

int DBaseManager::getSelected() const
{
    return m_selected;
}

void DBaseManager::openFolder(const QUrl &folder, const bool &saveChanges)
{
    emit statusChanged("Добавляю каталог:" + folder.toLocalFile());

    for(int i = 0; i < m_dbaseList.count(); ++i) {
        if(m_dbaseList.at(i)->getFolder() == folder.toLocalFile()) {
            emit statusChanged("Данный каталог уже существует");
            select(i);
            return;
        }
    }

    if(!QFile::exists(folder.toLocalFile()))
        return;

    DBaseController* controller = new DBaseController(folder.toLocalFile());
    connect(controller, SIGNAL(statusChanged(const QString&)),
            SIGNAL(statusChanged(const QString&))
            );
    connect(controller, SIGNAL(dataChanged()),
            SIGNAL(dataChanged())
            );
    connect(controller, SIGNAL(artistDataChanged()),
            SIGNAL(artistsDataChanged())
            );

    m_dbaseList << controller;
    emit dbaseListChanged();

    select(m_dbaseList.count() - 1);

    if(saveChanges)
        saveDBPreset();
}

void DBaseManager::select(const int &index)
{
    if(m_dbaseList.count() <= 0) {
        m_selected = -1;
    } else if(index >= m_dbaseList.count()) {
        m_selected = m_dbaseList.count() - 1;
    } else
        m_selected = index;

    if(m_selected == -1) {
        emit statusChanged("Каталог не выбран");
        emit dataChanged();
        emit artistsDataChanged();
        return;
    } else {
        emit statusChanged("Выбран: " + getSelectedController()->getName());

        for(auto m_dbase: m_dbaseList)
            m_dbase->blockSignals(true);

        m_dbaseList.at(m_selected)->blockSignals(false);
    }

    emit statusChanged(m_dbaseList.at(m_selected)->getStatus());
    emit dataChanged();
    emit artistsDataChanged();
}

void DBaseManager::remove(const int &index)
{
    DBaseController *controller = m_dbaseList.takeAt(index);
    disconnect(controller);
    emit statusChanged("Закрыт: " + controller->getFolder());

    select(index-1);

    emit dbaseListChanged();

    controller->deleteLater();

    saveDBPreset();
}

void DBaseManager::scan(const int &index)
{
    m_dbaseList.at(index)->scanDir();
}

DBaseController *DBaseManager::getSelectedController()
{
    if(m_selected == -1)
        return nullptr;

    return m_dbaseList.at(m_selected);
}

void DBaseManager::loadDBPreset()
{
    if(!QFile::exists("preset.json"))
        return;

    QFile loadFile("preset.json");
    if(!loadFile.open(QIODevice::ReadOnly))
        return;

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    QJsonObject dbObject = loadDoc.object();

    QJsonArray dbPaths = dbObject["path"].toArray();

    for(auto path: dbPaths)
        openFolder(path.toString(), false);
}

void DBaseManager::saveDBPreset()
{
    QFile saveFile("preset.json");
    if(!saveFile.open(QIODevice::WriteOnly))
        return;

    QByteArray saveData = saveFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    QJsonArray dbPaths;
    for(auto dbase: m_dbaseList) {
        dbPaths << QUrl::fromLocalFile(dbase->getFolder()).toString();
    }

    QJsonObject dbObject;
    dbObject["path"] = dbPaths;

    QJsonDocument saveDoc(dbObject);
    saveFile.write(saveDoc.toJson());

    return;
}
