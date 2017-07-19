#include "f_adduser.h"
#include "ui_f_adduser.h"

F_AddUser::F_AddUser(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_AddUser)
{
    ui->setupUi(this);
}

F_AddUser::~F_AddUser()
{
    delete ui;
}
