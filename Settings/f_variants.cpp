#include "f_variants.h"
#include "ui_f_variants.h"

F_Variants::F_Variants(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_Variants)
{
    ui->setupUi(this);
}

F_Variants::~F_Variants()
{
    delete ui;
}
