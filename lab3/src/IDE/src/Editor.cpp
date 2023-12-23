#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QFont>
#include <QString>
#include <QtGlobal>
#include <QDir>
#include <QStatusBar>
#include <QTextDocument>
#include <QClipboard>

#include "Editor.h"
#include "ui_Editor.h"

#include "config.h"

Editor::Editor(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::Editor) {
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

    setWindowTitle(QString("[*]") + default_file_name + QString(" — YAAI"));

    createStatusBar();

    connect(ui->actionNew,              &QAction::triggered,                this, &Editor::newDocument);
    connect(ui->actionOpen,             &QAction::triggered,                this, &Editor::open);
    connect(ui->actionSave,             &QAction::triggered,                this, &Editor::save);
    connect(ui->actionSave_as,          &QAction::triggered,                this, &Editor::saveAs);
    connect(ui->actionExit,             &QAction::triggered,                this, &Editor::exit);
    connect(ui->actionCopy,             &QAction::triggered,                this, &Editor::copy);
    connect(ui->actionCut,              &QAction::triggered,                this, &Editor::cut);
    connect(ui->actionPaste,            &QAction::triggered,                this, &Editor::paste);
    connect(ui->actionUndo,             &QAction::triggered,                this, &Editor::undo);
    connect(ui->actionRedo,             &QAction::triggered,                this, &Editor::redo);
    connect(ui->actionZoomOut,          &QAction::triggered,                this, &Editor::zoomOut);
    connect(ui->actionZoomIn,           &QAction::triggered,                this, &Editor::zoomIn);
    connect(ui->actionRun,              &QAction::triggered,                this, &Editor::run);
    connect(ui->textEdit->document(),   &QTextDocument::contentsChanged,    this, &Editor::documentWasModified);

    QFont font;

    font.setFamily(font_family);
    font.setStyleHint(QFont::Monospace);
    font.setFixedPitch(true);
    font.setPointSize(font_size);

    ui->textEdit->setFont(font);
    ui->textEdit->setAcceptRichText(false);

    if (QApplication::arguments().size() > 1) {
    QString fileName = QApplication::arguments().at(1);
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    QString text = QString::fromUtf8(file.readAll());
    ui->textEdit->setText(text);
    ui->textEdit->document()->setModified(false);
    setWindowModified(false);
    setWindowTitle(QString("[*]") + fileName + QString(" — YAAI"));
    file.close();
    statusBar()->showMessage("File opened", status_bar_message_timeout);
    }

    ui->textEdit->setTabStopDistance(tab_size * 10);
}

Editor::~Editor() {
    delete ui;
}

void Editor::createStatusBar() {
    statusBar()->showMessage("YAAI");
}

void Editor::newDocument() {
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void Editor::open() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file", QDir::homePath(), "Assembly files (*.asm);;All files (*)");
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    QString text = QString::fromUtf8(file.readAll());
    ui->textEdit->setText(text);
    ui->textEdit->document()->setModified(false);
    setWindowModified(false);
    setWindowTitle(QString("[*]") + fileName + QString(" — Editor"));
    file.close();
    statusBar()->showMessage("File opened", status_bar_message_timeout);
}

void Editor::save() {
    QString fileName;
    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save", QDir::homePath(), "Text files (*.txt);;All files (*)");
        currentFile = fileName;
    }
    else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    file.write(ui->textEdit->toPlainText().toUtf8());
    ui->textEdit->document()->setModified(false);
    setWindowModified(false);
    setWindowTitle(QString("[*]") + fileName + QString(" — YAAI"));
    file.close();
    statusBar()->showMessage("File saved", status_bar_message_timeout);
}

void Editor::saveAs() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save as", QDir::homePath(), "Assembly files (*.asm);;All files (*)");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
}

    currentFile = fileName;

    file.write(ui->textEdit->toPlainText().toUtf8());
    ui->textEdit->document()->setModified(false);
    setWindowModified(false);
    setWindowTitle(QString("[*]") + fileName + QString(" — YAAI"));
    file.close();
    statusBar()->showMessage("File saved", status_bar_message_timeout);
}

void Editor::exit() {
    QCoreApplication::quit();
}

void Editor::copy() {
    ui->textEdit->copy();
}

void Editor::cut() {
    ui->textEdit->cut();
}

void Editor::paste() {
    ui->textEdit->paste();
}

void Editor::undo() {
    ui->textEdit->undo();
}

void Editor::redo() {
    ui->textEdit->redo();
}

void Editor::zoomOut() {
    ui->textEdit->zoomOut(zoom_range);
}

void Editor::zoomIn() {
    ui->textEdit->zoomIn(zoom_range);
}

void Editor::run() {
    return ;
}

void Editor::documentWasModified() {
    setWindowModified(ui->textEdit->document()->isModified());
}
