#ifndef F_ADDPURCHASESBYCSV_H
#define F_ADDPURCHASESBYCSV_H

#include <QFrame>

namespace Ui {
class F_AddPurchasesByCSV;
}

class F_AddPurchasesByCSV : public QFrame
{
    Q_OBJECT

public:
    explicit F_AddPurchasesByCSV(QWidget *parent = 0);
    ~F_AddPurchasesByCSV();

private:
    Ui::F_AddPurchasesByCSV *ui;
};

#endif // F_ADDPURCHASESBYCSV_H
