#include "f_addsalebycsv.h"
#include "ui_f_addsalebycsv.h"

F_AddSaleByCSV::F_AddSaleByCSV(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_AddSaleByCSV)
{
    ui->setupUi(this);
}

F_AddSaleByCSV::~F_AddSaleByCSV()
{
    delete ui;
}
