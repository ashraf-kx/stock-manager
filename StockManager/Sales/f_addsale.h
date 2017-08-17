#ifndef F_ADDSALE_H
#define F_ADDSALE_H

#include <QFrame>

namespace Ui {
class F_AddSale;
}

class F_AddSale : public QFrame
{
    Q_OBJECT

public:
    explicit F_AddSale(QWidget *parent = 0);
    ~F_AddSale();

private:
    Ui::F_AddSale *ui;
};

#endif // F_ADDSALE_H
