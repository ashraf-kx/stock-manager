#ifndef F_UNITS_H
#define F_UNITS_H

#include <QFrame>
#include "../classes.h"
#include "dialog.h"

using namespace std;

namespace Ui {
class F_Units;
}

class F_Units : public QFrame
{
    Q_OBJECT

public:
    explicit F_Units(QWidget *parent = 0);
    ~F_Units();

    void createMapper();
    void keyPressEvent(QKeyEvent *e) override;

public slots:
    void addUnit();
    void deleteUnit();
private:
    Ui::F_Units *ui;
    Toast  *mToast;

    Cfg_Db *mCfgDb;
    DBH *DB;

    QSqlTableModel        *modelUnit;
    QDataWidgetMapper     *mapper;
    QSortFilterProxyModel *proxyModelUnit;
};

#endif // F_UNITS_H
