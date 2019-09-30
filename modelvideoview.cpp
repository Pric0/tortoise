#include "modelvideoview.h"

#include <QDebug>

ModelVideoView::ModelVideoView(QObject *parent)
    : QAbstractListModel(parent)
{
    dir.setPath(".");
    dir.setFilter(QDir::NoDot | QDir::Readable | QDir::Dirs | QDir::Files);
    update();
}

int ModelVideoView::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return itemsList.size();
}

QVariant ModelVideoView::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole) {
        return itemsList.at(index.row());
    }

    return QVariant();
}

void ModelVideoView::update(QString filepath)
{
    dir.cd(filepath);
    QStringList list;
    QFileInfoList filelist = dir.entryInfoList();
    for(int i = 0; i < filelist.size(); ++i) {
        list.append(filelist.at(i).fileName());
    }

    beginResetModel();
    itemsList = list;
    endResetModel();

    qDebug() << itemsList;
}
