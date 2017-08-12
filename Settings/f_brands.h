#ifndef F_BRANDS_H
#define F_BRANDS_H

#include <QFrame>
#include "../classes.h"

namespace Ui {
class F_Brands;
}

class F_Brands : public QFrame
{
    Q_OBJECT

public:
    explicit F_Brands(QWidget *parent = 0);
    ~F_Brands();

    void createMapper();
    void keyPressEvent(QKeyEvent *e) override;

public slots:
    void addBrand();
    void deleteBrand();

private:
    Ui::F_Brands *ui;
    Toast *mToast;

    Cfg_Db *mCfgDb;
    DBH *DB;

    QSqlTableModel        *modelBrand;
    QDataWidgetMapper     *mapper;
    QSortFilterProxyModel *proxyModelBrand;
};

#endif // F_BRANDS_H
