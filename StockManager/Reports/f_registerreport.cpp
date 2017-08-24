#include "f_registerreport.h"
#include "ui_f_registerreport.h"

F_RegisterReport::F_RegisterReport(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_RegisterReport)
{
    ui->setupUi(this);
}

F_RegisterReport::~F_RegisterReport()
{
    delete ui;
}
