#include "f_units.h"
#include "ui_f_units.h"
#include "../mdialog.h"
F_Units::F_Units(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_Units)
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

    DB = new DBH("_units_");

    mapper    = new QDataWidgetMapper();
    modelUnit = new QSqlTableModel(this,DB->getCnx());
    modelUnit->setTable("units");
    modelUnit->select();

    modelUnit->setHeaderData(0, Qt::Horizontal, tr("N#"));
    modelUnit->setHeaderData(1, Qt::Horizontal, tr("Size Name"));
    modelUnit->setHeaderData(2, Qt::Horizontal, tr("Measurement"));

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->setSortingEnabled(true);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    proxyModelUnit = new QSortFilterProxyModel(this);
    proxyModelUnit->setSourceModel(modelUnit);

    proxyModelUnit->setFilterRegExp(QRegExp("", Qt::CaseInsensitive,QRegExp::FixedString));
    proxyModelUnit->setFilterKeyColumn(1);

    ui->tableView->setModel(proxyModelUnit);

    ui->tableView->setVisible(false);
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->setWordWrap(true);

    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
    //ui->tableView->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->stretchLastSection();
    ui->tableView->verticalHeader()->stretchLastSection();

    ui->tableView->setVisible(true);

    mapper->setSubmitPolicy(mapper->ManualSubmit);
    createMapper();

    connect(ui->tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            mapper, SLOT(setCurrentModelIndex(QModelIndex)));


    connect(ui->Bt_AddNew,SIGNAL(clicked(bool)),ui->F_AddNew,SLOT(show()));
    connect(ui->Bt_cancel,SIGNAL(clicked(bool)),ui->F_AddNew,SLOT(hide()));

    connect(ui->Bt_save,SIGNAL(clicked(bool)),this,SLOT(addUnit()));

}

void F_Units::addUnit()
{
    if(ui->Le_sizeName->text().isEmpty() || ui->Le_measurement->text().isEmpty())
    {
        //mToast = new Toast();
        //mToast->setMessage(tr("Fill Both Values For Size Name & Measurement"));
    }else
    {
        DB->addUnit(ui->Le_sizeName->text(),ui->Le_measurement->text());

        modelUnit->select();

        ui->Le_sizeName->clear();
        ui->Le_measurement->clear();
        ui->F_AddNew->setVisible(false);
    }
}

void F_Units::deleteUnit()
{
    if(ui->Sb_ID->value() >= 0)
    {
        DB->deleteUnit(ui->Sb_ID->value());

        modelUnit->select();
        ui->Sb_ID->setValue(-1);
    }else
    {
        //mToast = new Toast();
        //mToast->setMessage(tr("Select a row unit"));
    }
}

void F_Units::createMapper()
{
    mapper->setModel(proxyModelUnit);
    mapper->addMapping(ui->Sb_ID,modelUnit->fieldIndex("id"));
}

void F_Units::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Delete) {
        MDialog *mDialog = new MDialog();
        mDialog->setMessage("Do You Really Want To Delete This Unit ?");
        if(mDialog->exec() == 1 )
            deleteUnit();
        mDialog->close();
        mDialog->deleteLater();
//        this->showMaximized();
    }
}

//bool F_Units::event(QEvent *event)
//{
//    if (event->type() == QEvent::KeyPress) {
//            QKeyEvent *keys = static_cast<QKeyEvent *>(event);
//            if (keys->key() == Qt::Key_Delete) {
//                deleteUnit();
//                return true;
//            }
//    }
//    return true;
//}


F_Units::~F_Units()
{
    #ifdef _WIN32
        DB->mRemoveDatabase("_units_");
    #endif
    delete ui;
}
