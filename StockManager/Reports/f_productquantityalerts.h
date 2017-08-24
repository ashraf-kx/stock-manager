#ifndef F_PRODUCTQUANTITYALERTS_H
#define F_PRODUCTQUANTITYALERTS_H

#include <QFrame>

namespace Ui {
class F_ProductQuantityAlerts;
}

class F_ProductQuantityAlerts : public QFrame
{
    Q_OBJECT

public:
    explicit F_ProductQuantityAlerts(QWidget *parent = 0);
    ~F_ProductQuantityAlerts();

private:
    Ui::F_ProductQuantityAlerts *ui;
};

#endif // F_PRODUCTQUANTITYALERTS_H
