#ifndef F_SALESREPORT_H
#define F_SALESREPORT_H

#include <QFrame>

namespace Ui {
class F_SalesReport;
}

class F_SalesReport : public QFrame
{
    Q_OBJECT

public:
    explicit F_SalesReport(QWidget *parent = 0);
    ~F_SalesReport();

private:
    Ui::F_SalesReport *ui;
};

#endif // F_SALESREPORT_H
