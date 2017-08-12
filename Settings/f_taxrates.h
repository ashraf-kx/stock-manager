#ifndef F_TAXRATES_H
#define F_TAXRATES_H

#include <QFrame>

namespace Ui {
class F_TaxRates;
}

class F_TaxRates : public QFrame
{
    Q_OBJECT

public:
    explicit F_TaxRates(QWidget *parent = 0);
    ~F_TaxRates();

private:
    Ui::F_TaxRates *ui;
};

#endif // F_TAXRATES_H
