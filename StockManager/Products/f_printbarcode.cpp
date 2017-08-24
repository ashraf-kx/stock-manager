#include "f_printbarcode.h"
#include "ui_f_printbarcode.h"

F_PrintBarcode::F_PrintBarcode(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_PrintBarcode)
{
    ui->setupUi(this);
}

F_PrintBarcode::~F_PrintBarcode()
{
    delete ui;
}
