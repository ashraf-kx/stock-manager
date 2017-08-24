#ifndef F_LISTPURCHASES_H
#define F_LISTPURCHASES_H

#include <QFrame>

namespace Ui {
class F_ListPurchases;
}

class F_ListPurchases : public QFrame
{
    Q_OBJECT

public:
    explicit F_ListPurchases(QWidget *parent = 0);
    ~F_ListPurchases();

private:
    Ui::F_ListPurchases *ui;
};

#endif // F_LISTPURCHASES_H
