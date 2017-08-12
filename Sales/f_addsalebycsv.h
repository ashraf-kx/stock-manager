#ifndef F_ADDSALEBYCSV_H
#define F_ADDSALEBYCSV_H

#include <QFrame>

namespace Ui {
class F_AddSaleByCSV;
}

class F_AddSaleByCSV : public QFrame
{
    Q_OBJECT

public:
    explicit F_AddSaleByCSV(QWidget *parent = 0);
    ~F_AddSaleByCSV();

private:
    Ui::F_AddSaleByCSV *ui;
};

#endif // F_ADDSALEBYCSV_H
