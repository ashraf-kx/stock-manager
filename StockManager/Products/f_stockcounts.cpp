#include "f_stockcounts.h"
#include "ui_f_stockcounts.h"

F_StockCounts::F_StockCounts(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_StockCounts)
{
    ui->setupUi(this);
}

F_StockCounts::~F_StockCounts()
{
    delete ui;
}
