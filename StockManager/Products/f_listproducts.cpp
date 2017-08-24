#include "f_listproducts.h"
#include "ui_f_listproducts.h"

F_ListProducts::F_ListProducts(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_ListProducts)
{
    ui->setupUi(this);
}

F_ListProducts::~F_ListProducts()
{
    delete ui;
}
