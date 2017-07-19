#include "f_listsuppliers.h"
#include "ui_f_listsuppliers.h"

F_ListSuppliers::F_ListSuppliers(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_ListSuppliers)
{
    ui->setupUi(this);
}

F_ListSuppliers::~F_ListSuppliers()
{
    delete ui;
}
