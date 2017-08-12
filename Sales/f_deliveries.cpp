#include "f_deliveries.h"
#include "ui_f_deliveries.h"

F_Deliveries::F_Deliveries(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_Deliveries)
{
    ui->setupUi(this);
}

F_Deliveries::~F_Deliveries()
{
    delete ui;
}
