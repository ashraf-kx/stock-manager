#include "f_listsales.h"
#include "ui_f_listsales.h"

F_ListSales::F_ListSales(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_ListSales)
{
    ui->setupUi(this);
}

F_ListSales::~F_ListSales()
{
    delete ui;
}
