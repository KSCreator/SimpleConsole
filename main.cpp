#include <cstring>
#include <QApplication>
#include <QProcess>
#include <QDir>
#include "Console.hpp"

int main(int argc, char *argv[])
{
    int qt_argc = 0;
    while(++qt_argc < argc
          && std::strcmp(argv[qt_argc],"-p"))
    {
        //
    }
    if(qt_argc == argc || qt_argc == argc-1)    //if no -p or it was last token
    {
        qDebug("no program specified");
        return -1;
    }
    QScopedArrayPointer<char*> qt_args(new char*[qt_argc]);
    const int qt_argc_original = qt_argc;

    for(int i = 0; i < qt_argc; ++i)
        qt_args[i] = argv[i];
    QApplication a(qt_argc, qt_args.data());    //qt argc may changed
    QString program_name(argv[qt_argc_original+1]);
    QStringList user_args;
    for(int i = qt_argc_original + 2; i < argc; ++i)
    {
        user_args.push_back(argv[i]);
    }
    Console console(program_name,user_args);
    console.show();
    //process.waitForFinished();
    return a.exec();
}
