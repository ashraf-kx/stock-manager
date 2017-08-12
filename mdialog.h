#ifndef MDIALOG_H
#define MDIALOG_H

#include <QWidget>
#include <dialog.h>

namespace Ui {
class MDialog;
}

class MDialog : public QWidget
{
    Q_OBJECT

public:
    explicit MDialog(QWidget *parent = 0);
    ~MDialog();

public slots:
    void setMessage(const QString &message);
    int exec();
    Dialog *getDialog();
private:
    Ui::MDialog *ui;
    Dialog *mDialog;

};

#endif // MDIALOG_H
