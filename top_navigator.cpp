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

//    QTimer *timer = new QTimer(this);
//    timer->setInterval(3000);
//    timer->start();

//    connect(timer,SIGNAL(timeout()),this,SLOT(updateInfo()));
//    connect(timer,SIGNAL(timeout()),timer,SLOT(start()));
}

void Top_navigator::updateInfo()
{
//    QString txt="";
//    foreach (QString name, QSqlDatabase::connectionNames()) {
//        txt += "["+name+"], ";
//    }
//    ui->label->setText(txt);

}

Top_navigator::~Top_navigator()
{
    delete ui;
}
