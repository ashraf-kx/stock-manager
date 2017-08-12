#include "f_updates.h"
#include "ui_f_updates.h"

F_Updates::F_Updates(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_Updates)
{
    ui->setupUi(this);
}

F_Updates::~F_Updates()
{
    delete ui;
}
