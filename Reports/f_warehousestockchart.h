#ifndef F_WAREHOUSESTOCKCHART_H
#define F_WAREHOUSESTOCKCHART_H

#include <QFrame>

namespace Ui {
class F_WarehouseStockChart;
}

class F_WarehouseStockChart : public QFrame
{
    Q_OBJECT

public:
    explicit F_WarehouseStockChart(QWidget *parent = 0);
    ~F_WarehouseStockChart();

private:
    Ui::F_WarehouseStockChart *ui;
};

#endif // F_WAREHOUSESTOCKCHART_H
