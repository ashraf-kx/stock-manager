#include "mdialog.h"
#include "ui_mdialog.h"
#include <QPoint>

MDialog::MDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MDialog)
{
    ui->setupUi(this);
    setParent(qApp->activeWindow());
    this->setWindowModality(Qt::WindowModal);
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    this->showMaximized();
    this->setWindowOpacity(0.35);
    this->setVisible(true);

    mDialog = new Dialog(this);
    ui->gridLayout->addWidget(mDialog,0,0);
    mDialog->setWindowOpacity(1);

    // Re-locate the Position pf the dialog.
    QSize winSize =  qApp->activeWindow()->size();
    QPoint center =  QPoint(winSize.width()/2,winSize.height()/2);
    QPoint CD     =  QPoint(mDialog->size().width()/2,mDialog->size().height()/2);
    QPoint corner =  QPoint(center.x()-CD.x(),center.y()-CD.y()-40);

    mDialog->setGeometry(QRect(corner,QSize(mDialog->size().width(),0)));

}

MDialog::~MDialog()
{
    delete ui;
}

Dialog* MDialog::getDialog()
{
    return mDialog;
}

int MDialog::exec()
{
    return mDialog->exec();
}

void MDialog::setMessage(const QString& message)
{
    mDialog->setMessage(message,"");
}
