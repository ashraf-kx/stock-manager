#ifndef F_ADDPRODUCTS_H
#define F_ADDPRODUCTS_H

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
#include <QtWidgets/QSpinBox>

namespace Ui {
class F_AddProducts;
}

class F_AddProducts : public QFrame
{
    Q_OBJECT

public:
    explicit F_AddProducts(QWidget *parent = 0);
    ~F_AddProducts();

     void keyPressEvent(QKeyEvent *e) override;

    void createWHList();
    QWidget *createWarehouseInputsWidget(const QString &nameWH);

public slots:
    void addProduct();
    QStringList getAllWarehousesByStatus(const QString& status);
    QStringList getAllWarehouses();


    void updateBarcodeSymCombo();
    void updateBrandCombo();
    void updateCategoryCombo();
    void updateSubCategoryCombo();
    void updateUnitCombo();

private:
    Ui::F_AddProducts *ui;
    Toast *mToast;

    Cfg_Db *mCfgDb;
    QSqlDatabase DBH;

//    QSqlTableModel        *modelProduct;
//    QDataWidgetMapper     *mapper;
//    QSortFilterProxyModel *proxyModelProduct;

};

#endif // F_ADDPRODUCTS_H
