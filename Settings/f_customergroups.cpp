#include "f_customergroups.h"
#include "ui_f_customergroups.h"

F_CustomerGroups::F_CustomerGroups(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_CustomerGroups)
{
    ui->setupUi(this);
}

F_CustomerGroups::~F_CustomerGroups()
{
    delete ui;
}
