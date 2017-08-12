#include "f_grouppermissions.h"
#include "ui_f_grouppermissions.h"

F_GroupPermissions::F_GroupPermissions(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_GroupPermissions)
{
    ui->setupUi(this);
}

F_GroupPermissions::~F_GroupPermissions()
{
    delete ui;
}
