#ifndef MODELVIDEOVIEW_H
#define MODELVIDEOVIEW_H

#include <QAbstractListModel>
#include <QFile>
#include <QDir>
#include <QFileInfo>

class ModelVideoView : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ModelVideoView(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE void update(QString filepath = ".");

private:
    QStringList itemsList;
    QDir dir;

};

#endif // MODELVIDEOVIEW_H
