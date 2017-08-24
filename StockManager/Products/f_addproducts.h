#ifndef F_ADDPRODUCTS_H
#define F_ADDPRODUCTS_H

#include <QFrame>
#include "../classes.h"
#include <QSpinBox>
#include <camera.h>

Q_DECLARE_LOGGING_CATEGORY(LC_ADDpro)
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

    void updateBarcodeSymCombo();
    void updateBrandCombo();
    void updateCategoryCombo();
    void updateSubCategoryCombo();
    void updateUnitCombo();

    void createSupplierWidgetHundler();
private:
    Ui::F_AddProducts *ui;
    Toast *mToast;

    Cfg_Db *mCfgDb;
    DBH *DB;

    Camera *mCamera;

};

#endif // F_ADDPRODUCTS_H
