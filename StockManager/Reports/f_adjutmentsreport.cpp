#include "f_adjutmentsreport.h"
#include "ui_f_adjutmentsreport.h"

F_AdjutmentsReport::F_AdjutmentsReport(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_AdjutmentsReport)
{
    ui->setupUi(this);
}

F_AdjutmentsReport::~F_AdjutmentsReport()
{
    delete ui;
}
