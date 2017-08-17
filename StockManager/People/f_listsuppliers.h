#ifndef F_LISTSUPPLIERS_H
#define F_LISTSUPPLIERS_H

#include <QFrame>
#include "../classes.h"

Q_DECLARE_LOGGING_CATEGORY(PLS)

namespace Ui {
class F_ListSuppliers;
}

class F_ListSuppliers : public QFrame
{
    Q_OBJECT

public:
    explicit F_ListSuppliers(QWidget *parent = 0);
    ~F_ListSuppliers();

    void createMapper();
    void keyPressEvent(QKeyEvent *e) override;
private:
    Ui::F_ListSuppliers *ui;
    Toast *mToast;

    Cfg_Db *mCfgDb;
    DBH *DB;

    QSqlTableModel        *modelSupplier;
    QDataWidgetMapper     *mapper;
    QSortFilterProxyModel *proxyModelSupplier;

};

#endif // F_LISTSUPPLIERS_H
