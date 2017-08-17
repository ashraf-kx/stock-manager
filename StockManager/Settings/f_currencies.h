#ifndef F_CURRENCIES_H
#define F_CURRENCIES_H

#include <QFrame>

namespace Ui {
class F_Currencies;
}

class F_Currencies : public QFrame
{
    Q_OBJECT

public:
    explicit F_Currencies(QWidget *parent = 0);
    ~F_Currencies();

private:
    Ui::F_Currencies *ui;
};

#endif // F_CURRENCIES_H
