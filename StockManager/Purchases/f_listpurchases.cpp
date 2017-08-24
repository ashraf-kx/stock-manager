#include "f_listpurchases.h"
#include "ui_f_listpurchases.h"

F_ListPurchases::F_ListPurchases(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_ListPurchases)
{
    ui->setupUi(this);
}

F_ListPurchases::~F_ListPurchases()
{
    delete ui;
}
