#include "viewermodel.h"

ViewerModel::ViewerModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

QHash<int, QByteArray> ViewerModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[modelData]  = "modelData";
    roles[selectedRole]   = "isSelected";
    return roles;
}

int ViewerModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    if(modelIsEmpty())
        return 0;

    return m_dataSource->count();
}

QVariant ViewerModel::data(const QModelIndex &index, int role) const
{
//height: {
//    if(model.index <= 0)
//        return 0

//    if(viewerModel.data(viewerModel.index(model.index-1, 0, 0), 256).albumId
//            === model.modelData.albumId)
//        return 0

//    var albCount = viewerModel.data(
//                viewerModel.index(model.index-1, 0, 0), 256).albumTrackCount

//    var needTracks = parseInt((albumImage.width - 20)/20)

//    if(albCount > needTracks)
//        return 0

//    return needTracks * 20
//}

    if (!index.isValid())
        return QVariant();

    if(modelIsEmpty())
        return QVariant();

    if(role == modelData) {
        return QVariant::fromValue(m_dataSource->itemAt(index.row()));
    }

    if(role == selectedRole)
        return m_selectedList.contains(index.row());

    return QVariant();
}

void ViewerModel::setDataSource(DBaseController *dataSource)
{
    beginResetModel();
        m_selectedList.clear();
        m_dataSource = dataSource;
    endResetModel();

    emit isEmptyChanged();
    emit searchFilterChanged();
}

bool ViewerModel::modelIsEmpty() const
{
    return m_dataSource == nullptr;
}

QString ViewerModel::getSearchFilter() const
{
    if(modelIsEmpty())
        return "";

    return m_dataSource->getSearchFilter();
}

void ViewerModel::setSearchFilter(const QString &searchFilter)
{
    if(m_dataSource->getSearchFilter() == searchFilter)
        return;

    search(searchFilter);
}

void ViewerModel::removeSelection()
{
    QList<int> toUnselect = m_selectedList;
    m_selectedList.clear();

    for(auto selected: toUnselect)
        dataChanged(index(selected), index(selected),
                    QVector<int>() << selectedRole);
}

void ViewerModel::select(const int &row)
{
    removeSelection();

    m_selectedList << row;
    dataChanged(index(row), index(row),
                QVector<int>() << selectedRole);
}

void ViewerModel::selectAdd(const int &row)
{
    if(!m_selectedList.contains(row))
        m_selectedList << row;
    else
        m_selectedList.removeOne(row);

    dataChanged(index(row), index(row),
                QVector<int>() << selectedRole);
}

void ViewerModel::selectTo(const int &to)
{
    int from = m_selectedList.last();

    for(; to > from; ++from) {
        if(m_selectedList.contains(from))
            continue;

        m_selectedList << from;
        dataChanged(index(from), index(from),
                    QVector<int>() << selectedRole);
    }

    for(; to <= from; --from) {
        if(m_selectedList.contains(from))
            continue;

        m_selectedList << from;
        dataChanged(index(from), index(from),
                    QVector<int>() << selectedRole);
    }
}

void ViewerModel::fileToPlay(const QUrl &filename)
{
    emit playFile(filename);
}

void ViewerModel::appendToPlaylist(const ItemTrack *filename)
{
//    QList<ItemTrack*> list;
//    list.append(filename);
//    appendToPlaylist(QList<ItemTrack*>() << filename);
}

void ViewerModel::appendSelectedToPlaylist()
{
    QList<ItemTrack*> list;

    for(auto selRow: m_selectedList) {
        list << m_dataSource->itemAt(selRow);
    }

    emit appendToPlaylist(list);
}

void ViewerModel::search(const QString &searchFilter)
{
    if(modelIsEmpty())
        return;

    m_dataSource->setSearchFilter(searchFilter);
    emit searchFilterChanged();
}
