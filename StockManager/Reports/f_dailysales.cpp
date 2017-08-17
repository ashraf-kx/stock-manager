#include "f_dailysales.h"
#include "ui_f_dailysales.h"

F_DailySales::F_DailySales(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_DailySales)
{
    ui->setupUi(this);
}

F_DailySales::~F_DailySales()
{
    delete ui;
}
