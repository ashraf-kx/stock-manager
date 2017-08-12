#include "f_countstock.h"
#include "ui_f_countstock.h"

F_CountStock::F_CountStock(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_CountStock)
{
    ui->setupUi(this);
}

F_CountStock::~F_CountStock()
{
    delete ui;
}
