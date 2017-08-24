#include "f_listbillers.h"
#include "ui_f_listbillers.h"

F_ListBillers::F_ListBillers(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_ListBillers)
{
    ui->setupUi(this);
}

F_ListBillers::~F_ListBillers()
{
    delete ui;
}
