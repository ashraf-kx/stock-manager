#include "f_addbiller.h"
#include "ui_f_addbiller.h"

F_AddBiller::F_AddBiller(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_AddBiller)
{
    ui->setupUi(this);
}

F_AddBiller::~F_AddBiller()
{
    delete ui;
}
