#include <QApplication>
#include <QProcess>
#include <QDir>

#include "Console.hpp"

int main(int argc, char *argv[])
{
    if(argc < 2)
        return -1;
    QApplication a(argc, argv);
    QString program(argv[1]);
    QStringList arguments;
    for(int i = 2; i < argc; ++i)
    {
        arguments.push_back(argv[i]);
    }
    Console w(program,arguments);
    w.show();
    //process.waitForFinished();
    return a.exec();
}
