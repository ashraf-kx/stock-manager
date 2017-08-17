#include "f_addexpense.h"
#include "ui_f_addexpense.h"

F_AddExpense::F_AddExpense(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_AddExpense)
{
    ui->setupUi(this);
}

F_AddExpense::~F_AddExpense()
{
    delete ui;
}
