#include "f_listquotations.h"
#include "ui_f_listquotations.h"

F_ListQuotations::F_ListQuotations(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_ListQuotations)
{
    ui->setupUi(this);
}

F_ListQuotations::~F_ListQuotations()
{
    delete ui;
}
