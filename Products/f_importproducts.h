#ifndef F_IMPORTPRODUCTS_H
#define F_IMPORTPRODUCTS_H

#include <QFrame>

namespace Ui {
class F_ImportProducts;
}

class F_ImportProducts : public QFrame
{
    Q_OBJECT

public:
    explicit F_ImportProducts(QWidget *parent = 0);
    ~F_ImportProducts();

private:
    Ui::F_ImportProducts *ui;
};

#endif // F_IMPORTPRODUCTS_H
