#include "videoviewer.h"

#include <QQmlContext>

VideoViewer::VideoViewer(QQmlApplicationEngine *engine,
                         QObject *parent) : QObject(parent)
{
    m_model = new ModelVideoView;
    m_engine = engine;

    engine->rootContext()->setContextProperty("modelVideoView", m_model);
}
