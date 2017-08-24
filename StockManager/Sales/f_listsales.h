#ifndef F_LISTSALES_H
#define F_LISTSALES_H

#include <QFrame>

namespace Ui {
class F_ListSales;
}

class F_ListSales : public QFrame
{
    Q_OBJECT

public:
    explicit F_ListSales(QWidget *parent = 0);
    ~F_ListSales();

private:
    Ui::F_ListSales *ui;
};

#endif // F_LISTSALES_H
