#ifndef F_ADDSUPPLIER_H
#define F_ADDSUPPLIER_H

#include <QFrame>
#include "../classes.h"
#include "../toast.h"
#include <QGraphicsDropShadowEffect>
#include <QEvent>
#include <QKeyEvent>

//! [DB QtSql ]
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSortFilterProxyModel>
#include <QtWidgets/QDataWidgetMapper>

namespace Ui {
class F_AddSupplier;
}

class F_AddSupplier : public QFrame
{
    Q_OBJECT

public:
    explicit F_AddSupplier(QWidget *parent = 0);
    ~F_AddSupplier();

    void createMapper();
    void keyPressEvent(QKeyEvent *e) override;

public slots:
    void addSupplier();
    void updateSupplier();
    void deleteSupplier();

private:
    Ui::F_AddSupplier *ui;

    Toast *mToast;

    Cfg_Db *mCfgDb;
    QSqlDatabase DBH;

    QSqlTableModel        *modelSupplier;
    QDataWidgetMapper     *mapper;
    QSortFilterProxyModel *proxyModelSupplier;
};

#endif // F_ADDSUPPLIER_H
