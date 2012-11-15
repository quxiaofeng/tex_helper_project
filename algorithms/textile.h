#ifndef TEXTILE_H
#define TEXTILE_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QStringList>
#include <QSize>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class Textile : public QObject
{
    Q_OBJECT
public:
    explicit Textile(QObject *parent = 0);
    void setTextileFileName(QString fileName);
    void setMove(int move);
    void setStart(int start);
    void setBackground(QString strChar);
    void setForeground(QString strChar);
    QString drawPattern();
    QString drawPattern(int start, int move);
    QString drawNextPattern();
    bool save();
    void setTextile(QString tex);
    bool loadFromTxt();
    bool loadFromTxt(QString txtFileName);
    bool saveToTxt();
    bool saveToTxt(QString txtFileName);
    QString loadEmptyTextile();
    QString loadEmptyTextile(int nCols, int nRows, QString background, QString foreground);
    void setImageName(QString imName);
    bool saveToImage();
    bool saveToImage(QString imName);
    void setNcols(int ncols);
    int getNcols();
    void setNrows(int nrows);
    void setDisplayFactor(int edge);
    QString showTextile();

    void copyTo(Textile *);

    void setReverse(bool reverse);
    void setFgFillBlock(uint graylevel);
    void setBgFillBlock(uint graylevel);
    void expand(uint scale);

    // varables for textile weaver, should be refactored.
    // each textile is cached as a QStringList, which is differet from general textile
    // need to be fixed
    bool weaveAndSaveToTxt(QStringList inputs, QString dstFileName);

signals:

public slots:

private:
    QString mImageFileName;
    QString mTextile;
    QString mTextileFileName;
    int mnCols;
    int mnRows;
    int mMove;
    int mStart;
    QString mBackground;
    QString mForeground;
    int mFactor;
    bool mReverse;
    cv::Scalar mFgFillBlock;
    cv::Scalar mBgFillBlock;
    // add for repeat pattern
    QSize mGetTexsSizeLcm(QStringList fileNameList);
    QSize mGetSizeFromTxt(QString fileName);
    bool mloadTexForWeaving(QStringList *tex, QString fileName, QSize texsize);
};

#endif // TEXTILE_H
