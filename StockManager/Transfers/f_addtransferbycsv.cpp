#include "f_addtransferbycsv.h"
#include "ui_f_addtransferbycsv.h"

F_AddTransferByCSV::F_AddTransferByCSV(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_AddTransferByCSV)
{
    ui->setupUi(this);
}

F_AddTransferByCSV::~F_AddTransferByCSV()
{
    delete ui;
}
