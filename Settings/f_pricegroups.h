#ifndef F_PRICEGROUPS_H
#define F_PRICEGROUPS_H

#include <QFrame>

namespace Ui {
class F_PriceGroups;
}

class F_PriceGroups : public QFrame
{
    Q_OBJECT

public:
    explicit F_PriceGroups(QWidget *parent = 0);
    ~F_PriceGroups();

private:
    Ui::F_PriceGroups *ui;
};

#endif // F_PRICEGROUPS_H
