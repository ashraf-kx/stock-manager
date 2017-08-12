#ifndef F_LISTGIFTCARDS_H
#define F_LISTGIFTCARDS_H

#include <QFrame>

namespace Ui {
class F_ListGiftCards;
}

class F_ListGiftCards : public QFrame
{
    Q_OBJECT

public:
    explicit F_ListGiftCards(QWidget *parent = 0);
    ~F_ListGiftCards();

private:
    Ui::F_ListGiftCards *ui;
};

#endif // F_LISTGIFTCARDS_H
