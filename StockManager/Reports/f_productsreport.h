#ifndef F_PRODUCTSREPORT_H
#define F_PRODUCTSREPORT_H

#include <QFrame>

namespace Ui {
class F_ProductsReport;
}

class F_ProductsReport : public QFrame
{
    Q_OBJECT

public:
    explicit F_ProductsReport(QWidget *parent = 0);
    ~F_ProductsReport();

private:
    Ui::F_ProductsReport *ui;
};

#endif // F_PRODUCTSREPORT_H
