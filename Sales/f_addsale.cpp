#include "f_addsale.h"
#include "ui_f_addsale.h"

F_AddSale::F_AddSale(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_AddSale)
{
    ui->setupUi(this);
}

F_AddSale::~F_AddSale()
{
    delete ui;
}
