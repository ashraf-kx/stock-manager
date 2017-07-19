#ifndef F_ADDSUPPLIER_H
#define F_ADDSUPPLIER_H

#include <QFrame>

namespace Ui {
class F_AddSupplier;
}

class F_AddSupplier : public QFrame
{
    Q_OBJECT

public:
    explicit F_AddSupplier(QWidget *parent = 0);
    ~F_AddSupplier();

private:
    Ui::F_AddSupplier *ui;
};

#endif // F_ADDSUPPLIER_H
