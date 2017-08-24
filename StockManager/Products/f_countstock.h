#ifndef F_COUNTSTOCK_H
#define F_COUNTSTOCK_H

#include <QFrame>

namespace Ui {
class F_CountStock;
}

class F_CountStock : public QFrame
{
    Q_OBJECT

public:
    explicit F_CountStock(QWidget *parent = 0);
    ~F_CountStock();

private:
    Ui::F_CountStock *ui;
};

#endif // F_COUNTSTOCK_H
