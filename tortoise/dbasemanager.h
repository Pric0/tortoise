#ifndef DBASEMANAGER_H
#define DBASEMANAGER_H

#include <QObject>
#include <QUrl>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QDebug>

#include "dbasecontroller.h"

class DBaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DBaseManager(QObject *parent = nullptr);

    Q_PROPERTY(QList<QObject*> dbaseList READ getDbaseList NOTIFY dbaseListChanged)
    QList<QObject*> getDbaseList() const;

    Q_PROPERTY(int selected READ getSelected NOTIFY dataChanged)
    int getSelected() const;

    Q_INVOKABLE void openFolder(const QUrl &folder, const bool &saveChanges = true);
    Q_INVOKABLE void select(const int &index);
    Q_INVOKABLE void remove(const int &index);

    Q_INVOKABLE void scan(const int &index);

    DBaseController* getSelectedController();

signals:
    void dbaseListChanged();
    void dataChanged();
    void artistsDataChanged();
    void statusChanged(const QString&);

public slots:


private:
    QList<DBaseController*> m_dbaseList;
    int m_selected = -1;

    void loadDBPreset();
    void saveDBPreset();
};

#endif // DBASEMANAGER_H
