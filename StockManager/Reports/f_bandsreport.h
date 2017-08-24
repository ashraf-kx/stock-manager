#ifndef F_BANDSREPORT_H
#define F_BANDSREPORT_H

#include <QFrame>

namespace Ui {
class F_BandsReport;
}

class F_BandsReport : public QFrame
{
    Q_OBJECT

public:
    explicit F_BandsReport(QWidget *parent = 0);
    ~F_BandsReport();

private:
    Ui::F_BandsReport *ui;
};

#endif // F_BANDSREPORT_H
