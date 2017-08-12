#ifndef F_LISTCUSTOMERS_H
#define F_LISTCUSTOMERS_H

#include <QFrame>
#include "../classes.h"

Q_DECLARE_LOGGING_CATEGORY(PLC)
namespace Ui {
class F_ListCustomers;
}

class F_ListCustomers : public QFrame
{
    Q_OBJECT

public:
    explicit F_ListCustomers(QWidget *parent = 0);
    ~F_ListCustomers();
    void createMapper();
    void keyPressEvent(QKeyEvent *e) override;
private:
    Ui::F_ListCustomers *ui;
    Toast *mToast;

    Cfg_Db *mCfgDb;
    DBH *DB;

    QSqlTableModel        *modelCustomer;
    QDataWidgetMapper     *mapper;
    QSortFilterProxyModel *proxyModelCustomer;
};

#endif // F_LISTCUSTOMERS_H
