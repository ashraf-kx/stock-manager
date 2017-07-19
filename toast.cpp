#include "toast.h"
#include "ui_toast.h"
#include <QGraphicsDropShadowEffect>
#include <QDebug>

Toast::Toast(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Toast)
{
    ui->setupUi(this);
    QGraphicsDropShadowEffect * sh = new QGraphicsDropShadowEffect();
    sh->setBlurRadius(8);
    sh->setOffset(2);
    sh->setColor(QColor(63, 63, 63, 180));
    this->setGraphicsEffect(sh);

    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setWindowOpacity(0.9);
    this->setGeometry(5,30,300,80);
    this->setVisible(true);

    mTimer = new QTimer();
    mTimer->setInterval(600);
    mTimer->start();

    colorA = 255;
    connect(mTimer,SIGNAL(timeout()),this,SLOT(fade()));
}


void Toast::fade()
{
    if(colorA < 75 ) this->deleteLater();
    mTimer->setInterval(500);
    mTimer->start();
    colorA = colorA-25;
    this->setStyleSheet("background-color: rgba(178, 6, 245,"+QString::number(colorA)+");"
                        "color: rgb(255, 255, 255);"
                        "border-radius:15px;");
}

void Toast::setMessage(const QString& msg)
{
    ui->label->setText(msg);
}

Toast::~Toast()
{
    delete ui;
}
