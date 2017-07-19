#include "f_addsupplier.h"
#include "ui_f_addsupplier.h"

F_AddSupplier::F_AddSupplier(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_AddSupplier)
{
    ui->setupUi(this);
}

F_AddSupplier::~F_AddSupplier()
{
    delete ui;
}
