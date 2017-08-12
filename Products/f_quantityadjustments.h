#ifndef F_QUANTITYADJUSTMENTS_H
#define F_QUANTITYADJUSTMENTS_H

#include <QFrame>

namespace Ui {
class F_QuantityAdjustments;
}

class F_QuantityAdjustments : public QFrame
{
    Q_OBJECT

public:
    explicit F_QuantityAdjustments(QWidget *parent = 0);
    ~F_QuantityAdjustments();

private:
    Ui::F_QuantityAdjustments *ui;
};

#endif // F_QUANTITYADJUSTMENTS_H
