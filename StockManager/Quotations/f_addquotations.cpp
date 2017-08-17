#include "f_addquotations.h"
#include "ui_f_addquotations.h"

F_AddQuotations::F_AddQuotations(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_AddQuotations)
{
    ui->setupUi(this);
}

F_AddQuotations::~F_AddQuotations()
{
    delete ui;
}
