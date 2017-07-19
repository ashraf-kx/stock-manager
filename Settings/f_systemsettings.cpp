#include "f_systemsettings.h"
#include "ui_f_systemsettings.h"

F_SystemSettings::F_SystemSettings(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_SystemSettings)
{
    ui->setupUi(this);
}

F_SystemSettings::~F_SystemSettings()
{
    delete ui;
}
