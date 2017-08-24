#include "f_importproducts.h"
#include "ui_f_importproducts.h"

F_ImportProducts::F_ImportProducts(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_ImportProducts)
{
    ui->setupUi(this);
}

F_ImportProducts::~F_ImportProducts()
{
    delete ui;
}
