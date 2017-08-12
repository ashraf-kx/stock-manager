#include "f_bestsellers.h"
#include "ui_f_bestsellers.h"

F_BestSellers::F_BestSellers(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_BestSellers)
{
    ui->setupUi(this);
}

F_BestSellers::~F_BestSellers()
{
    delete ui;
}
