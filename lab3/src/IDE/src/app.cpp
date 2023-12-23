#include <QApplication>
#include <QCoreApplication>
#include <QCommandLineParser>

#include "Editor.h"

int main(int argc, char *argv[]) {
    QApplication EditorApp(argc, argv);
    QApplication::setWindowIcon(QIcon(":/images/app_icon.png"));

    QCoreApplication::setApplicationName("Yet another assembly IDE");

    QCommandLineParser cli_parser;
    cli_parser.process(EditorApp);
    const QStringList args = cli_parser.positionalArguments();

    Editor Editor;
    Editor.show();

    return QApplication::exec();
}
