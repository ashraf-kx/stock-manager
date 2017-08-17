#ifndef F_DAILYSALES_H
#define F_DAILYSALES_H

#include <QFrame>

namespace Ui {
class F_DailySales;
}

class F_DailySales : public QFrame
{
    Q_OBJECT

public:
    explicit F_DailySales(QWidget *parent = 0);
    ~F_DailySales();

private:
    Ui::F_DailySales *ui;
};

#endif // F_DAILYSALES_H
