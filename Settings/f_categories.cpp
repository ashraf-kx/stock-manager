#include "f_categories.h"
#include "ui_f_categories.h"

F_Categories::F_Categories(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_Categories)
{
    ui->setupUi(this);

    QGraphicsDropShadowEffect *sh = new QGraphicsDropShadowEffect();
    sh->setBlurRadius(8);
    sh->setOffset(2);
    sh->setColor(QColor(63, 63, 63, 180));
    this->setGraphicsEffect(sh);

    ui->F_AddNew->setVisible(false);
    ui->Sb_ID->setVisible(false);
    ui->F_AddNewSub->setVisible(false);
    ui->Sb_IDSub->setVisible(false);

    mCfgDb = new Cfg_Db();

    this->DBH = QSqlDatabase::addDatabase(mCfgDb->getDriverName(),"CnxCategory");
    this->DBH.setHostName(mCfgDb->getHostname());
    this->DBH.setDatabaseName(mCfgDb->getSchemaName());
    this->DBH.setUserName(mCfgDb->getUsername());
    this->DBH.setPassword(mCfgDb->getPassword());
    this->DBH.open();

    //###########  Categories Section ######################

    mapper        = new QDataWidgetMapper();
    modelCategory = new QSqlTableModel(this,this->DBH);
    modelCategory->setTable("categories");
    modelCategory->select();

    modelCategory->setHeaderData(0, Qt::Horizontal, tr("N#"));
    modelCategory->setHeaderData(1, Qt::Horizontal, tr("Category Name"));
    modelCategory->setHeaderData(2, Qt::Horizontal, tr("Code"));
    modelCategory->setHeaderData(3, Qt::Horizontal, tr("Image"));

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->setSortingEnabled(true);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    proxyModelCategory = new QSortFilterProxyModel(this);
    proxyModelCategory->setSourceModel(modelCategory);

    proxyModelCategory->setFilterRegExp(QRegExp("", Qt::CaseInsensitive,QRegExp::FixedString));
    proxyModelCategory->setFilterKeyColumn(1);

    ui->tableView->setModel(proxyModelCategory);

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

    connect(ui->Bt_save,SIGNAL(clicked(bool)),this,SLOT(addCategory()));

    //######################### Sub Categories Section #########################

    mapperSub        = new QDataWidgetMapper();
    modelSubCategory = new QSqlTableModel(this,this->DBH);
    modelSubCategory->setTable("subcategories");
    modelSubCategory->select();

    modelSubCategory->setHeaderData(0, Qt::Horizontal, tr("N#"));
    modelSubCategory->setHeaderData(1, Qt::Horizontal, tr("Sub Category Name"));
    modelSubCategory->setHeaderData(2, Qt::Horizontal, tr("Code"));
    modelSubCategory->setHeaderData(3, Qt::Horizontal, tr("Image"));
    modelSubCategory->setHeaderData(4, Qt::Horizontal, tr("ID Parent"));

    ui->tableViewSub->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewSub->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableViewSub->setSortingEnabled(true);
    ui->tableViewSub->setSelectionMode(QAbstractItemView::SingleSelection);

    proxyModelSubCategory = new QSortFilterProxyModel(this);
    proxyModelSubCategory->setSourceModel(modelSubCategory);

    proxyModelSubCategory->setFilterRegExp(QRegExp("", Qt::CaseInsensitive,QRegExp::FixedString));
    proxyModelSubCategory->setFilterKeyColumn(1);

    ui->tableViewSub->setModel(proxyModelSubCategory);

    ui->tableViewSub->horizontalHeader()->stretchLastSection();
    ui->tableViewSub->verticalHeader()->stretchLastSection();
    ui->tableViewSub->resizeColumnsToContents();

    ui->tableViewSub->setColumnHidden(0,true);
    ui->tableViewSub->show();
    ui->tableViewSub->setWordWrap(true);

    mapperSub->setSubmitPolicy(mapperSub->ManualSubmit);
    createMapperSub();

    updateCategoriesCombo();

    connect(ui->tableViewSub->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            mapperSub, SLOT(setCurrentModelIndex(QModelIndex)));

    connect(ui->Bt_AddNewSub,SIGNAL(clicked(bool)),ui->F_AddNewSub,SLOT(show()));
    connect(ui->Bt_cancelSub,SIGNAL(clicked(bool)),ui->F_AddNewSub,SLOT(hide()));

    connect(ui->Bt_saveSub,SIGNAL(clicked(bool)),this,SLOT(addSubCategory()));
}

F_Categories::~F_Categories()
{
    delete ui;
}

void F_Categories::createMapper()
{
    mapper->setModel(proxyModelCategory);
    mapper->addMapping(ui->Sb_ID,modelCategory->fieldIndex("id"));
}

void F_Categories::createMapperSub()
{
    mapperSub->setModel(proxyModelSubCategory);
    mapperSub->addMapping(ui->Sb_IDSub,modelSubCategory->fieldIndex("id"));
}

void F_Categories::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Delete) {
        // deleteUnit();
    }
}

void F_Categories::addCategory()
{
    if(ui->Le_CategoryName->text().isEmpty() || ui->Le_Code->text().isEmpty())
    {
        //mToast  = new Toast();
        //mToast ->setMessage(tr("Fill Both Values For Category Name & Code"));
    }else
    {
        if(!this->DBH.isOpen())
            this->DBH.open();
        this->DBH.transaction();

        //! [1] Execute Statements On `categories` Table.
        QSqlQuery *query = new QSqlQuery(this->DBH);

        query->prepare("SELECT id FROM categories WHERE name=:name");
        query->bindValue(":name",ui->Le_CategoryName->text());
        query->exec();

        if (query->next()) {
            //mToast  = new Toast();
            //mToast ->setMessage(tr("Already Exists"));
        }else
        {
            query->prepare("INSERT INTO categories (id,name,code)"
                           " VALUES (NULL,:name,:code)");

            query->bindValue(":name",ui->Le_CategoryName->text());
            query->bindValue(":code",ui->Le_Code->text());
            query->exec();
        }

        this->DBH.commit();
        modelCategory->select();

        updateCategoriesCombo();

        ui->Le_CategoryName->clear();
        ui->Le_Code->clear();
        ui->F_AddNew->setVisible(false);
    }
}

void F_Categories::addSubCategory()
{
    if(ui->Le_SubCategoryName->text().isEmpty() || ui->Le_CodeSub->text().isEmpty())
    {
        //mToast  = new Toast();
        //mToast ->setMessage(tr("Fill Both Values For Sub  Category Name & Code"));
    }else
    {
        if(!this->DBH.isOpen())
            this->DBH.open();
        this->DBH.transaction();

        //! [1] Execute Statements On `subcategories` Table.
        QSqlQuery *query = new QSqlQuery(this->DBH);

        query->prepare("SELECT id FROM categories WHERE name=:name");
        query->bindValue(":name",ui->Cb_ParentCat->currentText());
        query->exec();
        int tmpID = -1;
        if (query->next()){
            tmpID = query->value(0).toInt();
        }

        query->prepare("SELECT id FROM subcategories WHERE name=:name AND code=:code AND category_id=:category_id");
        query->bindValue(":name",ui->Le_SubCategoryName->text());
        query->bindValue(":code",ui->Le_CodeSub->text());
        query->bindValue(":category_id",tmpID);
        query->exec();

        if (query->next()) {
            //mToast  = new Toast();
            //mToast ->setMessage(tr("Already Exists"));
        }else
        {
            query->prepare("INSERT INTO subcategories (id,name,code,category_id)"
                           " VALUES (NULL,:name,:code,:category_id)");

            query->bindValue(":name",ui->Le_SubCategoryName->text());
            query->bindValue(":code",ui->Le_CodeSub->text());
            query->bindValue(":category_id",tmpID);

            query->exec();
        }

        this->DBH.commit();
        modelSubCategory->select();

        ui->Le_SubCategoryName->clear();
        ui->Le_CodeSub->clear();
        ui->Cb_ParentCat->setCurrentIndex(0);

        ui->F_AddNewSub->setVisible(false);
    }
}

void F_Categories::deleteCategory()
{
    if(!this->DBH.isOpen())
        this->DBH.open();

    if(ui->Sb_ID->value() >= 0)
    {
        this->DBH.transaction();

        //! [1] Execute Statements On `subcategories` Table.
        QSqlQuery *query = new QSqlQuery(this->DBH);

        query->prepare("DELETE FROM subcategories WHERE category_id=:id");
        query->bindValue(":id",ui->Sb_ID->value());
        query->exec();

        query->prepare("DELETE FROM categories WHERE id=:id");
        query->bindValue(":id",ui->Sb_ID->value());
        query->exec();

        this->DBH.commit();
        modelCategory->select();
        updateCategoriesCombo();
        ui->Sb_ID->setValue(-1);

    }else
    {
        //mToast  = new Toast();
        //mToast ->setMessage(tr("Select a row Category"));
    }
}

void F_Categories::deleteSubCategory()
{
    if(!this->DBH.isOpen())
        this->DBH.open();

    if(ui->Sb_ID->value() >= 0)
    {
        this->DBH.transaction();

        //! [1] Execute Statements On `units` Table.
        QSqlQuery *query = new QSqlQuery(this->DBH);

        query->prepare("DELETE FROM subcategories WHERE id=:id");
        query->bindValue(":id",ui->Sb_IDSub->value());
        query->exec();

        this->DBH.commit();
        modelSubCategory->select();
        ui->Sb_IDSub->setValue(-1);
    }else
    {
        //mToast  = new Toast();
        //mToast ->setMessage(tr("Select a row unit"));
    }
}

void F_Categories::updateCategoriesCombo()
{
    if(!this->DBH.isOpen())
        this->DBH.open();
    this->DBH.transaction();

    //! [1] Execute Statements On `categories` Table.
    QSqlQuery *query = new QSqlQuery(this->DBH);

    query->prepare("SELECT name FROM categories");
    query->exec();

    ui->Cb_ParentCat->clear();

    while(query->next()){
        if(!query->value(0).toString().isEmpty())
            ui->Cb_ParentCat->addItem(query->value(0).toString());
    }

    this->DBH.commit();
}
