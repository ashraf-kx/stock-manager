#include "f_productsreport.h"
#include "ui_f_productsreport.h"

F_ProductsReport::F_ProductsReport(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_ProductsReport)
{
    ui->setupUi(this);
}

F_ProductsReport::~F_ProductsReport()
{
    delete ui;
}
