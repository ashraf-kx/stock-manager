#include "f_listtransfers.h"
#include "ui_f_listtransfers.h"

F_ListTransfers::F_ListTransfers(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_ListTransfers)
{
    ui->setupUi(this);
}

F_ListTransfers::~F_ListTransfers()
{
    delete ui;
}
