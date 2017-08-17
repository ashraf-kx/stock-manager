#ifndef F_LISTEXPENSES_H
#define F_LISTEXPENSES_H

#include <QFrame>

namespace Ui {
class F_ListExpenses;
}

class F_ListExpenses : public QFrame
{
    Q_OBJECT

public:
    explicit F_ListExpenses(QWidget *parent = 0);
    ~F_ListExpenses();

private:
    Ui::F_ListExpenses *ui;
};

#endif // F_LISTEXPENSES_H
