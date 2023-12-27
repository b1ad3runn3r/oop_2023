#include <QApplication>
#include <QCoreApplication>
#include <QIcon>

#include "TableViewer/TableViewer.h"

int main(int argc, char **argv) {
    QApplication TableViewerApp(argc, argv);
    QApplication::setWindowIcon(QIcon("assets"));
    QCoreApplication::setApplicationName("Table viewer and editor");

    TableViewer tableViewer;
    tableViewer.show();

    return QApplication::exec();
}