#include "f_listusers.h"
#include "ui_f_listusers.h"
#include <math.h>

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

    queryModelUser = new QSqlQueryModel();
    queryModelUser->setQuery("SELECT `id`,`first_name`,`last_name`,`username`,`email`,`status`,"
                             "`created_on`,`group_id`,`company_id` FROM `users`",DB->getCnx());
    qDebug()<<queryModelUser->rowCount();

    ui->tableView->setVisible(false);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->setSortingEnabled(true);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    proxyModelUser = new QSortFilterProxyModel(this);
    proxyModelUser->setSourceModel(queryModelUser);

    proxyModelUser->setFilterRegExp(QRegExp("", Qt::CaseInsensitive,QRegExp::FixedString));
    proxyModelUser->setFilterKeyColumn(1);

    ui->tableView->setModel(proxyModelUser);

    // 6.7.8.10.11.12.13.15-22.24.26
    ui->tableView->setColumnHidden(0,true);

//    modelUser->setHeaderData(0, Qt::Horizontal, tr("N#"));
//    modelUser->setHeaderData(1, Qt::Horizontal, tr("First Name"));
//    modelUser->setHeaderData(2, Qt::Horizontal, tr("Last Name"));
//    modelUser->setHeaderData(3, Qt::Horizontal, tr("User Name"));
//    modelUser->setHeaderData(4, Qt::Horizontal, tr("Group"));
//    modelUser->setHeaderData(5, Qt::Horizontal, tr("Email"));
//    modelUser->setHeaderData(6, Qt::Horizontal, tr("Company"));
//    modelUser->setHeaderData(7, Qt::Horizontal, tr("Created on"));
//    modelUser->setHeaderData(8, Qt::Horizontal, tr("Status"));

    ui->tableView->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->stretchLastSection();
    ui->tableView->verticalHeader()->stretchLastSection();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
    //ui->tableView->horizontalHeader()->setResizeContentsPrecision(40);
    ui->tableView->setWordWrap(true);
    ui->tableView->setVisible(true);

    mapper->setSubmitPolicy(mapper->ManualSubmit);
    createMapper();

    initListRowsPerPage();
    ui->Cb_rows->setCurrentIndex(0);

    connect(ui->tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            mapper, SLOT(setCurrentModelIndex(QModelIndex)));

    connect(ui->Cb_rows,SIGNAL(currentTextChanged(QString)),this,SLOT(updateTableViewRows()));
    connect(ui->Cb_pages,SIGNAL(currentTextChanged(QString)),this,SLOT(showPageRows()));


//    connect(ui->Bt_AddNew,SIGNAL(clicked(bool)),ui->F_AddNew,SLOT(show()));
//    connect(ui->Bt_cancel,SIGNAL(clicked(bool)),ui->F_AddNew,SLOT(hide()));

    // connect(ui->Bt_save,SIGNAL(clicked(bool)),this,SLOT());

}

F_ListUsers::~F_ListUsers()
{
    DB->mRemoveDatabase("_listUsers_");
    delete ui;
}

void F_ListUsers::hideAllRows()
{
    for(int i=0; i<queryModelUser->rowCount(); i++)
    {
        ui->tableView->hideRow(i);
    }
}

void F_ListUsers::showAllRows()
{
    for(int i=0; queryModelUser->rowCount();i++)
    {
        ui->tableView->showRow(i);
    }
}

void F_ListUsers::initListRowsPerPage()
{
    ui->Cb_rows->clear();
    int maxRows  = queryModelUser->rowCount();
    ui->Cb_rows->addItem(QString::number(maxRows));

    if(maxRows >= 10 ) ui->Cb_rows->addItem("10");
    if(maxRows >= 15 ) ui->Cb_rows->addItem("15");
    if(maxRows >= 20 ) ui->Cb_rows->addItem("20");
    if(maxRows >= 30 ) ui->Cb_rows->addItem("30");
    if(maxRows >= 50 ) ui->Cb_rows->addItem("50");
    if(maxRows >= 100 ) ui->Cb_rows->addItem("100");

}

void F_ListUsers::initListNumberPages()
{
    ui->Cb_pages->clear();
    int maxRows   = queryModelUser->rowCount();
    int RowsCount = ui->Cb_rows->currentText().toInt();

    int NumPages  = maxRows/RowsCount;
    int restPages = maxRows%RowsCount;

    qDebug()<<"Number Pages : "<< NumPages
            <<"Rest   Pages : " << restPages;
    int save_i = 0;
    for(int i=1; i<= NumPages;i++)
    {
        ui->Cb_pages->addItem(QString::number(i));
        save_i = i;
    }

    if(restPages > 0) ui->Cb_pages->addItem(QString::number(save_i+1));
}

void F_ListUsers::showPageRows()
{
    hideAllRows();
    int startIdx =0;
    int numRowsVisible =0;
    if(ui->Cb_pages->count()>0 && ui->Cb_rows->count()>0)
    {
        startIdx = (ui->Cb_pages->currentText().toInt()-1)*ui->Cb_rows->currentText().toInt();
        numRowsVisible = ui->Cb_rows->currentText().toInt();

        int endIdx = startIdx+numRowsVisible;
        if(endIdx>queryModelUser->rowCount()) endIdx = queryModelUser->rowCount();

        for(int i = startIdx; i< endIdx; i++)
        {
            ui->tableView->showRow(i);
        }
    }
}

void F_ListUsers::updateTableViewRows()
{
    initListNumberPages();
    showPageRows();
}

void F_ListUsers::createMapper()
{
    mapper->setModel(proxyModelUser);

    mapper->addMapping(ui->Sb_IDUser,0);
    mapper->addMapping(ui->Le_firstName,1);
    mapper->addMapping(ui->Le_lastName,2);
    mapper->addMapping(ui->Le_email,3);
    mapper->addMapping(ui->Le_group,4);
    mapper->addMapping(ui->Le_company,5);
    mapper->addMapping(ui->Le_status,6);
}

void F_ListUsers::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Delete)
    {
        // deleteWarehouse();
    }
}
