#include <QtCore/QCoreApplication>
#include <../algorithms/anyoption.h>
#include <../algorithms/textile.h>
#include <QDebug>
#include <QString>

void readoption(int argc, char *argv[], Textile *texWeaver, QStringList *inputs, QString *dstFileName);

//void noMessageOutput(QtMsgType, const char *)
//{}

int main(int argc, char *argv[])
{
    //qInstallMsgHandler(noMessageOutput);
    Textile texWeaver;
    QStringList inputs;
    QString dstFileName;
    readoption(argc, argv, &texWeaver, &inputs, &dstFileName);
    qDebug() << "input files: " << inputs;
    qDebug() << "destination file name: " << dstFileName;
    texWeaver.weaveAndSaveToTxt(inputs, dstFileName);
    return 0;
}

void readoption(int argc, char *argv[], Textile *texWeaver,
                QStringList *inputs, QString *dstFileName)
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
    opt->addUsage( " -h          --help                     Prints this help. " );
    opt->addUsage( " -s NUMBER   --size NUMBER              Tex size 16 or 32. Default is 16. " );
    opt->addUsage( " -n NUMBER   --input-number NUMBER      Number of input tex files. Default is 1. " );
    opt->addUsage( " -o FILENAME --output-filename FILENAME Output file name, plain text. Default is \"out.txt\". " );
    opt->addUsage( "" );

    /* 4. SET THE OPTION STRINGS/CHARACTERS */

    /* by default all  options  will be checked on the command line and from option/resource file */
    opt->setFlag(  "help", 'h' );   /* a flag (takes no argument), supporting long and short form */
    opt->setOption(  "size", 's' ); /* an option (takes an argument), supporting long and short form */
    opt->setOption(  "input-number", 'n' ); /* an option (takes an argument), supporting long and short form */
    opt->setOption(  "output-filename", 'o' ); /* an option (takes an argument), supporting long and short form */

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

    if( opt->getValue( 's' ) != NULL  || opt->getValue( "size" ) != NULL  ) {
        texWeaver->setNcols(QString(opt->getValue( 's' )).toUInt());
        texWeaver->setNrows(QString(opt->getValue( 's' )).toUInt());
    }
    else {
        texWeaver->setNcols(16);
        texWeaver->setNrows(16);
    }

    int number;
    if( opt->getValue( 'n' ) != NULL  || opt->getValue( "input-number" ) != NULL  ) {
        number = QString(opt->getValue( 'n' )).toUInt();
    }
    else {
        number = 1;
    }

    if( opt->getValue( 'o' ) != NULL  || opt->getValue( "output-filename" ) != NULL  ) {
        dstFileName->append(QString(opt->getValue( 'o' )));
    }
    else {
        dstFileName->append( QString("out.txt") );
    }

    /* 7. GET THE ACTUAL ARGUMENTS AFTER THE OPTIONS */
    if (opt->getArgc() < number) {
        qDebug() << "Not enough input files. There should be "
                 << number
                 << " input tex files.";
        exit(1);
    }
    for( int i = 0 ; i < number ; i++ ){
        inputs->append(QString(opt->getArgv( i )));
    }

    /* 8. DONE */
    delete opt;

}


