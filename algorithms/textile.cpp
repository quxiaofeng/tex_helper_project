#include "textile.h"
int GCD(int a, int b)
{
    if ( b == 0 )
        return a;
    return GCD ( b,a%b);
}

int LCM(int a, int b)
{
    return a*(b/GCD(a,b));

}

Textile::Textile(QObject *parent) :
    QObject(parent)
{
    // default black background white foreground
    setReverse(false);
    setDisplayFactor(20);
    setForeground(".");
    setBackground("X");
}

QString Textile::loadEmptyTextile()
{
    QString textile;
    QString lineMask;
    for (int iCol = 0; iCol < mnCols; iCol ++) {
        lineMask.append(mBackground);
    }
    lineMask.append("\n");

    for (int iRow = 0; iRow < mnRows; iRow ++) {
        textile.append(lineMask);
    }
    setTextile(textile);
    return textile;
}

QString Textile::loadEmptyTextile(
        int nCols, int nRows, QString background, QString foreground)
{
    this->setNcols(nCols);
    this->setNrows(nRows);
    this->setBackground(background);
    this->setForeground(foreground);
    return loadEmptyTextile();
}

QString Textile::drawNextPattern()
{
    ++ mStart;
    return drawPattern(mStart, mMove);
}

QString Textile::drawPattern()
{
    return drawPattern(mStart, mMove);
}

QString Textile::drawPattern(int start, int move)
{
    for (int iRow = 0; iRow < mnRows; iRow ++) {
        int offset = (iRow * move + start - 1) % mnCols;
        mTextile.replace((mnRows-iRow-1) * (mnCols+1) + offset, 1, mForeground);
    }
    QString tex(mTextile);
    return tex;
}

bool Textile::loadFromTxt()
{
    QFile file(mTextileFileName);
    if (file.exists()) {
        loadFromTxt(mTextileFileName);
        return true;
    }
    else
        return false;
}

bool Textile::loadFromTxt(QString txtFileName)
{
    QFile file(txtFileName);
    if (file.exists()==false) return false;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Can not open tex file " << txtFileName << "!";
        return false;
    }
    QTextStream in(&file);
    QString line = in.readLine();
    if (line.size() != mnCols) {
        qDebug() << "The line length of exist tex file is not equal to "
                 << mnCols
                 << " , which is set by option -c INTEGER.";
        this->setNcols(line.size());
    }
    QString tempTextile;
    int nRows = 0;
    while (!line.isNull()) {
        tempTextile.append(line).append("\n");
        ++ nRows;
        line = in.readLine();
    }
    file.close();
    this->setNrows(nRows);
    this->setTextile(tempTextile);
    return true;
}

bool Textile::save()
{
    if (loadFromTxt() == false)
        loadEmptyTextile();

    drawPattern();
    qDebug() << mTextile;

    if (saveToTxt()) return true;
    else return false;
}

bool Textile::saveToTxt(QString txtFileName)
{
    QFile file(txtFileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)==false) {
        qDebug() << txtFileName;
        return false;
    }
    QTextStream out(&file);
    out << mTextile;
    file.close();
    return true;
}

bool Textile::saveToTxt()
{
    return saveToTxt(mTextileFileName);
}

bool Textile::saveToImage()
{
    return saveToImage(mImageFileName);
}

bool Textile::saveToImage(QString imName)
{
    cv::Mat im = cv::Mat::zeros(cv::Size(mnCols*mFactor, mnRows*mFactor), CV_8U);
    for (int iRow = 0; iRow < mnRows; ++ iRow) {
        for (int iCol = 0; iCol <mnCols; ++ iCol) {
            cv::Scalar fillBlock;
            if ( QString(mTextile.at(iRow*(mnCols+1)+iCol)).compare(mForeground) == 0) {
                fillBlock = mFgFillBlock;
            }
            else {
                fillBlock = mBgFillBlock;
            }
            cv::rectangle( im,
                           cv::Point( iCol*mFactor, iRow*mFactor ),
                           cv::Point( iCol*mFactor+mFactor-1, iRow*mFactor+mFactor-1),
                           fillBlock,
                           -1,
                           8 );
        }
    }
    if (cv::imwrite(imName.toAscii().data(), im)) return true;
    else return false;
}

void Textile::setBackground(QString strChar)
{
    mBackground = strChar;
}

void Textile::setForeground(QString strChar)
{
    mForeground = strChar;
}

void Textile::setNcols(int ncols)
{
    mnCols = ncols;
}

void Textile::setNrows(int nrows)
{
    mnRows = nrows;
}

void Textile::setMove(int move)
{
    this->mMove = move;
}

void Textile::setStart(int start)
{
    this->mStart = start;
}

void Textile::setTextileFileName(QString fileName)
{
    mTextileFileName = fileName;
}

void Textile::setDisplayFactor(int edge)
{
    mFactor = edge;
}

int Textile::getNcols()
{
    return mnCols;
}

void Textile::setImageName(QString imName)
{
    mImageFileName = imName;
}

QString Textile::showTextile()
{
    QString tex = QString(mTextile);
    return tex;
}

void Textile::copyTo(Textile * nt)
{
    nt->setImageName(mImageFileName);
    nt->setTextile(mTextile);
    nt->setTextileFileName(mTextileFileName);
    nt->setNcols(mnCols);
    nt->setNrows(mnRows);
    nt->setMove(mMove);
    nt->setStart(mStart);
    nt->setBackground(mBackground);
    nt->setForeground(mForeground);
    nt->setDisplayFactor(mFactor);
}

void Textile::setTextile(QString tex)
{
    mTextile = tex;
}

bool Textile::weaveAndSaveToTxt(QStringList inputs, QString dstFileName)
{
    QString dstWeavedTex;
    QStringList texList;
    QSize commonInputSize = mGetTexsSizeLcm(inputs);
    qDebug() << "BEGIN Textile";
    qDebug() << "input files: " << inputs;
    qDebug() << "destination file name: " << dstFileName;
    qDebug() << "LCM size: " << commonInputSize;

    // load input files
    QList<QString>::Iterator it = inputs.begin();
    QList<QString>::Iterator itend = inputs.end();
    // each textile is loaded as a qstring list to maintain the lines in order
    for (;it != itend; ++it){
        QStringList currentTex;
        qDebug() << "read txt file: " << *it;
        if (mloadTexForWeaving(&currentTex, *it, commonInputSize)) {
            texList.append(currentTex);
            qDebug() << "current textile file" << currentTex;
        }
        else return false;
    }

    QFile file(dstFileName);
    if (file.exists()) {
        qDebug() << "Output Tex File "<< dstFileName << " already exists!";
        return false;
    }

    QList<QStringList> tempListOfWeavedTex;
    for (int iRow=0;iRow<commonInputSize.height();iRow++) {
        QStringList temp;
        tempListOfWeavedTex << temp;
    }

    int iTexLine = 0;
    for ( it = texList.begin(),itend = texList.end();
          it != itend;
          ++ it, ++ iTexLine) {
        tempListOfWeavedTex[iTexLine % commonInputSize.height()].append(*it);
    }

    for (int i=0;i<commonInputSize.height();i++) {
        dstWeavedTex.append(tempListOfWeavedTex.at(i).join("\n")).append("\n");
    }
    qDebug() << "output weaved tex file: " << dstWeavedTex;

    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << dstWeavedTex;
    file.close();

    return true;
}

bool Textile::mloadTexForWeaving(QStringList *tex, QString fileName, QSize texsize)
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

    QStringList temptex;
    QString line = in.readLine();
    uint ncolsScale = texsize.width() / line.size();
    while (!line.isNull()) {
        QString totalLine=line.repeated(ncolsScale);
        temptex.append(totalLine);
        qDebug() << ncolsScale << " times line is " << totalLine;
        line = in.readLine();
    }
    uint nrowsScale = texsize.height() / temptex.size();
    for (uint scale =0; scale < nrowsScale; ++ scale) {
        QStringList anotherList = temptex;
        qDebug() << "current textile:" << anotherList;
        tex->append(anotherList);
        qDebug() << "current output weaved file is :" << tex;
    }
    file.close();
    return true;
}

void Textile::setReverse(bool reverse)
{
    mReverse = reverse;
    if (mReverse == true) {
        // reverse to white background black foreground
        // reverse to white paper
        setFgFillBlock(0);
        setBgFillBlock(255);
    }
    else {
        // default black background white foreground
        // default: black board
        setFgFillBlock(255);
        setBgFillBlock(0);
    }
}

void Textile::setBgFillBlock(uint graylevel)
{
    mBgFillBlock = cv::Scalar(graylevel,graylevel,graylevel);
}

void Textile::setFgFillBlock(uint graylevel)
{
    mFgFillBlock = cv::Scalar(graylevel,graylevel,graylevel);
}

QSize Textile::mGetTexsSizeLcm(QStringList fileNameList)
{
    QList<uint> nrowsList;
    QList<uint> ncolsList;
    QList<QString>::Iterator it = fileNameList.begin();
    QList<QString>::Iterator itend = fileNameList.end();
    for (;it != itend; ++it){
        QSize currentSize = mGetSizeFromTxt(*it);
        nrowsList.append(currentSize.height());
        ncolsList.append(currentSize.width());
    }
    uint nrowsLcm =1;
    QList<uint>::Iterator itNrow = nrowsList.begin();
    QList<uint>::Iterator itendNrow = nrowsList.end();
    for (;itNrow != itendNrow; ++itNrow){
        nrowsLcm = LCM(nrowsLcm,*itNrow);
    }
    uint ncolsLcm =1;
    QList<uint>::Iterator itNcol = ncolsList.begin();
    QList<uint>::Iterator itendNcol = ncolsList.end();
    for (;itNcol != itendNcol; ++itNcol){
        ncolsLcm = LCM(ncolsLcm,*itNcol);
    }
    return QSize(ncolsLcm,nrowsLcm);
}

QSize Textile::mGetSizeFromTxt(QString fileName)
{
    QSize texsize(0,0);
    QFile file(fileName);

    if (!file.exists()) {
        qDebug() << "Tex File "<< fileName << " does not exist!";
        return texsize;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Can not open tex file " << fileName << "!";
        return texsize;
    }
    QTextStream in(&file);
    QString line = in.readLine();
    uint height = 0;
    if (!line.isNull()) texsize.setWidth(line.size());
    while (!line.isNull()) {
        ++ height;
        line = in.readLine();
    }
    texsize.setHeight(height);
    file.close();
    return texsize;
}


