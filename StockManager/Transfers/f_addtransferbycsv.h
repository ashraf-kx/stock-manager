#ifndef F_ADDTRANSFERBYCSV_H
#define F_ADDTRANSFERBYCSV_H

#include <QFrame>

namespace Ui {
class F_AddTransferByCSV;
}

class F_AddTransferByCSV : public QFrame
{
    Q_OBJECT

public:
    explicit F_AddTransferByCSV(QWidget *parent = 0);
    ~F_AddTransferByCSV();

private:
    Ui::F_AddTransferByCSV *ui;
};

#endif // F_ADDTRANSFERBYCSV_H
