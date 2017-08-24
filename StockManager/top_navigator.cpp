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
    isToolBoxVisible = true;
    connect(ui->Bt_toolbox,SIGNAL(clicked(bool)),this,SLOT(changeIcon()));
}

QPushButton *Top_navigator::getBtToolBox()
{
    return ui->Bt_toolbox;
}

void Top_navigator::changeIcon()
{
    if(isToolBoxVisible)
        isToolBoxVisible = false;
    else
        isToolBoxVisible = true;

    if(isToolBoxVisible)
        ui->Bt_toolbox->setIcon(QIcon(":/b/icons/b/ic_arrow_back_2x.png"));
    else
        ui->Bt_toolbox->setIcon(QIcon(":/b/icons/b/ic_list_2x.png"));
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
