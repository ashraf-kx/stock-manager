#ifndef F_ADDPRODUCTS_H
#define F_ADDPRODUCTS_H

#include <QFrame>
#include "../classes.h"

namespace Ui {
class F_AddProducts;
}

class F_AddProducts : public QFrame
{
    Q_OBJECT

public:
    explicit F_AddProducts(QWidget *parent = 0);
    ~F_AddProducts();

private:
    Ui::F_AddProducts *ui;
    DB *DBH;
};

#endif // F_ADDPRODUCTS_H
