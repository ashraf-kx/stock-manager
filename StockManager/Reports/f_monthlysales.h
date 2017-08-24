#ifndef F_MONTHLYSALES_H
#define F_MONTHLYSALES_H

#include <QFrame>

namespace Ui {
class F_MonthlySales;
}

class F_MonthlySales : public QFrame
{
    Q_OBJECT

public:
    explicit F_MonthlySales(QWidget *parent = 0);
    ~F_MonthlySales();

private:
    Ui::F_MonthlySales *ui;
};

#endif // F_MONTHLYSALES_H
