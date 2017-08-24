#include "f_monthlysales.h"
#include "ui_f_monthlysales.h"

F_MonthlySales::F_MonthlySales(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_MonthlySales)
{
    ui->setupUi(this);
}

F_MonthlySales::~F_MonthlySales()
{
    delete ui;
}
