#ifndef F_LISTSUPPLIERS_H
#define F_LISTSUPPLIERS_H

#include <QFrame>

namespace Ui {
class F_ListSuppliers;
}

class F_ListSuppliers : public QFrame
{
    Q_OBJECT

public:
    explicit F_ListSuppliers(QWidget *parent = 0);
    ~F_ListSuppliers();

private:
    Ui::F_ListSuppliers *ui;
};

#endif // F_LISTSUPPLIERS_H
