#include "f_possales.h"
#include "ui_f_possales.h"

F_POSSales::F_POSSales(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_POSSales)
{
    ui->setupUi(this);
}

F_POSSales::~F_POSSales()
{
    delete ui;
}
