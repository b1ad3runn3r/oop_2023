#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class Editor;
}
QT_END_NAMESPACE

class Editor: public QMainWindow {
    Q_OBJECT
    public:
        explicit Editor(QWidget *parent = nullptr);
        ~Editor() override;

    private slots:
        void newDocument();
        void open();
        void save();
        void saveAs();
        static void exit();
        void copy();
        void cut();
        void paste();
        void undo();
        void redo();
        void zoomOut();
        void zoomIn();
        static void run();
        void documentWasModified();

    private:
        Ui::Editor *ui;
        QString currentFile;
        void createStatusBar();
};

#endif
