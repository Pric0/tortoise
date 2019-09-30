#ifndef VIDEOVIEWER_H
#define VIDEOVIEWER_H

#include <QObject>
#include <QQmlApplicationEngine>

#include "modelvideoview.h"

class VideoViewer : public QObject
{
    Q_OBJECT
public:
    explicit VideoViewer(QQmlApplicationEngine *engine,
                         QObject *parent = nullptr);


signals:

public slots:

private:
    ModelVideoView *m_model;
    QQmlApplicationEngine *m_engine;
};

#endif // VIDEOVIEWER_H
