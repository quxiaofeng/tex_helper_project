#include <QtCore/QCoreApplication>
#include <../algorithms/textile.h>
#include <QChar>
#include <QString>

void autoGenTextiles(
        int nCols, int nRows, int start, int move, QString foreground,
        QString background, int displayFactor, bool reverse,
        QString txtFileNamePattern, QString imageFileNamePattern);
void genTextile(
        int nCols, int nRows, int start, int move, QString foreground,
        QString background, int displayFactor, bool reverse,
        QString txtFileName, QString imageFileName);

int main(int argc, char *argv[])
{
    Textile tex;
    autoGenTextiles(16,16,1,7,"X",".",20,true,"tex001-%1.txt","tex001-%1.png");
    genTextile(8,8,1,5,".","X",20,false,"tex002-001.txt","tex002-001.png");
    genTextile(16,16,1,7,".","X",20,false,"tex003-001.txt","tex003-001.png");
    genTextile(32,32,1,7,".","X",20,false,"tex004-001.txt","tex004-001.png");
    for (uint iTex = 1; iTex < 16; ++ iTex) {
        QStringList inputList;
        inputList.append(QString("tex001-%1.txt").arg(iTex,3,10,QChar('0')));
        inputList.append("tex002-001.txt");
        inputList.append("tex003-001.txt");
        inputList.append("tex004-001.txt");
        QString dstFileName = QString("texResult%1-001-001-001.txt")
                .arg(iTex,3,10,QChar('0'));
        QString dstImage = QString("texResult%1-001-001-001.png")
                .arg(iTex,3,10,QChar('0'));
        tex.weaveAndSaveToTxt(inputList, dstFileName);
        tex.loadFromTxt(dstFileName);
        tex.saveToImage(dstImage);
    }
    return 0;
}

void autoGenTextiles(
        int nCols, int nRows, int start, int move,
        QString foreground, QString background, int displayFactor,
        bool reverse, QString txtFileNamePattern, QString imageFileNamePatter)
{
    QChar fill('0');
    Textile texGenerator;
    QStringList texList;
    texGenerator.setNcols(nCols);
    texGenerator.setNrows(nRows);
    texGenerator.setMove(move);
    texGenerator.setStart(start);
    texGenerator.setForeground(foreground);
    texGenerator.setBackground(background);
    texGenerator.setDisplayFactor(displayFactor);
    texGenerator.setReverse(reverse);
    texGenerator.loadEmptyTextile();
    texGenerator.drawPattern();
    texList.append(texGenerator.showTextile());
    for (int i=1; i<texGenerator.getNcols()-1; ++i) {
        texGenerator.drawNextPattern();
        texList.append(texGenerator.showTextile());
    }
    for(int i=0; i < texList.size(); ++ i) {
        QString imagefilename = QString(imageFileNamePatter).arg(i+1,3,10,fill);
        QString txtfilename = QString(txtFileNamePattern).arg(i+1,3,10,fill);
        texGenerator.setTextile(texList.at(i));
        texGenerator.saveToImage(imagefilename);
        texGenerator.saveToTxt(txtfilename);
    }
}


void genTextile(
        int nCols, int nRows, int start, int move, QString foreground,
        QString background, int displayFactor, bool reverse,
        QString txtFileName, QString imageFileName)
{
    Textile texGenerator;
    texGenerator.setNcols(nCols);
    texGenerator.setNrows(nRows);
    texGenerator.setMove(move);
    texGenerator.setStart(start);
    texGenerator.setForeground(foreground);
    texGenerator.setBackground(background);
    texGenerator.setDisplayFactor(displayFactor);
    texGenerator.setReverse(reverse);
    texGenerator.loadEmptyTextile();
    texGenerator.drawPattern();
    texGenerator.saveToImage(imageFileName);
    texGenerator.saveToTxt(txtFileName);
}
