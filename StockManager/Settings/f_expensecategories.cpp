#include "f_expensecategories.h"
#include "ui_f_expensecategories.h"

F_ExpenseCategories::F_ExpenseCategories(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_ExpenseCategories)
{
    ui->setupUi(this);
}

F_ExpenseCategories::~F_ExpenseCategories()
{
    delete ui;
}
