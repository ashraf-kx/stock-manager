#include "f_addcustomer.h"
#include "ui_f_addcustomer.h"

F_AddCustomer::F_AddCustomer(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_AddCustomer)
{
    ui->setupUi(this);
}

F_AddCustomer::~F_AddCustomer()
{
    delete ui;
}
