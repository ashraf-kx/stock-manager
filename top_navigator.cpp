#include "top_navigator.h"
#include "ui_top_navigator.h"

Top_navigator::Top_navigator(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Top_navigator)
{
    ui->setupUi(this);

    QGraphicsDropShadowEffect *sh = new QGraphicsDropShadowEffect();
    sh->setBlurRadius(8);
    sh->setOffset(2);
    sh->setColor(QColor(63, 63, 63, 180));
    this->setGraphicsEffect(sh);
}

Top_navigator::~Top_navigator()
{
    delete ui;
}
