#ifndef TEXWEAVER_H
#define TEXWEAVER_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QList>

class TexWeaver : public QObject
{
    Q_OBJECT
public:
    explicit TexWeaver(QObject *parent = 0);
    int texFileSize;
    int number;
    QString dstFileName;
    QStringList inputFileNameList;
    bool saveWeavedFile();
    bool texFileReader(QStringList *tex, QString fileName);

signals:

public slots:

};

#endif // TEXWEAVER_H
