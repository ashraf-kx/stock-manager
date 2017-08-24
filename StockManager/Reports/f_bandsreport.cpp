#include "f_bandsreport.h"
#include "ui_f_bandsreport.h"

F_BandsReport::F_BandsReport(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_BandsReport)
{
    ui->setupUi(this);
}

F_BandsReport::~F_BandsReport()
{
    delete ui;
}
