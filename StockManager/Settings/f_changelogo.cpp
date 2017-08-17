#include "f_changelogo.h"
#include "ui_f_changelogo.h"

F_ChangeLogo::F_ChangeLogo(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_ChangeLogo)
{
    ui->setupUi(this);
}

F_ChangeLogo::~F_ChangeLogo()
{
    delete ui;
}
