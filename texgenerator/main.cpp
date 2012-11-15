#include <QtCore/QCoreApplication>
#include <../algorithms/anyoption.h>
#include <../algorithms/textile.h>
#include <QDebug>
#include <QString>
#include <QStringList>

bool autogen = false;
bool saveim = false;
void readoption(int argc, char *argv[], Textile *texGenerator);
//void noMessageOutput(QtMsgType, const char *)
//{}
int main(int argc, char *argv[])
{
    //qInstallMsgHandler(noMessageOutput);
    Textile texGenerator;
    readoption(argc, argv, &texGenerator);

    if (autogen == true) {
        QStringList texList;
        texGenerator.loadEmptyTextile();
        texGenerator.drawPattern();
        qDebug() << texGenerator.showTextile();
        texList.append(texGenerator.showTextile());
        for (int i=1; i<texGenerator.getNcols()-1; ++i) {
            texGenerator.drawNextPattern();
            texList.append(texGenerator.showTextile());
            qDebug() << texList.last();
        }
        for(int i=0; i < texList.size(); ++ i) {
            QChar fill('0');
            QString imagefilename = QString("tex%1.png").arg(i,3,10,fill);
            QString txtfilename = QString("tex%1.txt").arg(i,3,10,fill);
            texGenerator.setTextile(texList.at(i));
            texGenerator.saveToImage(imagefilename);
            texGenerator.saveToTxt(txtfilename);
        }
        return 0;
    }
    else if (texGenerator.save() == true) {
        if (saveim == true) texGenerator.saveToImage();
        return 0;
    }
    else return 1;
}

void readoption(int argc, char *argv[], Textile *texGenerator)
{
    /* 1. CREATE AN OBJECT */
    AnyOption *opt = new AnyOption();

    /* 2. SET PREFERENCES  */
    //opt->noPOSIX(); /* do not check for POSIX style character options */
    //opt->setVerbose(); /* print warnings about unknown options */
    //opt->autoUsagePrint(true); /* print usage for bad options */

    /* 3. SET THE USAGE/HELP   */
    opt->addUsage( "" );
    opt->addUsage( "Usage: " );
    opt->addUsage( "" );
    opt->addUsage( " -h          --help                  Prints this help " );
    opt->addUsage( " -s NUMBER   --size NUMBER           Tex size 16 or 32. Default is 16. " );
    opt->addUsage( " -r NUMBER   --row-number NUMBER     Number of rows. Default is 16. " );
    opt->addUsage( " -c NUMBER   --column-number NUMBER  Number of columns. Default is 16. " );
    opt->addUsage( " -i NUMBER   --interval NUMBER       Distance between tow black point. Default is 3." );
    opt->addUsage( " -o NUMBER   --origin NUMBER         Location of first point, start from 1. Default is 1." );
    opt->addUsage( " -f FILENAME --filename FILENAME     Tex file name. Default is \"newtex.txt\"" );
    opt->addUsage( " -x          --exchange-fb           Exchange foreground and background." );
    opt->addUsage( " -a          --autogen               Auto generate a batch of textiles." );
    opt->addUsage( "             --saveim                Save image of generated textile." );
    opt->addUsage( "             --imname FILENAME       Path and Name of the image to save. " );
    opt->addUsage( "             --imblocksize NUMBER    Size of image block. " );
    opt->addUsage( "" );

    /* 4. SET THE OPTION STRINGS/CHARACTERS */

    opt->setFlag(  "help", 'h' );
    opt->setOption(  "size", 's' );
    opt->setOption(  "row-number", 'r' );
    opt->setOption(  "column-number", 'c' );
    opt->setOption(  "interval", 'i' );
    opt->setOption(  "origin", 'o' );
    opt->setOption(  "filename", 'f' );
    opt->setFlag(  "exchange-fb", 'x' );
    opt->setFlag(  "autogen", 'a' );
    opt->setFlag(  "saveim" );
    opt->setOption(  "imname" );
    opt->setOption(  "imblocksize" );

    /* 5. PROCESS THE COMMANDLINE AND RESOURCE FILE */

    /* read options from a  option/resource file with ':' separated opttions or flags, one per line */
    opt->processFile( ".options" );
    /* go through the command line and get the options  */
    opt->processCommandArgs( argc, argv );

    if( ! opt->hasOptions()) { /* print usage if no options */
        opt->printUsage();
        delete opt;
        return;
    }

    /* 6. GET THE VALUES */
    if( opt->getFlag( "help" ) || opt->getFlag( 'h' ) )
        opt->printUsage();
    if( opt->getValue( 's' ) != NULL  || opt->getValue( "size" ) != NULL  ){
        texGenerator->setNcols(QString(opt->getValue( 's' )).toUInt());
        texGenerator->setNrows(QString(opt->getValue( 's' )).toUInt());
    }
    else {
        texGenerator->setNcols(16);
        texGenerator->setNrows(16);
    }
    if( opt->getValue( 'r' ) != NULL  || opt->getValue( "row-number" ) != NULL  ){
        texGenerator->setNrows(QString(opt->getValue( 'r' )).toUInt());
    }
    if( opt->getValue( 'c' ) != NULL  || opt->getValue( "column-number" ) != NULL  ){
        texGenerator->setNcols(QString(opt->getValue( 'c' )).toUInt());
    }
    if( opt->getValue( 'i' ) != NULL  || opt->getValue( "interval" ) != NULL  ) {
        texGenerator->setMove(QString(opt->getValue( 'i' )).toUInt());
    }
    else {
        texGenerator->setMove(1);
    }
    if( opt->getValue( 'o' ) != NULL  || opt->getValue( "origin" ) != NULL  ) {
        texGenerator->setStart(QString(opt->getValue( 'o' )).toUInt());
    }
    else {
        texGenerator->setStart(1);
    }
    if( opt->getValue( 'f' ) != NULL  || opt->getValue( "filename" ) != NULL  ) {
        texGenerator->setTextileFileName(QString(opt->getValue( 'f' )));
    }
    else {
        texGenerator->setTextileFileName(QString("newtex.txt"));
    }
    texGenerator->setForeground("X");
    texGenerator->setBackground(".");
    if( opt->getFlag( "exchange-fb" ) || opt->getFlag( 'x' ) ) {
        texGenerator->setForeground(".");
        texGenerator->setBackground("X");
    }
    if( opt->getFlag( "autogen" ) || opt->getFlag( 'a' ) )
        autogen = true;
    if( opt->getFlag( "saveim" ) ) {
        texGenerator->setDisplayFactor(10);
        saveim = true;
    }
    if( opt->getValue( "imname" ) != NULL  ) {
        texGenerator->setImageName(QString(opt->getValue( "imname" )));
    }
    else {
        texGenerator->setImageName(QString("tex.png"));
    }
    if( opt->getValue( "imblocksize" ) != NULL  ) {
        texGenerator->setDisplayFactor(QString(opt->getValue( "imblocksize" )).toUInt());
    }
    else {
        texGenerator->setDisplayFactor(10);
    }

    /* 8. DONE */
    delete opt;

}
