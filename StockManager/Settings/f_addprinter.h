#ifndef F_ADDPRINTER_H
#define F_ADDPRINTER_H

#include <QFrame>

namespace Ui {
class F_AddPrinter;
}

class F_AddPrinter : public QFrame
{
    Q_OBJECT

public:
    explicit F_AddPrinter(QWidget *parent = 0);
    ~F_AddPrinter();

private:
    Ui::F_AddPrinter *ui;
};

#endif // F_ADDPRINTER_H
