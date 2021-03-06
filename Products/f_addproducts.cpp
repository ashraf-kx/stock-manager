#include "f_addproducts.h"
#include "ui_f_addproducts.h"

#include "../People/f_addsupplier.h"

Q_LOGGING_CATEGORY(LC_ADDpro,"products.addproduct")

F_AddProducts::F_AddProducts(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_AddProducts)
{
    ui->setupUi(this);

    qCDebug(LC_ADDpro)<<"Add product fram isWindows ? "<<this->isWindow();
    qCDebug(LC_ADDpro)<<"Get Modilarity : "<<this->windowModality();

    QGraphicsDropShadowEffect *sh = new QGraphicsDropShadowEffect();
    sh->setBlurRadius(8);
    sh->setOffset(2);
    sh->setColor(QColor(63, 63, 63, 180));
    this->setGraphicsEffect(sh);

    mCfgDb = new Cfg_Db();

    DB = new DBH("_addProducts_");

    // updateBarcodeSymCombo();
    updateBrandCombo();
    updateCategoryCombo();
    updateSubCategoryCombo();
    updateUnitCombo();

    createWHList();

    connect(ui->Cb_Category,SIGNAL(currentTextChanged(QString)),this,SLOT(updateSubCategoryCombo()));
    connect(ui->Bt_AddSupplier,SIGNAL(clicked(bool)),this,SLOT(createSupplierWidgetHundler()));
}

F_AddProducts::~F_AddProducts()
{
    DB->mRemoveDatabase("_addProducts_");
    delete ui;
}

void F_AddProducts::updateBrandCombo()
{
    ui->Cb_Brand->clear();
    ui->Cb_Brand->addItems(DB->getAllBrands());
}

void F_AddProducts::updateCategoryCombo()
{
    ui->Cb_Category->clear();
    ui->Cb_Category->addItems(DB->getAllCategories());
}

void F_AddProducts::updateSubCategoryCombo()
{
    ui->Cb_SubCategory->clear();
    int category_id = DB->getCategoryID(ui->Cb_Category->currentText());
    ui->Cb_SubCategory->addItems(DB->getAllSubCategories(category_id));
}

void F_AddProducts::updateUnitCombo()
{
    ui->Cb_ProductUnit->clear();
    ui->Cb_ProductUnit->addItems(DB->getAllUnits());
}

void F_AddProducts::keyPressEvent(QKeyEvent *e)
{

}

void F_AddProducts::addProduct()
{

}

void F_AddProducts::updateBarcodeSymCombo()
{
    // QWidgetList
}

QWidget *F_AddProducts::createWarehouseInputsWidget(const QString& nameWH)
{
    QFrame *frame            = new QFrame();

    QGraphicsDropShadowEffect *sh = new QGraphicsDropShadowEffect();
    sh->setBlurRadius(6);
    sh->setOffset(2);
    sh->setColor(QColor(63, 63, 63, 180));
    frame->setGraphicsEffect(sh);

    frame->setObjectName(nameWH);
    frame->setMinimumSize(QSize(150,100));
    frame->setMaximumSize(QSize(200,200));
    QVBoxLayout *layout      = new QVBoxLayout(frame);

    QLabel *L_nameWarehouse  = new QLabel(nameWH);

    QHBoxLayout *subLayout   = new QHBoxLayout();
    QLabel *L_quantity       = new QLabel("");
        L_quantity->setText(tr("Quantity"));

    QSpinBox *Sb_quantity    = new QSpinBox();
        Sb_quantity->setMaximum(999999);
        Sb_quantity->setMinimum(0);
        Sb_quantity->setValue(0);

    subLayout->addWidget(L_quantity);
    subLayout->addWidget(Sb_quantity);

    QLineEdit *Le_racks      = new QLineEdit();
    Le_racks->setPlaceholderText(tr("Racks"));

    layout->addWidget(L_nameWarehouse);
    layout->addLayout(subLayout);
    layout->addWidget(Le_racks);

    return frame;
}

void F_AddProducts::createWHList()
{
    QStringList list = DB->getAllWarehouses("Active");

    for(int i=0; i < list.size(); i++)
        ui->Gb_Warehouses->layout()->addWidget(createWarehouseInputsWidget(list.at(i)));
}

void F_AddProducts::createSupplierWidgetHundler()
{
    QString ObjName = "add Supplier";

    qCDebug(LC_ADDpro)<<"Add product fram isWindows ? "<<this->isWindow();
    qCDebug(LC_ADDpro)<<"Get Modilarity : "<<this->windowModality();

    QFrame *frame            = new QFrame(this);

    frame->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::Popup);

    frame->setWindowModality(Qt::WindowModal);
    frame->setStyleSheet(this->styleSheet());

    frame->setObjectName(ObjName);
    frame->setMinimumSize(QSize(600,600));
    frame->setVisible(true);

    QVBoxLayout *layout        = new QVBoxLayout(frame);
    QPushButton *Bt_cancel     = new QPushButton(tr("cancel"));
    F_AddSupplier *addSupplier = new F_AddSupplier();

    layout->addWidget(Bt_cancel);
    layout->addWidget(addSupplier);

    // frame->setStyleSheet("background-color:#448aff;");

    qCDebug(LC_ADDpro)<<"Add suplier fram isWindows ? "<<frame->isWindow();
    qCDebug(LC_ADDpro)<<"Get Modilarity : "<<frame->windowModality();

    connect(Bt_cancel,SIGNAL(clicked(bool)),frame,SLOT(close()));
}
