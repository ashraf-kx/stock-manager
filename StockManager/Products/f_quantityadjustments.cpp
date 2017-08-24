#include "f_quantityadjustments.h"
#include "ui_f_quantityadjustments.h"

F_QuantityAdjustments::F_QuantityAdjustments(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_QuantityAdjustments)
{
    ui->setupUi(this);
}

F_QuantityAdjustments::~F_QuantityAdjustments()
{
    delete ui;
}
