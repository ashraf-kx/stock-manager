#ifndef F_LISTCUSTOMERS_H
#define F_LISTCUSTOMERS_H

#include <QFrame>

namespace Ui {
class F_ListCustomers;
}

class F_ListCustomers : public QFrame
{
    Q_OBJECT

public:
    explicit F_ListCustomers(QWidget *parent = 0);
    ~F_ListCustomers();

private:
    Ui::F_ListCustomers *ui;
};

#endif // F_LISTCUSTOMERS_H
