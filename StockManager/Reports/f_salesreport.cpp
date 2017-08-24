#include "f_salesreport.h"
#include "ui_f_salesreport.h"

F_SalesReport::F_SalesReport(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_SalesReport)
{
    ui->setupUi(this);
}

F_SalesReport::~F_SalesReport()
{
    delete ui;
}
