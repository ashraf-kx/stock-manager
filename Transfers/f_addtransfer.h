#ifndef F_ADDTRANSFER_H
#define F_ADDTRANSFER_H

#include <QFrame>

namespace Ui {
class F_AddTransfer;
}

class F_AddTransfer : public QFrame
{
    Q_OBJECT

public:
    explicit F_AddTransfer(QWidget *parent = 0);
    ~F_AddTransfer();

private:
    Ui::F_AddTransfer *ui;
};

#endif // F_ADDTRANSFER_H
