#include "f_warhouses.h"
#include "ui_f_warhouses.h"

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

    this->DBH = QSqlDatabase::addDatabase(mCfgDb->getDriverName(),"CnxWarehouses");
    this->DBH.setHostName(mCfgDb->getHostname());
    this->DBH.setDatabaseName(mCfgDb->getSchemaName());
    this->DBH.setUserName(mCfgDb->getUsername());
    this->DBH.setPassword(mCfgDb->getPassword());
    this->DBH.open();

    mapper    = new QDataWidgetMapper();
    modelWarehouse = new QSqlTableModel(this,this->DBH);
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
    delete ui;
}

void F_Warhouses::addWarehouse()
{
    if(ui->Le_WarehouseName->text().isEmpty() )
    {
        mToast = new Toast();
        mToast->setMessage(tr("set a value for Warehouse name field"));
    }else
    {
        if(!this->DBH.isOpen())
            this->DBH.open();
        this->DBH.transaction();

        //! [1] Execute Statements On `Warehouses` Table.
        QSqlQuery *query = new QSqlQuery(this->DBH);

        query->prepare("SELECT id FROM warehouses WHERE name=:name");
        query->bindValue(":name",ui->Le_WarehouseName->text());
        query->exec();

        if (query->next()) {
            mToast = new Toast();
            mToast->setMessage(tr("Already Exists"));
        }else
        {
            query->prepare("INSERT INTO warehouses (id,name,status,description)"
                           " VALUES (NULL,:name,:status,:description)");

            query->bindValue(":name",ui->Le_WarehouseName->text());
            query->bindValue(":status",ui->Cb_Status->currentText());
            query->bindValue(":description",ui->Le_Description->text());

            query->exec();
        }

        this->DBH.commit();
        modelWarehouse->select();

        ui->Le_WarehouseName->clear();
        ui->Le_Description->clear();
        ui->Cb_Status->setCurrentIndex(0);
        ui->F_AddNew->setVisible(false);
    }
}

void F_Warhouses::updateStatusWarehouse()
{
    if(!this->DBH.isOpen())
        this->DBH.open();

    if(ui->Sb_ID->value() >= 0)
    {
        this->DBH.transaction();

        //! [1] Execute Statements On `Warehouses` Table.
        QSqlQuery *query = new QSqlQuery(this->DBH);

        query->prepare("DELETE FROM warehouses WHERE id=:id");
        query->bindValue(":id",ui->Sb_ID->value());
        query->exec();

        this->DBH.commit();
        modelWarehouse->select();
        ui->Sb_ID->setValue(-1);
    }else
    {
        mToast = new Toast();
        mToast->setMessage(tr("Select a Warehouse"));
    }
}

void F_Warhouses::createMapper()
{
    mapper->setModel(proxyModelWarehouse);

    mapper->addMapping(ui->Sb_ID,modelWarehouse->fieldIndex("id"));
}

void F_Warhouses::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Delete) {
        // deleteWarehouse();
    }
}
