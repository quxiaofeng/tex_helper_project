#include <QtCore/QCoreApplication>
#include <../algorithms/textile.h>

int main(int argc, char *argv[])
{
    Textile textile;
    if (argc = 3) {
        textile.load(argv[1]);
        textile.setBackground(".");
        textile.setForeground("X");
        textile.setDisplayFactor(10);
        textile.saveToImage(argv[2]);
        return 0;
    }
    return 1;
}
