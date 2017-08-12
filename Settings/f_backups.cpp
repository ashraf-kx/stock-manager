#include "f_backups.h"
#include "ui_f_backups.h"

F_BackUps::F_BackUps(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_BackUps)
{
    ui->setupUi(this);
}

F_BackUps::~F_BackUps()
{
    delete ui;
}
