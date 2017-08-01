#include "f_units.h"
#include "ui_f_units.h"

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
        deleteUnit();
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
    DB->mRemoveDatabase("_units_");
    delete ui;
}
