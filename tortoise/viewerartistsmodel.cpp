#include "viewerartistsmodel.h"

ViewerArtistsModel::ViewerArtistsModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

QHash<int, QByteArray> ViewerArtistsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[modelData]  = "modelData";
    roles[selectedRole]   = "isSelected";
    return roles;
}

int ViewerArtistsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    if(modelIsEmpty())
        return 0;

    return m_dataSource->artistsCount();
}

QVariant ViewerArtistsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(modelIsEmpty())
        return QVariant();

    if(role == modelData) {
        return QVariant::fromValue(
                    m_dataSource->artistAt(index.row()));
    }

    if(role == selectedRole)
        return m_dataSource->getArtistFilter() ==
            m_dataSource->artistAt(index.row())->getName();

    return QVariant();
}

void ViewerArtistsModel::setDataSource(DBaseController *dataSource)
{
    beginResetModel();
        m_dataSource = dataSource;
    endResetModel();

    emit artistFilterChanged();
    emit filterChanged();
}

bool ViewerArtistsModel::modelIsEmpty() const
{
    return m_dataSource == nullptr;
}

bool ViewerArtistsModel::isEmptyFilter() const
{
    if(modelIsEmpty())
        return true;

    return m_dataSource->getArtistFilter() == "";
}

void ViewerArtistsModel::selectArtist(const QString &name)
{
    if(modelIsEmpty())
        return;

    QString prevName = m_dataSource->getArtistFilter();
    m_dataSource->setArtistFilter(name);
    int finded = 0;

    for(int i = 0; i < m_dataSource->artistsCount(); ++i) {
        QString artName = m_dataSource->artistAt(i)->getName();
        if( (artName == prevName) || (artName == name) ) {
                dataChanged(index(i), index(i),
                            QVector<int>() << selectedRole);
                finded++;
                if(finded == 2)
                    break;
        }
    }

    emit filterChanged();
}
