#ifndef F_ADJUTMENTSREPORT_H
#define F_ADJUTMENTSREPORT_H

#include <QFrame>

namespace Ui {
class F_AdjutmentsReport;
}

class F_AdjutmentsReport : public QFrame
{
    Q_OBJECT

public:
    explicit F_AdjutmentsReport(QWidget *parent = 0);
    ~F_AdjutmentsReport();

private:
    Ui::F_AdjutmentsReport *ui;
};

#endif // F_ADJUTMENTSREPORT_H
