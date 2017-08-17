#include "f_addtransfer.h"
#include "ui_f_addtransfer.h"

F_AddTransfer::F_AddTransfer(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_AddTransfer)
{
    ui->setupUi(this);
}

F_AddTransfer::~F_AddTransfer()
{
    delete ui;
}
