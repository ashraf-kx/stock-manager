#include "f_addpurchasesbycsv.h"
#include "ui_f_addpurchasesbycsv.h"

F_AddPurchasesByCSV::F_AddPurchasesByCSV(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_AddPurchasesByCSV)
{
    ui->setupUi(this);
}

F_AddPurchasesByCSV::~F_AddPurchasesByCSV()
{
    delete ui;
}
