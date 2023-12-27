#ifndef CREATE_DIALOG_H
#define CREATE_DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
    class CreateDialog;
}
QT_END_NAMESPACE

class CreateDialog : public QDialog {
    Q_OBJECT
public:
    explicit CreateDialog(QString title, QWidget *parent = nullptr);
    ~CreateDialog() override;
    bool wasCancelled();
    bool setDialogElements();
    bool addComboBox(QString caption, QString barSepList, int *selIdx);


private slots:

private:
    Ui::CreateDialog *ui;
};

#endif // CREATE_DIALOG_H
