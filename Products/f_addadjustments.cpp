#include "f_addadjustments.h"
#include "ui_f_addadjustments.h"

F_AddAdjustments::F_AddAdjustments(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_AddAdjustments)
{
    ui->setupUi(this);
}

F_AddAdjustments::~F_AddAdjustments()
{
    delete ui;
}
