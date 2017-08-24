#ifndef F_OVERVIEWCHART_H
#define F_OVERVIEWCHART_H

#include <QFrame>

namespace Ui {
class F_OverViewChart;
}

class F_OverViewChart : public QFrame
{
    Q_OBJECT

public:
    explicit F_OverViewChart(QWidget *parent = 0);
    ~F_OverViewChart();

private:
    Ui::F_OverViewChart *ui;
};

#endif // F_OVERVIEWCHART_H
