#ifndef TAGSOURCE_H
#define TAGSOURCE_H

#include <QObject>
#include <QMap>
#include <QVariant>
#include <QFile>

class TagSource : public QObject
{
    Q_OBJECT
public:
    explicit TagSource(QObject *parent = nullptr);
    static QMap<QString, QVariant> getTagsFromFile(const QString &filename);

signals:

public slots:
};

#endif // TAGSOURCE_H
