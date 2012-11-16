#include <QtCore/QCoreApplication>
#include <../algorithms/textile.h>

void autoGenTextiles(
        int nCols, int nRows, int start, int move,
        QString foreground, QString background, int displayFactor,
        bool reverse, QString txtFileNamePattern, QString imageFileNamePattern);
void autoWeaver(
        uint texSize, QString outputFileName, QStringList inputFileNameList);

int main(int argc, char *argv[])
{
    QChar fill('0');
    Textile tex2image;
    tex2image.setBackground(".");
    tex2image.setForeground("X");
    tex2image.setDisplayFactor(20);
    autoGenTextiles(32,32,16,19,"X",".",20,true,"tex001-%1.txt","tex001-%1.png");
    autoGenTextiles(32,32,11,19,"X",".",20,true,"tex002-%1.txt","tex002-%1.png");
    autoGenTextiles(32,32,6,19,"X",".",20,true,"tex003-%1.txt","tex003-%1.png");
    autoGenTextiles(32,32,1,19,"X",".",20,true,"tex004-%1.txt","tex004-%1.png");
    for (int iTex1 = 1; iTex1 < 32; ++iTex1) {
        QString out = QString("texResult-%1-%2-%3-%4.txt")
                .arg(iTex1,3,10,fill)
                .arg(iTex1,3,10,fill)
                .arg(iTex1,3,10,fill)
                .arg(iTex1,3,10,fill);
        QString outim = QString("texResult-%1-%2-%3-%4.png")
                .arg(iTex1,3,10,fill)
                .arg(iTex1,3,10,fill)
                .arg(iTex1,3,10,fill)
                .arg(iTex1,3,10,fill);
        QStringList in;
        in.append(QString("tex001-%1.txt").arg(iTex1,3,10,fill));
        in.append(QString("tex002-%1.txt").arg(iTex1,3,10,fill));
        in.append(QString("tex003-%1.txt").arg(iTex1,3,10,fill));
        in.append(QString("tex004-%1.txt").arg(iTex1,3,10,fill));
        autoWeaver(32, out, in);
        tex2image.loadFromTxt(out);
        tex2image.setReverse(true);
        tex2image.saveToImage(outim);
    }
    return 0;
}


void autoGenTextiles(
        int nCols, int nRows, int start, int move,
        QString foreground, QString background, int displayFactor,
        bool reverse, QString txtFileNamePattern, QString imageFileNamePattern)
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
        QString imagefilename = QString(imageFileNamePattern).arg(i+1,3,10,fill);
        QString txtfilename = QString(txtFileNamePattern).arg(i+1,3,10,fill);
        texGenerator.setTextile(texList.at(i));
        texGenerator.saveToImage(imagefilename);
        texGenerator.saveToTxt(txtfilename);
    }
}

void autoWeaver(
        uint texSize, QString outputFileName,
        QStringList inputFileNameList)
{
    Textile texWeaver;
    texWeaver.setNcols(texSize);
    texWeaver.setNrows(texSize);
    texWeaver.weaveAndSaveToTxt(inputFileNameList, outputFileName);
}
