#include "f_warhouses.h"
#include "ui_f_warhouses.h"

F_Warhouses::F_Warhouses(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_Warhouses)
{
    ui->setupUi(this);

    QGraphicsDropShadowEffect *sh = new QGraphicsDropShadowEffect();
    sh->setBlurRadius(8);
    sh->setOffset(2);
    sh->setColor(QColor(63, 63, 63, 180));
    this->setGraphicsEffect(sh);

    ui->F_AddNew->setVisible(false);
    ui->Sb_ID->setVisible(false);

    mCfgDb = new Cfg_Db();

    DB     = new DBH("_warehouses_");

    mapper         = new QDataWidgetMapper();
    modelWarehouse = new QSqlTableModel(this,DB->getCnx());
    modelWarehouse->setTable("warehouses");
    modelWarehouse->select();

    modelWarehouse->setHeaderData(0, Qt::Horizontal, tr("N#"));
    modelWarehouse->setHeaderData(1, Qt::Horizontal, tr("Warehouse Name"));
    modelWarehouse->setHeaderData(2, Qt::Horizontal, tr("Status"));
    modelWarehouse->setHeaderData(3, Qt::Horizontal, tr("Description"));

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->setSortingEnabled(true);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    proxyModelWarehouse = new QSortFilterProxyModel(this);
    proxyModelWarehouse->setSourceModel(modelWarehouse);

    proxyModelWarehouse->setFilterRegExp(QRegExp("", Qt::CaseInsensitive,QRegExp::FixedString));
    proxyModelWarehouse->setFilterKeyColumn(1);


    ui->tableView->setModel(proxyModelWarehouse);

    ui->tableView->horizontalHeader()->stretchLastSection();
    ui->tableView->verticalHeader()->stretchLastSection();
    ui->tableView->resizeColumnsToContents();

    ui->tableView->setColumnHidden(0,true);
    ui->tableView->show();
    ui->tableView->setWordWrap(true);

    mapper->setSubmitPolicy(mapper->ManualSubmit);
    createMapper();

    connect(ui->tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            mapper, SLOT(setCurrentModelIndex(QModelIndex)));

    connect(ui->Bt_AddNew,SIGNAL(clicked(bool)),ui->F_AddNew,SLOT(show()));
    connect(ui->Bt_cancel,SIGNAL(clicked(bool)),ui->F_AddNew,SLOT(hide()));

    connect(ui->Bt_save,SIGNAL(clicked(bool)),this,SLOT(addWarehouse()));
}

F_Warhouses::~F_Warhouses()
{
    #ifdef _WIN32
        DB->mRemoveDatabase("_warehouses_");
    #endif
    delete ui;
}

void F_Warhouses::addWarehouse()
{
    if(ui->Le_WarehouseName->text().isEmpty() )
    {
        //mToast  = new Toast();
        //mToast ->setMessage(tr("set a value for Warehouse name field"));
    }else
    {
        DB->addWarehouse(ui->Le_WarehouseName->text(),ui->Cb_Status->currentText(),ui->Le_Description->text());

        modelWarehouse->select();

        ui->Le_WarehouseName->clear();
        ui->Le_Description->clear();
        ui->Cb_Status->setCurrentIndex(0);
        ui->F_AddNew->setVisible(false);
    }
}

void F_Warhouses::updateStatusWarehouse()
{
    if(ui->Sb_ID->value() >= 0)
    {
        // DB->deleteWarehouse(ui->Sb_ID->value()); // Delete ?? (o_0)
        modelWarehouse->select();
        ui->Sb_ID->setValue(-1);
    }else
    {
        //mToast  = new Toast();
        //mToast ->setMessage(tr("Select a Warehouse"));
    }
}

void F_Warhouses::createMapper()
{
    mapper->setModel(proxyModelWarehouse);
    mapper->addMapping(ui->Sb_ID,modelWarehouse->fieldIndex("id"));
}

void F_Warhouses::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Delete)
    {
        // deleteWarehouse();
    }
}
