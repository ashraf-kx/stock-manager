#include "f_brands.h"
#include "ui_f_brands.h"


F_Brands::F_Brands(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_Brands)
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

    this->DBH = QSqlDatabase::addDatabase(mCfgDb->getDriverName(),"CnxBrands");
    this->DBH.setHostName(mCfgDb->getHostname());
    this->DBH.setDatabaseName(mCfgDb->getSchemaName());
    this->DBH.setUserName(mCfgDb->getUsername());
    this->DBH.setPassword(mCfgDb->getPassword());
    this->DBH.open();

    mapper    = new QDataWidgetMapper();
    modelBrand = new QSqlTableModel(this,this->DBH);
    modelBrand->setTable("brands");
    modelBrand->select();

    modelBrand->setHeaderData(0, Qt::Horizontal, tr("N#"));
    modelBrand->setHeaderData(1, Qt::Horizontal, tr("Brand Name"));
    modelBrand->setHeaderData(2, Qt::Horizontal, tr("Code"));

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->setSortingEnabled(true);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    proxyModelBrand = new QSortFilterProxyModel(this);
    proxyModelBrand->setSourceModel(modelBrand);

    proxyModelBrand->setFilterRegExp(QRegExp("", Qt::CaseInsensitive,QRegExp::FixedString));
    proxyModelBrand->setFilterKeyColumn(1);


    ui->tableView->setModel(proxyModelBrand);

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

    connect(ui->Bt_save,SIGNAL(clicked(bool)),this,SLOT(addBrand()));
}

F_Brands::~F_Brands()
{
    delete ui;
}

void F_Brands::addBrand()
{
    if(ui->Le_BrandName->text().isEmpty() || ui->Le_Code->text().isEmpty())
    {
        mToast = new Toast();
        mToast->setMessage(tr("Fill Both Values For Brand Name & Code"));
    }else
    {
        if(!this->DBH.isOpen())
            this->DBH.open();
        this->DBH.transaction();

        //! [1] Execute Statements On `brands` Table.
        QSqlQuery *query = new QSqlQuery(this->DBH);

        query->prepare("SELECT id FROM brands WHERE name=:name AND code=:code");
        query->bindValue(":name",ui->Le_BrandName->text());
        query->bindValue(":code",ui->Le_Code->text());
        query->exec();

        if (query->next()) {
            mToast = new Toast();
            mToast->setMessage(tr("Already Exists"));
        }else
        {
            query->prepare("INSERT INTO brands (id,name,code)"
                           " VALUES (NULL,:name,:code)");

            query->bindValue(":name",ui->Le_BrandName->text());
            query->bindValue(":code",ui->Le_Code->text());

            query->exec();
        }

        this->DBH.commit();
        modelBrand->select();

        ui->Le_BrandName->clear();
        ui->Le_Code->clear();
        ui->F_AddNew->setVisible(false);
    }
}

void F_Brands::deleteBrand()
{
    if(!this->DBH.isOpen())
        this->DBH.open();

    if(ui->Sb_ID->value() >= 0)
    {
        this->DBH.transaction();

        //! [1] Execute Statements On `Brands` Table.
        QSqlQuery *query = new QSqlQuery(this->DBH);

        query->prepare("DELETE FROM brands WHERE id=:id");
        query->bindValue(":id",ui->Sb_ID->value());
        query->exec();

        this->DBH.commit();
        modelBrand->select();
        ui->Sb_ID->setValue(-1);
    }else
    {
        mToast = new Toast();
        mToast->setMessage(tr("Select a row Brand"));
    }
}

void F_Brands::createMapper()
{
    mapper->setModel(proxyModelBrand);

    mapper->addMapping(ui->Sb_ID,modelBrand->fieldIndex("id"));
}

void F_Brands::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Delete) {
        deleteBrand();
    }
}
