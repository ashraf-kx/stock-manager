#include "f_listexpenses.h"
#include "ui_f_listexpenses.h"

F_ListExpenses::F_ListExpenses(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_ListExpenses)
{
    ui->setupUi(this);
}

F_ListExpenses::~F_ListExpenses()
{
    delete ui;
}
