#ifndef F_EXPENSECATEGORIES_H
#define F_EXPENSECATEGORIES_H

#include <QFrame>

namespace Ui {
class F_ExpenseCategories;
}

class F_ExpenseCategories : public QFrame
{
    Q_OBJECT

public:
    explicit F_ExpenseCategories(QWidget *parent = 0);
    ~F_ExpenseCategories();

private:
    Ui::F_ExpenseCategories *ui;
};

#endif // F_EXPENSECATEGORIES_H
