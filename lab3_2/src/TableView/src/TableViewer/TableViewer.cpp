#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QtGlobal>
#include <QStatusBar>
#include <QTableWidget>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QAbstractItemView>
#include <QStandardItemModel>

#include "../Calculations.hpp"

#include <random>
#include "../../../Server/Packages/Package.hpp"
#include "../../../Server/Packages/MailPackage.hpp"
#include "../../../Server/Packages/FilePackage.hpp"
#include "../../../Server/Packages/HypertextPackage.hpp"


#include "TableViewer.h"
#include "ui_TableViewer.h"
#include "../Config.hpp"

TableViewer::TableViewer(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::TableViewer) {

    ui->setupUi(this);
    this->setCentralWidget(ui->tableWidget);

    connect(ui->actionRegenerate, &QAction::triggered, this, &TableViewer::refillTable);
    connect(ui->actionExit, &QAction::triggered, this, &TableViewer::exit);

    connect(ui->actionAddPackage, &QAction::triggered, this, &TableViewer::addPackage);
    connect(ui->actionFindPackage, &QAction::triggered, this, &TableViewer::findPackage);
    connect(ui->actionDropPackage, &QAction::triggered, this, &TableViewer::dropPackage);

    connect(ui->actionUniqueSenders, &QAction::triggered, this, &TableViewer::findUniqueSenders);
    connect(ui->actionPackageDistribution, &QAction::triggered, this, &TableViewer::calculateDistribution);

    QFont font;
    font.setFamily(font_family);
    font.setStyleHint(QFont::Monospace);
    font.setFixedPitch(true);
    font.setPointSize(font_size);

    ui->tableWidget->setFont(font);

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(8);

    QStringList list = {"type", "sender", "receiver", "username", "code_type", "info_type", "links", "message"};
    ui->tableWidget->setHorizontalHeaderLabels(list);

    fillTable(100);
    ui->tableWidget->setSortingEnabled(true);
}

TableViewer::~TableViewer() {
    delete ui;
}

void TableViewer::refillTable() {
    bool ok;
    QString text = QInputDialog::getText(this, "Refill table", "How many elements:",
                                         QLineEdit::Normal, "", &ok);
    if (!ok || text.isEmpty()) {
        return;
    }

    auto num_gens = text.toUInt();
    fillTable(num_gens);
}

void TableViewer::fillTable(unsigned int length) {
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    Message msg;
    std::string name = "username";

    std::random_device rnd;
    std::mt19937_64 rng(rnd());
    std::uniform_int_distribution<size_t> uni(0, 2);
    std::uniform_int_distribution<size_t> uni2(1, 10);

    for (auto i = 0; i < length; ++i) {
        auto rand_num = uni(rng);
        std::string sender = std::format("{}.{}.{}.{}", uni2(rng), uni2(rng), uni2(rng), uni2(rng));
        std::string receiver = std::format("{}.{}.{}.{}", uni2(rng), uni2(rng), uni2(rng), uni2(rng));
        std::shared_ptr<Package> ptr;
        switch (rand_num % 3) {
            case 0:
                ptr = std::make_shared<MailPackage>(
                        MailPackage(
                                {sender, receiver},
                                name,
                                msg)
                );
                table.add_package(ptr);
                break;

            case 1:
                ptr = std::make_shared<FilePackage>(
                        FilePackage(
                                {sender, receiver},
                                msg,
                                {ASCII, DATA})
                );
                table.add_package(ptr);
                break;

            case 2:
                ptr = std::make_shared<HypertextPackage>(
                        HypertextPackage(
                                {sender, receiver},
                                msg,
                                {ASCII, DATA},
                                {nullptr, 0})
                );
                table.add_package(ptr);
                break;
        }
    }

    auto old_row = ui->tableWidget->rowCount();
    for (const auto &iter: table.get_table()) {
        ui->tableWidget->setRowCount(old_row + 1);

        if (auto mp = std::dynamic_pointer_cast<MailPackage>(iter.second)) {
            for (size_t i = 0; i < 8; ++i) {
                ui->tableWidget->setItem(old_row, 0, new QTableWidgetItem(mp->get_package_type().c_str()));
                ui->tableWidget->setItem(old_row, 1, new QTableWidgetItem(mp->get_sender().c_str()));
                ui->tableWidget->setItem(old_row, 2, new QTableWidgetItem(mp->get_receiver().c_str()));
                ui->tableWidget->setItem(old_row, 3, new QTableWidgetItem(mp->get_username().c_str()));
                ui->tableWidget->setItem(old_row, 4, new QTableWidgetItem(""));
                ui->tableWidget->setItem(old_row, 5, new QTableWidgetItem(""));
                ui->tableWidget->setItem(old_row, 6, new QTableWidgetItem(""));
                ui->tableWidget->setItem(old_row, 7, new QTableWidgetItem(mp->get_message().get_msg_hex().c_str()));
            }
        } else if (auto fp = std::dynamic_pointer_cast<FilePackage>(iter.second)) {
            ui->tableWidget->setItem(old_row, 0, new QTableWidgetItem(fp->get_package_type().c_str()));
            ui->tableWidget->setItem(old_row, 1, new QTableWidgetItem(fp->get_sender().c_str()));
            ui->tableWidget->setItem(old_row, 2, new QTableWidgetItem(fp->get_receiver().c_str()));
            ui->tableWidget->setItem(old_row, 3, new QTableWidgetItem(""));
            std::string code_type;
            std::string info_type;
            std::string message;

            if (fp->get_code_type() == ASCII) {
                code_type = "ASCII";
                message = fp->get_message().get_msg_ascii();
            } else {
                code_type = "BIN";
                message = fp->get_message().get_msg_hex();
            }

            info_type = std::string((fp->get_info_type() == CMD) ? "CMD" : "DATA");
            ui->tableWidget->setItem(old_row, 4, new QTableWidgetItem(code_type.c_str()));
            ui->tableWidget->setItem(old_row, 5, new QTableWidgetItem(info_type.c_str()));
            ui->tableWidget->setItem(old_row, 6, new QTableWidgetItem(""));
            ui->tableWidget->setItem(old_row, 7, new QTableWidgetItem(message.c_str()));
        } else {
            auto hp = std::dynamic_pointer_cast<HypertextPackage>(iter.second);

            ui->tableWidget->setItem(old_row, 0, new QTableWidgetItem(hp->get_package_type().c_str()));
            ui->tableWidget->setItem(old_row, 1, new QTableWidgetItem(hp->get_sender().c_str()));
            ui->tableWidget->setItem(old_row, 2, new QTableWidgetItem(hp->get_receiver().c_str()));
            ui->tableWidget->setItem(old_row, 3, new QTableWidgetItem(""));

            std::string message;
            std::string code_type;
            std::string info_type;
            std::string links;

            if (hp->get_code_type() == ASCII) {
                code_type = "ASCII";
                message = hp->get_message().get_msg_ascii();
            } else {
                code_type = "BIN";
                message = hp->get_message().get_msg_hex();
            }

            info_type = std::string((hp->get_info_type() == CMD) ? "CMD" : "DATA");

            if (hp->get_links() != nullptr) {
                for (size_t i = 0; i < hp->get_links_size(); ++i) {
                    if (hp->get_links()[i].get_protocol() == FTP) {
                        links += "[FTP," + hp->get_links()[i].get_hostname() + "] ";
                    } else {
                        links += "[HTTP," + hp->get_links()[i].get_hostname() + "] ";
                    }
                }
            }

            ui->tableWidget->setItem(old_row, 4, new QTableWidgetItem(code_type.c_str()));
            ui->tableWidget->setItem(old_row, 5, new QTableWidgetItem(info_type.c_str()));
            ui->tableWidget->setItem(old_row, 6, new QTableWidgetItem(links.c_str()));
            ui->tableWidget->setItem(old_row, 7, new QTableWidgetItem(message.c_str()));

        }

        old_row = ui->tableWidget->rowCount();
    }
}

void TableViewer::addPackage() {

}

void TableViewer::findPackage() {
    bool ok;
    QString text = QInputDialog::getText(this, "Find package", "Sender address:",
                                         QLineEdit::Normal, "", &ok);

    size_t cnt = 0;
    if (ok && !text.isEmpty()) {
        ui->tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);
        auto num_rows = ui->tableWidget->rowCount();
        for (auto i = 0; i < num_rows; ++i) {
            if (text == ui->tableWidget->item(i, 1)->text()) {
                ui->tableWidget->selectRow(i);
                cnt += 1;
            }
        }
        ui->tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

        statusBar()->showMessage("Found " + QString::number(cnt) + " entries!", status_bar_timeout);
    } else {
        statusBar()->showMessage("Nothing found :(", status_bar_timeout);
    }

}

void TableViewer::dropPackage() {
    QModelIndexList selection(ui->tableWidget->selectionModel()->selectedRows());
    std::sort(selection.begin(), selection.end(),
              [](const QModelIndex &left, const QModelIndex &right) -> bool { return left.row() > right.row(); });

    if (selection.count() == 0) {
        QMessageBox::warning(this, "Warning", "You have nothing to delete :(");
        return ;
    }
    else {
        auto reply = QMessageBox::question(this, "Warning", "You sure you want to delete?",
                                           QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::No) {
            return ;
        }
    }

    const auto num_rows = selection.count();
    for (int i = 0; i < selection.count(); ++i) {
        QModelIndex index = selection.at(i);
        ui->tableWidget->removeRow(index.row());
    }

    statusBar()->showMessage("Deleted " + QString::number(num_rows) + " packages!", status_bar_timeout);
}

void TableViewer::findUniqueSenders() {
    std::map<std::string, std::atomic<size_t>> senders;
    senders = count_transmission_mt(table);

    auto *dialog = new QDialog(this);
    dialog->setModal(false);
    dialog->setDisabled(false);
    dialog->setMinimumHeight(500);
    dialog->setMinimumWidth(500);

    auto tv = new QTableView(dialog);
    auto model = new QStandardItemModel();
    tv->setModel(model);
    dialog->setLayout(new QVBoxLayout());
    dialog->layout()->addWidget(tv);

    model->setHorizontalHeaderItem(0, new QStandardItem("Sender"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Packets sent"));

    QList<QStandardItem*> rowData;
    for (const auto &iter : senders) {
        rowData.clear();
        rowData << new QStandardItem(iter.first.c_str());
        rowData << new QStandardItem(QString::number(iter.second.load()));
        model->appendRow(rowData);
    }
    tv->sortByColumn(1, Qt::DescendingOrder);

    dialog->exec();
    delete dialog;
}

void TableViewer::calculateDistribution() {
    std::map<std::string, std::atomic<size_t>> distribution;

    distribution = count_distrib_multithread(table);

    auto *bar_series = new QBarSeries();
    auto set_mail = new QBarSet("MAIL");
    *set_mail << distribution["MAIL"].load();
    auto set_file = new QBarSet("FILE");
    *set_file << distribution["FILE"].load();
    auto set_hypertext = new QBarSet("HYPERTEXT");
    *set_hypertext << distribution["HYPERTEXT"].load();


    bar_series->append(set_mail);
    bar_series->append(set_file);
    bar_series->append(set_hypertext);


    auto *dialog = new QDialog(this);
    dialog->setModal(false);
    dialog->setDisabled(false);
    dialog->setMinimumHeight(500);
    dialog->setMinimumWidth(500);

    auto *chart = new QChart;
    chart->addSeries(bar_series);
    chart->createDefaultAxes();
    chart->setTitle("Distribution of packages");

    auto *chartView = new QChartView(chart, dialog);
    chartView->setRenderHint(QPainter::Antialiasing);

    dialog->setLayout(new QVBoxLayout());
    dialog->layout()->addWidget(chartView);

    dialog->exec();
    delete dialog;
}

void TableViewer::exit() {
    QCoreApplication::quit();
}
