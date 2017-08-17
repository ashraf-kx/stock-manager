#include "f_pricegroups.h"
#include "ui_f_pricegroups.h"

F_PriceGroups::F_PriceGroups(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_PriceGroups)
{
    ui->setupUi(this);
}

F_PriceGroups::~F_PriceGroups()
{
    delete ui;
}
