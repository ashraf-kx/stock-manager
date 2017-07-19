#include "f_listusers.h"
#include "ui_f_listusers.h"

F_ListUsers::F_ListUsers(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_ListUsers)
{
    ui->setupUi(this);
}

F_ListUsers::~F_ListUsers()
{
    delete ui;
}
