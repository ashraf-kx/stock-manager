#include "f_listprinters.h"
#include "ui_f_listprinters.h"

F_ListPrinters::F_ListPrinters(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_ListPrinters)
{
    ui->setupUi(this);
}

F_ListPrinters::~F_ListPrinters()
{
    delete ui;
}
