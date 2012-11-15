#include "texweaver.h"

TexWeaver::TexWeaver(QObject *parent) :
    QObject(parent)
{
}

bool TexWeaver::saveWeavedFile()
{
    QString dstWeavedTex;
    QStringList texList;

    QList<QString>::Iterator it = inputFileNameList.begin();
    QList<QString>::Iterator itend = inputFileNameList.end();

    for (;it != itend; ++it){
        QStringList currentTex;
        if (texFileReader(&currentTex, *it)) {
            texList.append(currentTex);
        }
        else return false;
    }

    QFile file(this->dstFileName);
    if (file.exists()) {
        qDebug() << "Output Tex File "<< dstFileName << " already exists!";
        return false;
    }

    QList<QStringList> tempListOfWeavedTex;
    for (int i=0;i<texFileSize;i++) {
        QStringList temp;
        tempListOfWeavedTex << temp;
    }

    int iTexLine = 0;
    for ( it = texList.begin(),itend = texList.end();
          it != itend;
          ++ it, ++ iTexLine) {
        tempListOfWeavedTex[iTexLine % texFileSize].append(*it);
    }

    for (int i=0;i<texFileSize;i++) {
        dstWeavedTex.append(tempListOfWeavedTex.at(i).join("\n")).append("\n");
    }
    qDebug() << dstWeavedTex;

    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << dstWeavedTex;
    file.close();

    return true;
}

bool TexWeaver::texFileReader(QStringList *tex, QString fileName)
{
    QFile file(fileName);

    if (!file.exists()) {
        qDebug() << "Tex File "<< fileName << " does not exist!";
        return false;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Can not open tex file " << fileName << "!";
        return false;
    }
    QTextStream in(&file);
    QString line = in.readLine();
    if (line.size() != texFileSize) {
        qDebug() << "The line length of exist tex file is not equal to "
                 << texFileSize
                 << " , which is set by option -s INTEGER.";
        return false;
    }
    while (!line.isNull()) {
        tex->append(line);
        line = in.readLine();
    }
    file.close();
    return true;
}
