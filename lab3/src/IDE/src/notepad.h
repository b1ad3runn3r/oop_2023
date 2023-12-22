#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class Notepad;
}
QT_END_NAMESPACE

class Notepad: public QMainWindow {
    Q_OBJECT
    public:
        explicit Notepad(QWidget *parent = nullptr);
        ~Notepad() override;

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
        void about();
        static void run();
        void documentWasModified();

    private:
        Ui::Notepad *ui;
        QString currentFile;
        void createStatusBar();
};

#endif
