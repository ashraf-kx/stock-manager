#include "f_listusers.h"
#include "ui_f_listusers.h"
#include <math.h>

Q_LOGGING_CATEGORY(PLU,"people.listusers")

F_ListUsers::F_ListUsers(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_ListUsers)
{
    ui->setupUi(this);
    this->setStyleSheet(Style::loadStyle("listUsers"));


    ui->Sb_IDUser->setVisible(false);

//    QGraphicsDropShadowEffect *sh = new QGraphicsDropShadowEffect();
//    sh->setBlurRadius(8);
//    sh->setOffset(2);
//    sh->setColor(QColor(63, 63, 63, 180));
//    this->setGraphicsEffect(sh);

    mCfgDb         = new Cfg_Db();
    DB             = new DBH("_listUsers_");

    mapper         = new QDataWidgetMapper();
    queryModelUser = new QSqlQueryModel();

    queryModelUser->setQuery("SELECT `id`,`first_name`,`last_name`,`username`,`email`,`status`,"
                             "`created_on`,`group_id`,`company_id` FROM `users`",DB->getCnx());

    TA.clear();
    TA["id"]         = 0;
    TA["first_name"] = 1;
    TA["last_name"]  = 2;
    TA["username"]   = 3;
    TA["email"]      = 4;
    TA["status"]     = 5;
    TA["created_on"] = 6;
    TA["group_id"]   = 7;
    TA["company_id"] = 8;

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->setSortingEnabled(true);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    proxyModelUser = new QSortFilterProxyModel(this);
    proxyModelUser->setSourceModel(queryModelUser);

    ui->tableView->setModel(proxyModelUser);

    ui->tableView->setColumnHidden(0,true);

    queryModelUser->setHeaderData(TA["id"], Qt::Horizontal, tr("N#"));
    queryModelUser->setHeaderData(TA["first_name"], Qt::Horizontal, tr("First Name"));
    queryModelUser->setHeaderData(TA["last_name"], Qt::Horizontal, tr("Last Name"));
    queryModelUser->setHeaderData(TA["username"], Qt::Horizontal, tr("User Name"));
    queryModelUser->setHeaderData(TA["group_id"], Qt::Horizontal, tr("Group"));
    queryModelUser->setHeaderData(TA["email"], Qt::Horizontal, tr("Email"));
    queryModelUser->setHeaderData(TA["company_id"], Qt::Horizontal, tr("Company"));
    queryModelUser->setHeaderData(TA["created_on"], Qt::Horizontal, tr("Created on"));
    queryModelUser->setHeaderData(TA["status"], Qt::Horizontal, tr("Status"));

    ui->tableView->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->stretchLastSection();
    ui->tableView->verticalHeader()->stretchLastSection();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
    ui->tableView->horizontalHeader()->setResizeContentsPrecision(0);
    ui->tableView->setWordWrap(true);
    ui->tableView->setVisible(true);

    mapper->setSubmitPolicy(mapper->ManualSubmit);
    createMapper();

    initListRowsPerPage();
    ui->Cb_rows->setCurrentIndex(0);

    ui->Bt_editRow->setGraphicsEffect(Style::shadowbutton());

    ui->bt_cancel->setGraphicsEffect(Style::shadowbutton());
    ui->Bt_save->setGraphicsEffect(Style::shadowbutton());

    ui->Bt_previous->setGraphicsEffect(Style::shadowbutton());
    ui->Bt_next->setGraphicsEffect(Style::shadowbutton());

    ui->frame->setGraphicsEffect(Style::shadow());
    // NOTE : QModelIndex(nbrRow,nbrColumn)(New Clicked Index); QModelIndex(nbrRow,nbrColumn)(New Clicked Index).
    connect(ui->tableView->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(setmModelIndex(QModelIndex,QModelIndex)));

    connect(ui->tableView->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(selectedColumn(QModelIndex,QModelIndex)));

    connect(ui->Cb_rows,SIGNAL(currentTextChanged(QString)),this,SLOT(updateTableViewRows()));
    connect(ui->Cb_pages,SIGNAL(currentTextChanged(QString)),this,SLOT(showPageRows()));

    connect(ui->W_search->getLineEdit(),SIGNAL(textChanged(QString)),
            proxyModelUser,SLOT(setFilterRegExp(QString)));

    connect(ui->Bt_previous,SIGNAL(clicked(bool)),this,SLOT(previousPage()));
    connect(ui->Bt_next,SIGNAL(clicked(bool)),this,SLOT(nextPage()));

    connect(ui->Bt_editRow,SIGNAL(clicked(bool)),this,SLOT(visibility()));

    currentSize = QSize(300,500);
    isFrameUpdate = false;
    ui->frame->setVisible(false);

}

void F_ListUsers::setmModelIndex(QModelIndex idx,QModelIndex idx2)
{
    Q_UNUSED(idx2);

    mapper->setCurrentModelIndex(idx);
}

void F_ListUsers::showFrameUpdate()
{
    ui->frame->setVisible(!ui->frame->isVisible());
}

void F_ListUsers::updateMessageInfo()
{
    int startIdx =0;
    int numRowsVisible =0;
    int modelRows = queryModelUser->rowCount();
    if(ui->Cb_pages->count()>0 && ui->Cb_rows->count()>0)
    {
        startIdx = (ui->Cb_pages->currentText().toInt()-1)*ui->Cb_rows->currentText().toInt();
        numRowsVisible = ui->Cb_rows->currentText().toInt();

        int endIdx = startIdx+numRowsVisible;
        if(endIdx>modelRows) endIdx = modelRows;
        ui->L_info->setText(tr("Showing ")+QString::number(startIdx+1)+
                            tr(" to ")+QString::number(endIdx)+
                            tr(" From ")+QString::number(modelRows)+
                            tr(" Entries."));
    }
}

void F_ListUsers::nextPage()
{
    int idxCurrent = ui->Cb_pages->currentIndex();
    if(idxCurrent < ui->Cb_pages->count()-1 )
    {
        ui->Cb_pages->setCurrentIndex(idxCurrent+1);
        updateMessageInfo();
    }
}

void F_ListUsers::previousPage()
{
    int idxCurrent = ui->Cb_pages->currentIndex();
    if(idxCurrent > 0 )
    {
        ui->Cb_pages->setCurrentIndex(idxCurrent-1);
        updateMessageInfo();
    }
}

void F_ListUsers::selectedColumn(QModelIndex idx,QModelIndex idx2)
{
    Q_UNUSED(idx2)
    qDebug()<<"row : "<<idx.row()<<"Collumn : "<<idx.column();

   idxColSelected = idx.column();//ui->tableView->currentIndex().column();
   if(idxColSelected >= 0 )
   {
       proxyModelUser->setFilterRegExp(QRegExp("", Qt::CaseInsensitive));
       proxyModelUser->setFilterKeyColumn(idxColSelected);
       ui->W_search->setPlaceHolder(tr("Search By ")+queryModelUser->headerData(idxColSelected,Qt::Horizontal,Qt::DisplayRole).toString());
   }
}

F_ListUsers::~F_ListUsers()
{
    #ifdef _WIN32
       // DB->mRemoveDatabase("_listUsers_");
    #endif
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

    int save_i = 0;
    for(int i=1; i<= NumPages;i++)
    {
        ui->Cb_pages->addItem(QString::number(i));
        save_i = i;
    }

    if(restPages > 0) ui->Cb_pages->addItem(QString::number(save_i+1));
    updateMessageInfo();
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
        updateMessageInfo();
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
    mapper->addMapping(ui->Sb_IDUser,TA["id"]);

    ui->W_firstname->showLineEdit();
    mapper->addMapping(ui->W_firstname->getLineEdit(),TA["first_name"]);

    ui->W_lastname->showLineEdit();
    mapper->addMapping(ui->W_lastname->getLineEdit(),TA["last_name"]);

    ui->W_username->showLineEdit();
    mapper->addMapping(ui->W_username->getLineEdit(),TA["username"]);

    ui->W_email->showLineEdit();
    mapper->addMapping(ui->W_email->getLineEdit(),TA["email"]);

    ui->W_group->showLineEdit();
    mapper->addMapping(ui->W_group->getLineEdit(),TA["group_id"]);

    ui->W_company->showLineEdit();
    mapper->addMapping(ui->W_company->getLineEdit(),TA["company_id"]);

    ui->W_status->showLineEdit();
    mapper->addMapping(ui->W_status->getLineEdit(),TA["status"]);
}

void F_ListUsers::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Delete)
    {
        // deleteWarehouse();
        // TODO : Delete user in a safe way if it's not needed,( duplicated or mis-inserting record).
        // delicate situation CAREFULL PLEASE.
    }
}

void F_ListUsers::visibility()
{
    if(isFrameUpdate)
        isFrameUpdate = false;
    else
        isFrameUpdate = true;

    if(isFrameUpdate)
        slideIn();
    else
        slideOut();
}

//! [ Animation Come In Come out ]
void F_ListUsers::slideIn() // <+++++++>
{
    ui->frame->show();
    animateSize = new QPropertyAnimation(ui->frame, "size");
    animateSize->setDuration(200);
    animateSize->setStartValue(QSize(currentSize.width(),0));
    animateSize->setEndValue(currentSize);
    animateSize->setEasingCurve(QEasingCurve::Linear);
    animateSize->start();
}

void F_ListUsers::slideOut() // ---->++<-----
{
    currentSize = ui->frame->size();
    qDebug()<<currentSize;
    animateSize = new QPropertyAnimation(ui->frame, "size");
    animateSize->setDuration(200);               // <==  xMs = yMs = 200
    animateSize->setStartValue(currentSize);
    animateSize->setEndValue(QSize(currentSize.width(),0));
    animateSize->setEasingCurve(QEasingCurve::Linear);
    animateSize->start();
    QTimer::singleShot(200, ui->frame, SLOT(hide())); // <== yMs
}


// FIXME : problem #include "mdlineedit" located in the ui_f_listusers. because the plugin used {first guest}
