#include "f_listcustomers.h"
#include "ui_f_listcustomers.h"

Q_LOGGING_CATEGORY(PLC,"people.listcustomers")

F_ListCustomers::F_ListCustomers(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_ListCustomers)
{
    ui->setupUi(this);
    QGraphicsDropShadowEffect *sh = new QGraphicsDropShadowEffect();
    sh->setBlurRadius(8);
    sh->setOffset(2);
    sh->setColor(QColor(63, 63, 63, 180));
    this->setGraphicsEffect(sh);

    mCfgDb = new Cfg_Db();
    DB     = new DBH("_listCustomers_");

    mapper    = new QDataWidgetMapper();
    modelCustomer = new QSqlTableModel(this,DB->getCnx());
    modelCustomer->setTable("customers");
    modelCustomer->select();

    ui->tableView->setVisible(false);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->setSortingEnabled(true);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    proxyModelCustomer = new QSortFilterProxyModel(this);
    proxyModelCustomer->setSourceModel(modelCustomer);

    proxyModelCustomer->setFilterRegExp(QRegExp("", Qt::CaseInsensitive,QRegExp::FixedString));
    proxyModelCustomer->setFilterKeyColumn(1);

    ui->tableView->setModel(proxyModelCustomer);

    // 6.7.8.1???
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

    modelCustomer->setHeaderData(0, Qt::Horizontal, tr("N#"));
    modelCustomer->setHeaderData(1, Qt::Horizontal, tr("First Name"));
    modelCustomer->setHeaderData(2, Qt::Horizontal, tr("Last Name"));
    modelCustomer->setHeaderData(3, Qt::Horizontal, tr("User Name"));
    modelCustomer->setHeaderData(4, Qt::Horizontal, tr("Group"));
    modelCustomer->setHeaderData(5, Qt::Horizontal, tr("Email"));
    modelCustomer->setHeaderData(6, Qt::Horizontal, tr("Company"));
    modelCustomer->setHeaderData(7, Qt::Horizontal, tr("Created on"));
    modelCustomer->setHeaderData(8, Qt::Horizontal, tr("Status"));

    ui->tableView->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->stretchLastSection();
    ui->tableView->verticalHeader()->stretchLastSection();
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

F_ListCustomers::~F_ListCustomers()
{
    #ifdef _WIN32
        DB->mRemoveDatabase("_listCustomers_");
    #endif
    delete ui;
}

void F_ListCustomers::createMapper()
{
    mapper->setModel(proxyModelCustomer);

    mapper->addMapping(ui->Sb_IDCustomer,modelCustomer->fieldIndex("id"));
    mapper->addMapping(ui->Le_name,modelCustomer->fieldIndex("fullname"));
    mapper->addMapping(ui->Le_phone,modelCustomer->fieldIndex("phone"));
    mapper->addMapping(ui->Le_email,modelCustomer->fieldIndex("email"));
    mapper->addMapping(ui->Le_vatNumber,modelCustomer->fieldIndex("vat_number"));
    mapper->addMapping(ui->Le_company,modelCustomer->fieldIndex("company_id"));
    mapper->addMapping(ui->Le_customerGroup,modelCustomer->fieldIndex("customer_group_id"));
    mapper->addMapping(ui->Le_priceGroup,modelCustomer->fieldIndex("price_group_id"));
    mapper->addMapping(ui->Le_deposite,modelCustomer->fieldIndex("address_id"));
}

void F_ListCustomers::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Delete)
    {
        // deleteWarehouse();
    }
}
