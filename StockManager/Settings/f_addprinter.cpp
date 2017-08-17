#include "f_addprinter.h"
#include "ui_f_addprinter.h"

F_AddPrinter::F_AddPrinter(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_AddPrinter)
{
    ui->setupUi(this);
}

F_AddPrinter::~F_AddPrinter()
{
    delete ui;
}
