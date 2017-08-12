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
    DB = new DBH("_categories_");

    //###########  Categories Section ######################
    mapper        = new QDataWidgetMapper();
    modelCategory = new QSqlTableModel(this,DB->getCnx());
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
    modelSubCategory = new QSqlTableModel(this,DB->getCnx());
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
    #ifdef _WIN32
        DB->mRemoveDatabase("_categories_");
    #endif
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
        DB->addCategory(ui->Le_CategoryName->text(),ui->Le_Code->text().toUpper());

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
        int category_id    = DB->getCategoryID(ui->Cb_ParentCat->currentText());
        int subCategory_id = DB->getSubCategoryID(ui->Le_SubCategoryName->text(),ui->Le_CodeSub->text(),category_id);

        if (subCategory_id == -1) {
            // Doesn't exist > add the new record.
            subCategory_id = DB->addSubCategory(ui->Le_SubCategoryName->text(),ui->Le_CodeSub->text().toUpper(),category_id);

        }else
        {
            //mToast  = new Toast();
            //mToast ->setMessage(tr("Already Exists"));
        }

        modelSubCategory->select();

        ui->Le_SubCategoryName->clear();
        ui->Le_CodeSub->clear();
        ui->Cb_ParentCat->setCurrentIndex(0);

        ui->F_AddNewSub->setVisible(false);
    }
}

void F_Categories::deleteCategory()
{
    if(ui->Sb_ID->value() >= 0)
    {
        DB->deleteCategory(ui->Sb_ID->value());

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
    if(ui->Sb_ID->value() >= 0)
    {
        DB->deleteSubCategory(ui->Sb_IDSub->value());

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
    ui->Cb_ParentCat->clear();
    ui->Cb_ParentCat->addItems(DB->getAllCategories());
}
