#include "dialog.h"
#include "ui_dialog.h"
#include <QGraphicsDropShadowEffect>
#include <QGraphicsOpacityEffect>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::Popup);
    this->setModal(true);

    this->resize(310,148);

    // Aniamtion Section
    animSlideOut = new QPropertyAnimation(this, "size");

    animSlideOut->setDuration(500);
    animSlideOut->setStartValue(QSize(size().width(),0));
    animSlideOut->setEndValue(QSize(size().width(), size().height()));
    animSlideOut->setEasingCurve(QEasingCurve::OutSine);
    // FIXME : Aniamtion does not Work. ?? Fuck Fuck

    QGraphicsDropShadowEffect * sh = new QGraphicsDropShadowEffect();
    sh->setBlurRadius(8);
    sh->setOffset(3);
    sh->setColor(QColor(64, 64, 64, 180));
    this->setGraphicsEffect(sh);

    connect(ui->Bt_yes,SIGNAL(clicked()),this,SLOT(accept()));
    connect(ui->Bt_no,SIGNAL(clicked()),this,SLOT(reject()));
}

void Dialog::setMessage(const QString& msg,const QString& typeM)
{
    ui->labelMessage->setText(msg);
    if(typeM == "warning")
        ui->icon->setPixmap(QPixmap("::/icons/48x48/ic_format_list_bulleted_white_2x.png"));
    if(typeM == "error")
        ui->icon->setPixmap(QPixmap("::/icons/48x48/ic_format_list_bulleted_white_2x.png"));
    if(typeM == "question")
        ui->icon->setPixmap(QPixmap("::/icons/48x48/ic_format_list_bulleted_white_2x.png"));
    if(typeM == "done")
        ui->icon->setPixmap(QPixmap("::/icons/48x48/ic_format_list_bulleted_white_2x.png"));
    if(typeM == "")
        ui->icon->setVisible(false);

    animSlideOut->start();
}

Dialog::~Dialog()
{
    delete ui;
}
