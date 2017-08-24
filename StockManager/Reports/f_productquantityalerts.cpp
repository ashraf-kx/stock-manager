#include "f_productquantityalerts.h"
#include "ui_f_productquantityalerts.h"

F_ProductQuantityAlerts::F_ProductQuantityAlerts(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_ProductQuantityAlerts)
{
    ui->setupUi(this);
}

F_ProductQuantityAlerts::~F_ProductQuantityAlerts()
{
    delete ui;
}
