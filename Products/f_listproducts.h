#ifndef F_LISTPRODUCTS_H
#define F_LISTPRODUCTS_H

#include <QFrame>

namespace Ui {
class F_ListProducts;
}

class F_ListProducts : public QFrame
{
    Q_OBJECT

public:
    explicit F_ListProducts(QWidget *parent = 0);
    ~F_ListProducts();

private:
    Ui::F_ListProducts *ui;
};

#endif // F_LISTPRODUCTS_H
