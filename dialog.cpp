#include "dialog.h"
#include "ui_dialog.h"
#include <QGraphicsDropShadowEffect>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    this->setWindowModality(Qt::WindowModal);
    this->setModal(true);
    //QApplication::processEvents();

    QGraphicsDropShadowEffect * sh = new QGraphicsDropShadowEffect();
    sh->setBlurRadius(8);
    sh->setOffset(2);
    sh->setColor(QColor(63, 63, 63, 180));
    ui->frame->setGraphicsEffect(sh);

    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::Popup);

    ui->frame->setWindowOpacity(0.99);

    animSlideOut = new QPropertyAnimation(ui->frame, "size");

    animSlideOut->setDuration(2000);
    animSlideOut->setStartValue(QSize(350,0));
    animSlideOut->setEndValue(QSize(350, 180));
    animSlideOut->setEasingCurve(QEasingCurve::OutSine);

    connect(ui->Bt_yes,SIGNAL(clicked()),this,SLOT(accept()));
    connect(ui->Bt_no,SIGNAL(clicked()),this,SLOT(reject()));

}

void Dialog::setMessage(const QString& msg,const QString& typeM)
{
    ui->labelMessage->setText(msg);
    animSlideOut->start();
    if(typeM == "warning")
        ui->icon->setPixmap(QPixmap("::/icons/48x48/ic_format_list_bulleted_white_2x.png"));
    if(typeM == "error")
        ui->icon->setPixmap(QPixmap("::/icons/48x48/ic_format_list_bulleted_white_2x.png"));
    if(typeM == "question")
        ui->icon->setPixmap(QPixmap("::/icons/48x48/ic_format_list_bulleted_white_2x.png"));
    if(typeM == "done")
        ui->icon->setPixmap(QPixmap("::/icons/48x48/ic_format_list_bulleted_white_2x.png"));

}

Dialog::~Dialog()
{
    delete ui;
}
