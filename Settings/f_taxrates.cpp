#include "f_taxrates.h"
#include "ui_f_taxrates.h"

F_TaxRates::F_TaxRates(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_TaxRates)
{
    ui->setupUi(this);
}

F_TaxRates::~F_TaxRates()
{
    delete ui;
}
