#ifndef F_PRINTBARCODE_H
#define F_PRINTBARCODE_H

#include <QFrame>

namespace Ui {
class F_PrintBarcode;
}

class F_PrintBarcode : public QFrame
{
    Q_OBJECT

public:
    explicit F_PrintBarcode(QWidget *parent = 0);
    ~F_PrintBarcode();

private:
    Ui::F_PrintBarcode *ui;
};

#endif // F_PRINTBARCODE_H
