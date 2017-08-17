#ifndef F_WARHOUSES_H
#define F_WARHOUSES_H

#include <QFrame>
#include "../classes.h"

namespace Ui {
class F_Warhouses;
}

class F_Warhouses : public QFrame
{
    Q_OBJECT

public:
    explicit F_Warhouses(QWidget *parent = 0);
    ~F_Warhouses();

    void createMapper();
    void keyPressEvent(QKeyEvent *e) override;

public slots:
    void addWarehouse();
    void updateStatusWarehouse();

private:
    Ui::F_Warhouses *ui;
    Toast *mToast;

    Cfg_Db *mCfgDb;
    DBH *DB;

    QSqlTableModel        *modelWarehouse;
    QDataWidgetMapper     *mapper;
    QSortFilterProxyModel *proxyModelWarehouse;
};

#endif // F_WARHOUSES_H
