#include "f_currencies.h"
#include "ui_f_currencies.h"

F_Currencies::F_Currencies(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_Currencies)
{
    ui->setupUi(this);
}

F_Currencies::~F_Currencies()
{
    delete ui;
}
