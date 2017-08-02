#include "f_listsuppliers.h"
#include "ui_f_listsuppliers.h"

Q_LOGGING_CATEGORY(PLS,"people.listsuppliers")

F_ListSuppliers::F_ListSuppliers(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_ListSuppliers)
{
    ui->setupUi(this);
    QGraphicsDropShadowEffect *sh = new QGraphicsDropShadowEffect();
    sh->setBlurRadius(8);
    sh->setOffset(2);
    sh->setColor(QColor(63, 63, 63, 180));
    this->setGraphicsEffect(sh);

    mCfgDb = new Cfg_Db();
    DB     = new DBH("_listSuppliers_");

    mapper    = new QDataWidgetMapper();
    modelSupplier = new QSqlTableModel(this,DB->getCnx());
    modelSupplier->setTable("suppliers");
    modelSupplier->select();

    modelSupplier->setHeaderData(0, Qt::Horizontal, tr("N#"));
    modelSupplier->setHeaderData(1, Qt::Horizontal, tr("Full Name"));
    modelSupplier->setHeaderData(2, Qt::Horizontal, tr("Email"));
    modelSupplier->setHeaderData(3, Qt::Horizontal, tr("Phone"));
    modelSupplier->setHeaderData(4, Qt::Horizontal, tr("VAT Number"));
    modelSupplier->setHeaderData(5, Qt::Horizontal, tr("Company"));
    modelSupplier->setHeaderData(6, Qt::Horizontal, tr("Address"));
    modelSupplier->setHeaderData(7, Qt::Horizontal, tr("Created on"));


    ui->tableView->setVisible(false);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->setSortingEnabled(true);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    proxyModelSupplier = new QSortFilterProxyModel(this);
    proxyModelSupplier->setSourceModel(modelSupplier);

    proxyModelSupplier->setFilterRegExp(QRegExp("", Qt::CaseInsensitive,QRegExp::FixedString));
    proxyModelSupplier->setFilterKeyColumn(1);

    ui->tableView->setModel(proxyModelSupplier);

    // 6.7.8.10.11.12.13.15-22.24.26
//    ui->tableView->setColumnHidden(0,true);
//    ui->tableView->setColumnHidden(4,true);
//    ui->tableView->setColumnHidden(6,true);
//    ui->tableView->setColumnHidden(7,true);
//    ui->tableView->setColumnHidden(8,true);
//    ui->tableView->setColumnHidden(10,true);
//    ui->tableView->setColumnHidden(11,true);
//    ui->tableView->setColumnHidden(12,true);
//    ui->tableView->setColumnHidden(13,true);
//    ui->tableView->setColumnHidden(15,true);
//    ui->tableView->setColumnHidden(16,true);
//    ui->tableView->setColumnHidden(17,true);
//    ui->tableView->setColumnHidden(18,true);
//    ui->tableView->setColumnHidden(19,true);
//    ui->tableView->setColumnHidden(20,true);
//    ui->tableView->setColumnHidden(21,true);
//    ui->tableView->setColumnHidden(22,true);
//    ui->tableView->setColumnHidden(24,true);
//    ui->tableView->setColumnHidden(26,true);

    ui->tableView->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->stretchLastSection();
    ui->tableView->verticalHeader()->stretchLastSection(); //setVisible(false);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
    ui->tableView->horizontalHeader()->setResizeContentsPrecision(10);
    ui->tableView->setWordWrap(true);
    ui->tableView->setVisible(true);


    mapper->setSubmitPolicy(mapper->ManualSubmit);
    createMapper();

    connect(ui->tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            mapper, SLOT(setCurrentModelIndex(QModelIndex)));

//    connect(ui->Bt_AddNew,SIGNAL(clicked(bool)),ui->F_AddNew,SLOT(show()));
//    connect(ui->Bt_cancel,SIGNAL(clicked(bool)),ui->F_AddNew,SLOT(hide()));

    // connect(ui->Bt_save,SIGNAL(clicked(bool)),this,SLOT());
}

F_ListSuppliers::~F_ListSuppliers()
{
    DB->mRemoveDatabase("_listsuppliers_");
    delete ui;
}

void F_ListSuppliers::createMapper()
{
    mapper->setModel(proxyModelSupplier);

    mapper->addMapping(ui->Sb_IDUser,modelSupplier->fieldIndex("id"));
    mapper->addMapping(ui->Le_company,modelSupplier->fieldIndex("company_id"));
    mapper->addMapping(ui->Le_name,modelSupplier->fieldIndex("fullname"));
    mapper->addMapping(ui->Le_email,modelSupplier->fieldIndex("email"));
    mapper->addMapping(ui->Le_phone,modelSupplier->fieldIndex("phone"));
    mapper->addMapping(ui->Le_vatNumber,modelSupplier->fieldIndex("vat_number"));
    mapper->addMapping(ui->Le_city,modelSupplier->fieldIndex("address_id"));
}

void F_ListSuppliers::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Delete)
    {
        // deleteWarehouse();
    }
}
