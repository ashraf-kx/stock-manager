#include "f_listcustomers.h"
#include "ui_f_listcustomers.h"

F_ListCustomers::F_ListCustomers(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_ListCustomers)
{
    ui->setupUi(this);
}

F_ListCustomers::~F_ListCustomers()
{
    delete ui;
}
