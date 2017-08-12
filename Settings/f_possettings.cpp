#include "f_possettings.h"
#include "ui_f_possettings.h"

F_POSSettings::F_POSSettings(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_POSSettings)
{
    ui->setupUi(this);
}

F_POSSettings::~F_POSSettings()
{
    delete ui;
}
