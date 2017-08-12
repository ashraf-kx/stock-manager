#ifndef F_REGISTERREPORT_H
#define F_REGISTERREPORT_H

#include <QFrame>

namespace Ui {
class F_RegisterReport;
}

class F_RegisterReport : public QFrame
{
    Q_OBJECT

public:
    explicit F_RegisterReport(QWidget *parent = 0);
    ~F_RegisterReport();

private:
    Ui::F_RegisterReport *ui;
};

#endif // F_REGISTERREPORT_H
