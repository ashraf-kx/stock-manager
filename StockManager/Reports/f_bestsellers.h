#ifndef F_BESTSELLERS_H
#define F_BESTSELLERS_H

#include <QFrame>

namespace Ui {
class F_BestSellers;
}

class F_BestSellers : public QFrame
{
    Q_OBJECT

public:
    explicit F_BestSellers(QWidget *parent = 0);
    ~F_BestSellers();

private:
    Ui::F_BestSellers *ui;
};

#endif // F_BESTSELLERS_H
