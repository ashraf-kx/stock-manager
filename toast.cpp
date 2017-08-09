#include "toast.h"
#include "ui_toast.h"

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
    this->setVisible(true);

    animSlideOut = new QPropertyAnimation(this, "geometry");

    animSlideOut->setDuration(200);
    animSlideOut->setStartValue(QRect(1,3, 1, 150));
    animSlideOut->setEndValue(QRect(1,3, 250, 150));
    animSlideOut->setEasingCurve(QEasingCurve::OutSine);

    animSlideIn = new QPropertyAnimation(this, "geometry");

    animSlideIn->setDuration(200);
    animSlideIn->setStartValue(QRect(1,3, 250, 150));
    animSlideIn->setEndValue(QRect(1,3, 1, 150));
    animSlideIn->setEasingCurve(QEasingCurve::InSine);

    QTimer *mTimer = new  QTimer();
    mTimer->setInterval(2750);

    connect(animSlideOut,SIGNAL(finished()),mTimer,SLOT(start()));
    connect(mTimer,SIGNAL(timeout()),this,SLOT(slideInStart()));
    connect(animSlideIn,SIGNAL(finished()),this,SLOT(close()));

}

void Toast::slideInStart()
{
    animSlideIn->start();
}

void Toast::show(const QString &message, const QString& style)
{

    this->setStyleSheet(style);
    ui->label->setText(message);

    animSlideOut->start();
}

Toast::~Toast()
{
    delete ui;
}
