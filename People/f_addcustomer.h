#ifndef F_ADDCUSTOMER_H
#define F_ADDCUSTOMER_H

#include <QFrame>

namespace Ui {
class F_AddCustomer;
}

class F_AddCustomer : public QFrame
{
    Q_OBJECT

public:
    explicit F_AddCustomer(QWidget *parent = 0);
    ~F_AddCustomer();

private:
    Ui::F_AddCustomer *ui;
};

#endif // F_ADDCUSTOMER_H
