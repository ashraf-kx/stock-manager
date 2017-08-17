#include "f_categoriesreport.h"
#include "ui_f_categoriesreport.h"

F_CategoriesReport::F_CategoriesReport(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_CategoriesReport)
{
    ui->setupUi(this);
}

F_CategoriesReport::~F_CategoriesReport()
{
    delete ui;
}
