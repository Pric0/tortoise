#ifndef VIEWERMODEL_H
#define VIEWERMODEL_H

#include <QAbstractListModel>
#include <QList>

#include <QDebug>

#include "dbasecontroller.h"

class ViewerModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ViewerModel(QObject *parent = nullptr);
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = modelData) const override;

    void setDataSource(DBaseController* dataSource);

    Q_PROPERTY(bool isEmpty READ modelIsEmpty NOTIFY isEmptyChanged)
    bool modelIsEmpty() const;

    Q_PROPERTY(QString searchFilter READ getSearchFilter WRITE setSearchFilter NOTIFY searchFilterChanged)
    QString getSearchFilter() const;
    void setSearchFilter(const QString &searchFilter);

    bool isSelected(const int &row) const;
    void removeSelection();
    Q_INVOKABLE void select(const int &row);
    Q_INVOKABLE void selectAdd(const int &row);
    Q_INVOKABLE void selectTo(const int &to);

    Q_INVOKABLE void fileToPlay(const QUrl &filename);
    Q_INVOKABLE void appendToPlaylist(const ItemTrack *filename);
    Q_INVOKABLE void appendSelectedToPlaylist();

signals:
    void isEmptyChanged();
    void searchFilterChanged();
    void playFile(const QUrl &filename);
    void appendToPlaylist(const QList<ItemTrack*> &filename);

private:
    DBaseController *m_dataSource = nullptr;

    QString m_searchFilter;

    enum Roles {
        modelData     = Qt::UserRole,
        selectedRole  = Qt::UserRole + 1
    };

    void search(const QString &searchFilter);

    QList<int> m_selectedList;
};

#endif // VIEWERMODEL_H
