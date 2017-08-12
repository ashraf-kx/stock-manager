#include "f_warehousestockchart.h"
#include "ui_f_warehousestockchart.h"

F_WarehouseStockChart::F_WarehouseStockChart(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_WarehouseStockChart)
{
    ui->setupUi(this);
}

F_WarehouseStockChart::~F_WarehouseStockChart()
{
    delete ui;
}
