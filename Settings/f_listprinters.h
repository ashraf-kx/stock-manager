#ifndef F_LISTPRINTERS_H
#define F_LISTPRINTERS_H

#include <QFrame>

namespace Ui {
class F_ListPrinters;
}

class F_ListPrinters : public QFrame
{
    Q_OBJECT

public:
    explicit F_ListPrinters(QWidget *parent = 0);
    ~F_ListPrinters();

private:
    Ui::F_ListPrinters *ui;
};

#endif // F_LISTPRINTERS_H
