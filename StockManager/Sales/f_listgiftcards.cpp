#include "f_listgiftcards.h"
#include "ui_f_listgiftcards.h"

F_ListGiftCards::F_ListGiftCards(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_ListGiftCards)
{
    ui->setupUi(this);
}

F_ListGiftCards::~F_ListGiftCards()
{
    delete ui;
}
