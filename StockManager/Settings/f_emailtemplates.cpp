#include "f_emailtemplates.h"
#include "ui_f_emailtemplates.h"

F_EmailTemplates::F_EmailTemplates(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_EmailTemplates)
{
    ui->setupUi(this);
}

F_EmailTemplates::~F_EmailTemplates()
{
    delete ui;
}
