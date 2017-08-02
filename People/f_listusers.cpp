#include "f_listusers.h"
#include "ui_f_listusers.h"

Q_LOGGING_CATEGORY(PLU,"people.listusers")

F_ListUsers::F_ListUsers(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_ListUsers)
{

    ui->setupUi(this);
    QGraphicsDropShadowEffect *sh = new QGraphicsDropShadowEffect();
    sh->setBlurRadius(8);
    sh->setOffset(2);
    sh->setColor(QColor(63, 63, 63, 180));
    this->setGraphicsEffect(sh);

    mCfgDb = new Cfg_Db();
    DB     = new DBH("_listUsers_");

    mapper    = new QDataWidgetMapper();
    modelUser = new QSqlTableModel(this,DB->getCnx());
    modelUser->setTable("users");
    modelUser->select();



    ui->tableView->setVisible(false);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->setSortingEnabled(true);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    proxyModelUser = new QSortFilterProxyModel(this);
    proxyModelUser->setSourceModel(modelUser);

    proxyModelUser->setFilterRegExp(QRegExp("", Qt::CaseInsensitive,QRegExp::FixedString));
    proxyModelUser->setFilterKeyColumn(1);

    ui->tableView->setModel(proxyModelUser);

    // 6.7.8.10.11.12.13.15-22.24.26
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->setColumnHidden(4,true);
    ui->tableView->setColumnHidden(6,true);
    ui->tableView->setColumnHidden(7,true);
    ui->tableView->setColumnHidden(8,true);
    ui->tableView->setColumnHidden(10,true);
    ui->tableView->setColumnHidden(11,true);
    ui->tableView->setColumnHidden(12,true);
    ui->tableView->setColumnHidden(13,true);
    ui->tableView->setColumnHidden(15,true);
    ui->tableView->setColumnHidden(16,true);
    ui->tableView->setColumnHidden(17,true);
    ui->tableView->setColumnHidden(18,true);
    ui->tableView->setColumnHidden(19,true);
    ui->tableView->setColumnHidden(20,true);
    ui->tableView->setColumnHidden(21,true);
    ui->tableView->setColumnHidden(22,true);
    ui->tableView->setColumnHidden(24,true);
    ui->tableView->setColumnHidden(26,true);

    modelUser->setHeaderData(0, Qt::Horizontal, tr("N#"));
    modelUser->setHeaderData(1, Qt::Horizontal, tr("First Name"));
    modelUser->setHeaderData(2, Qt::Horizontal, tr("Last Name"));
    modelUser->setHeaderData(3, Qt::Horizontal, tr("User Name"));
    modelUser->setHeaderData(4, Qt::Horizontal, tr("Group"));
    modelUser->setHeaderData(5, Qt::Horizontal, tr("Email"));
    modelUser->setHeaderData(6, Qt::Horizontal, tr("Company"));
    modelUser->setHeaderData(7, Qt::Horizontal, tr("Created on"));
    modelUser->setHeaderData(8, Qt::Horizontal, tr("Status"));

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

F_ListUsers::~F_ListUsers()
{
    DB->mRemoveDatabase("_listUsers_");
    delete ui;
}

void F_ListUsers::createMapper()
{
    mapper->setModel(proxyModelUser);

    mapper->addMapping(ui->Sb_IDUser,modelUser->fieldIndex("id"));
    mapper->addMapping(ui->Le_firstName,modelUser->fieldIndex("first_name"));
    mapper->addMapping(ui->Le_lastName,modelUser->fieldIndex("last_name"));
    mapper->addMapping(ui->Le_email,modelUser->fieldIndex("email"));
    mapper->addMapping(ui->Le_group,modelUser->fieldIndex("group_id"));
    mapper->addMapping(ui->Le_company,modelUser->fieldIndex("company_id"));
    mapper->addMapping(ui->Le_status,modelUser->fieldIndex("status"));
}

void F_ListUsers::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Delete)
    {
        // deleteWarehouse();
    }
}
