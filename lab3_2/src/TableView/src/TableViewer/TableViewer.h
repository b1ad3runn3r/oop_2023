#ifndef TABLE_VIEWER_H
#define TABLE_VIEWER_H

#include <QMainWindow>
#include "../../../Server/TransportTable/TransportTable.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
    class TableViewer;
}
QT_END_NAMESPACE

class TableViewer : public QMainWindow {
    Q_OBJECT
public:
    explicit TableViewer(QWidget *parent = nullptr);
    ~TableViewer() override;

private slots:
    void refillTable();
    void exit();
    void addPackage();
    void findPackage();
    void dropPackage();
    void findUniqueSenders();
    void calculateDistribution();

private:
    Ui::TableViewer *ui;
    TransportTable table;
    void fillTable(unsigned int length);
};

#endif // TABLE_VIEWER_H
