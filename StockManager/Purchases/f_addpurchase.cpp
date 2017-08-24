#include "f_addpurchase.h"
#include "ui_f_addpurchase.h"

F_AddPurchase::F_AddPurchase(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_AddPurchase)
{
    ui->setupUi(this);
}

F_AddPurchase::~F_AddPurchase()
{
    delete ui;
}
