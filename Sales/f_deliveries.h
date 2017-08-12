#ifndef F_DELIVERIES_H
#define F_DELIVERIES_H

#include <QFrame>

namespace Ui {
class F_Deliveries;
}

class F_Deliveries : public QFrame
{
    Q_OBJECT

public:
    explicit F_Deliveries(QWidget *parent = 0);
    ~F_Deliveries();

private:
    Ui::F_Deliveries *ui;
};

#endif // F_DELIVERIES_H
