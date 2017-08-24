#ifndef F_ADDPURCHASE_H
#define F_ADDPURCHASE_H

#include <QFrame>

namespace Ui {
class F_AddPurchase;
}

class F_AddPurchase : public QFrame
{
    Q_OBJECT

public:
    explicit F_AddPurchase(QWidget *parent = 0);
    ~F_AddPurchase();

private:
    Ui::F_AddPurchase *ui;
};

#endif // F_ADDPURCHASE_H
