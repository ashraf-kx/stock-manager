#ifndef F_LISTTRANSFERS_H
#define F_LISTTRANSFERS_H

#include <QFrame>

namespace Ui {
class F_ListTransfers;
}

class F_ListTransfers : public QFrame
{
    Q_OBJECT

public:
    explicit F_ListTransfers(QWidget *parent = 0);
    ~F_ListTransfers();

private:
    Ui::F_ListTransfers *ui;
};

#endif // F_LISTTRANSFERS_H
