#ifndef F_ADDEXPENSE_H
#define F_ADDEXPENSE_H

#include <QFrame>

namespace Ui {
class F_AddExpense;
}

class F_AddExpense : public QFrame
{
    Q_OBJECT

public:
    explicit F_AddExpense(QWidget *parent = 0);
    ~F_AddExpense();

private:
    Ui::F_AddExpense *ui;
};

#endif // F_ADDEXPENSE_H
