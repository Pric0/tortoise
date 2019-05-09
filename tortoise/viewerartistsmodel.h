#ifndef VIEWERARTISTSMODEL_H
#define VIEWERARTISTSMODEL_H

#include <QAbstractListModel>

#include "dbasecontroller.h"

#include <QDebug>

class ViewerArtistsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ViewerArtistsModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void setDataSource(DBaseController* dataSource);

    Q_INVOKABLE bool modelIsEmpty() const;

    Q_PROPERTY(bool isEmptyFilter READ isEmptyFilter NOTIFY filterChanged)

    bool isEmptyFilter() const;
    Q_INVOKABLE void selectArtist(const QString &name);

signals:
    void artistFilterChanged();
    void filterChanged();

private:
    DBaseController *m_dataSource = nullptr;

    enum Roles {
        modelData     = Qt::UserRole,
        selectedRole  = Qt::UserRole + 1
    };
};

#endif // VIEWERARTISTSMODEL_H
