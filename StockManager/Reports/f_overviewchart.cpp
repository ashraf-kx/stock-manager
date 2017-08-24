#include "f_overviewchart.h"
#include "ui_f_overviewchart.h"

F_OverViewChart::F_OverViewChart(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_OverViewChart)
{
    ui->setupUi(this);
}

F_OverViewChart::~F_OverViewChart()
{
    delete ui;
}
