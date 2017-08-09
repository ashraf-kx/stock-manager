#include "dashboard.h"
#include "ui_dashboard.h"

Dashboard::Dashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("Stock Manager V 0.0.1"));
    this->setWindowIcon(QIcon("://icons/inventory.png"));
    this->setStyleSheet(Style::loadStyle("MaterialDesgin"));

    QFont f = QFont();
    f.setPointSizeF(14.0);
    this->setFont(f);

    qDebug()<<"font Size of"<<this->objectName()<<this->fontInfo().pointSizeF();

    mTopNav     = new Top_navigator(this);
    mSideNAV    = new Side_navigator(this);

    ui->layoutTop->addWidget(mTopNav);
    ui->layoutMain->addWidget(mSideNAV);

    this->showMaximized();

    //! [Stupidito ] 100%
    // Products
    connect(mSideNAV->getBtnListProducts(),SIGNAL(clicked(bool)),this,SLOT(setFrameListProducts()));
    connect(mSideNAV->getBtnAddProducts(),SIGNAL(clicked(bool)),this,SLOT(setFrameAddProducts()));
    connect(mSideNAV->getBtnImportProducts(),SIGNAL(clicked(bool)),this,SLOT(setFrameImportProducts()));
    connect(mSideNAV->getBtnPrintBarcode(),SIGNAL(clicked(bool)),this,SLOT(setFramePrintBarcode()));
    connect(mSideNAV->getBtnQuantityAdjustments(),SIGNAL(clicked(bool)),this,SLOT(setFrameQuantityAdjustments()));
    connect(mSideNAV->getBtnAddAdjustments(),SIGNAL(clicked(bool)),this,SLOT(setFrameAddAdjustments()));
    connect(mSideNAV->getBtnStockCounts(),SIGNAL(clicked(bool)),this,SLOT(setFrameStockCounts()));
    connect(mSideNAV->getBtnCountStock(),SIGNAL(clicked(bool)),this,SLOT(setFrameCountStock()));

    // Sales
    connect(mSideNAV->getBtnListSales(),SIGNAL(clicked(bool)),this,SLOT(setFrameListSales()));
    connect(mSideNAV->getBtnPOSSales(),SIGNAL(clicked(bool)),this,SLOT(setFramePOSSales()));
    connect(mSideNAV->getBtnAddSale(),SIGNAL(clicked(bool)),this,SLOT(setFrameAddSale()));
    connect(mSideNAV->getBtnAddSaleByCSV(),SIGNAL(clicked(bool)),this,SLOT(setFrameAddSaleByCSV()));
    connect(mSideNAV->getBtnDeliveries(),SIGNAL(clicked(bool)),this,SLOT(setFrameDeliveries()));
    connect(mSideNAV->getBtnListGiftCards(),SIGNAL(clicked(bool)),this,SLOT(setFrameListGiftCards()));

    // Quotations
    connect(mSideNAV->getBtnListQuotations(),SIGNAL(clicked(bool)),this,SLOT(setFrameListQuotations()));
    connect(mSideNAV->getBtnAddQuotations(),SIGNAL(clicked(bool)),this,SLOT(setFrameAddQuotations()));

    // Purchases
    connect(mSideNAV->getBtnListPurchases(),SIGNAL(clicked(bool)),this,SLOT(setFrameListPurchases()));
    connect(mSideNAV->getBtnAddPurchase(),SIGNAL(clicked(bool)),this,SLOT(setFrameAddPurchase()));
    connect(mSideNAV->getBtnAddPurchasesByCSV(),SIGNAL(clicked(bool)),this,SLOT(setFrameAddPurchasesByCSV()));
    connect(mSideNAV->getBtnListExpenses(),SIGNAL(clicked(bool)),this,SLOT(setFrameListExpenses()));
    connect(mSideNAV->getBtnAddExpense(),SIGNAL(clicked(bool)),this,SLOT(setFrameAddExpense()));

    // Transfers
    connect(mSideNAV->getBtnListTransfers(),SIGNAL(clicked(bool)),this,SLOT(setFrameListTransfers()));
    connect(mSideNAV->getBtnAddTransfer(),SIGNAL(clicked(bool)),this,SLOT(setFrameAddTransfer()));
    connect(mSideNAV->getBtnAddTransferByCSV(),SIGNAL(clicked(bool)),this,SLOT(setFrameAddTransferByCSV()));

    // People
    connect(mSideNAV->getBtnListUsers(),SIGNAL(clicked(bool)),this,SLOT(setFrameListUsers()));
    connect(mSideNAV->getBtnAddUser(),SIGNAL(clicked(bool)),this,SLOT(setFrameAddUser()));

    connect(mSideNAV->getBtnListBillers(),SIGNAL(clicked(bool)),this,SLOT(setFrameListBillers()));
    connect(mSideNAV->getBtnAddBiller(),SIGNAL(clicked(bool)),this,SLOT(setFrameAddBiller()));

    connect(mSideNAV->getBtnListCustomers(),SIGNAL(clicked(bool)),this,SLOT(setFrameListCustomers()));
    connect(mSideNAV->getBtnAddCustomer(),SIGNAL(clicked(bool)),this,SLOT(setFrameAddCustomer()));

    connect(mSideNAV->getBtnListSuppliers(),SIGNAL(clicked(bool)),this,SLOT(setFrameListSuppliers()));
    connect(mSideNAV->getBtnAddSupplier(),SIGNAL(clicked(bool)),this,SLOT(setFrameAddSupplier()));

    // Notifications

    // Settings
    connect(mSideNAV->getBtnSystemSettings(),SIGNAL(clicked(bool)),this,SLOT(setFrameSystemSettings()));
    connect(mSideNAV->getBtnPOSSettings(),SIGNAL(clicked(bool)),this,SLOT(setFramePOSSettings()));
    connect(mSideNAV->getBtnListPrinters(),SIGNAL(clicked(bool)),this,SLOT(setFrameListPrinters()));
    connect(mSideNAV->getBtnAddPrinter(),SIGNAL(clicked(bool)),this,SLOT(setFrameAddPrinter()));
    connect(mSideNAV->getBtnChangeLogo(),SIGNAL(clicked(bool)),this,SLOT(setFrameChangeLogo()));
    connect(mSideNAV->getBtnCurrencies(),SIGNAL(clicked(bool)),this,SLOT(setFrameCurrencies()));
    connect(mSideNAV->getBtnCustomerGroups(),SIGNAL(clicked(bool)),this,SLOT(setFrameCustomerGroups()));
    connect(mSideNAV->getBtnPriceGroups(),SIGNAL(clicked(bool)),this,SLOT(setFramePriceGroups()));
    connect(mSideNAV->getBtnCategories(),SIGNAL(clicked(bool)),this,SLOT(setFrameCategories()));
    connect(mSideNAV->getBtnExpenseCategories(),SIGNAL(clicked(bool)),this,SLOT(setFrameExpenseCategories()));
    connect(mSideNAV->getBtnUnits(),SIGNAL(clicked(bool)),this,SLOT(setFrameUnits()));
    connect(mSideNAV->getBtnBrands(),SIGNAL(clicked(bool)),this,SLOT(setFrameBrands()));
    connect(mSideNAV->getBtnVariants(),SIGNAL(clicked(bool)),this,SLOT(setFrameVariants()));
    connect(mSideNAV->getBtnTaxRates(),SIGNAL(clicked(bool)),this,SLOT(setFrameTaxRates()));
    connect(mSideNAV->getBtnWarhouses(),SIGNAL(clicked(bool)),this,SLOT(setFrameWarhouses()));
    connect(mSideNAV->getBtnEmailTemplates(),SIGNAL(clicked(bool)),this,SLOT(setFrameEmailTemplates()));
    connect(mSideNAV->getBtnGroupPermissions(),SIGNAL(clicked(bool)),this,SLOT(setFrameGroupPermissions()));
    connect(mSideNAV->getBtnBackUps(),SIGNAL(clicked(bool)),this,SLOT(setFrameBackUps()));
    connect(mSideNAV->getBtnUpdates(),SIGNAL(clicked(bool)),this,SLOT(setFrameUpdates()));

    // Reports
    connect(mSideNAV->getBtnOverViewChart(),SIGNAL(clicked(bool)),this,SLOT(setFrameOverViewChart()));
    connect(mSideNAV->getBtnWarehouseStockChart(),SIGNAL(clicked(bool)),this,SLOT(setFrameWarehouseStockChart()));
    connect(mSideNAV->getBtnBestSellers(),SIGNAL(clicked(bool)),this,SLOT(setFrameBestSellers()));
    connect(mSideNAV->getBtnRegisterReport(),SIGNAL(clicked(bool)),this,SLOT(setFrameRegisterReport()));
    connect(mSideNAV->getBtnProductQuantityAlerts(),SIGNAL(clicked(bool)),this,SLOT(setFrameProductQuantityAlerts()));
    connect(mSideNAV->getBtnProductsReport(),SIGNAL(clicked(bool)),this,SLOT(setFrameProductsReport()));
    connect(mSideNAV->getBtnAdjutmentsReport(),SIGNAL(clicked(bool)),this,SLOT(setFrameAdjutmentsReport()));
    connect(mSideNAV->getBtnCategoriesReport(),SIGNAL(clicked(bool)),this,SLOT(setFrameCategoriesReport()));
    connect(mSideNAV->getBtnBandsReport(),SIGNAL(clicked(bool)),this,SLOT(setFrameBandsReport()));
    connect(mSideNAV->getBtnDailySales(),SIGNAL(clicked(bool)),this,SLOT(setFrameDailySales()));
    connect(mSideNAV->getBtnMonthlySales(),SIGNAL(clicked(bool)),this,SLOT(setFrameMonthlySales()));
    connect(mSideNAV->getBtnSalesReport(),SIGNAL(clicked(bool)),this,SLOT(setFrameSalesReport()));

}

//! [Stupidito ] 185%
// Products

void Dashboard::setFrameListProducts()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mListProducts = new F_ListProducts(this);
    ui->layoutOneFrame->addWidget(mListProducts);
    mListProducts->setObjectName("ListProducts");
}

void Dashboard::setFrameAddProducts()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mAddProducts = new F_AddProducts(this);
    ui->layoutOneFrame->addWidget(mAddProducts);
    mAddProducts->setObjectName("AddProducts");
}

void Dashboard::setFrameImportProducts()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mImportProducts = new F_ImportProducts(this);
    ui->layoutOneFrame->addWidget(mImportProducts);
    mImportProducts->setObjectName("ImportProducts");
}

void Dashboard::setFramePrintBarcode()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mPrintBarcode = new F_PrintBarcode(this);
    ui->layoutOneFrame->addWidget(mPrintBarcode);
    mPrintBarcode->setObjectName("PrintBarcode");
}

void Dashboard::setFrameQuantityAdjustments()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mQuantityAdjustments = new F_QuantityAdjustments(this);
    ui->layoutOneFrame->addWidget(mQuantityAdjustments);
    mQuantityAdjustments->setObjectName("QuantityAdjustments");
}

void Dashboard::setFrameAddAdjustments()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mAddAdjustments = new F_AddAdjustments(this);
    ui->layoutOneFrame->addWidget(mAddAdjustments);
    mAddAdjustments->setObjectName("AddAdjustments");
}

void Dashboard::setFrameStockCounts()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mStockCounts = new F_StockCounts(this);
    ui->layoutOneFrame->addWidget(mStockCounts);
    mStockCounts->setObjectName("StockCounts");
}

void Dashboard::setFrameCountStock()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mCountStock = new F_CountStock(this);
    ui->layoutOneFrame->addWidget(mCountStock);
    mCountStock->setObjectName("CountStock");
}

// Sales

void Dashboard::setFrameListSales()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mListSales = new F_ListSales(this);
    ui->layoutOneFrame->addWidget(mListSales);
    mListSales->setObjectName("ListSales");
}

void Dashboard::setFramePOSSales()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mPOSSales = new F_POSSales(this);
    ui->layoutOneFrame->addWidget(mPOSSales);
    mPOSSales->setObjectName("POSSales");
}

void Dashboard::setFrameAddSale()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mAddSale = new F_AddSale(this);
    ui->layoutOneFrame->addWidget(mAddSale);
    mAddSale->setObjectName("AddSale");
}

void Dashboard::setFrameAddSaleByCSV()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mAddSaleByCSV = new F_AddSaleByCSV(this);
    ui->layoutOneFrame->addWidget(mAddSaleByCSV);
    mAddSaleByCSV->setObjectName("AddSaleByCSV");
}

void Dashboard::setFrameDeliveries()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mDeliveries = new F_Deliveries(this);
    ui->layoutOneFrame->addWidget(mDeliveries);
    mDeliveries->setObjectName("Deliveries");
}

void Dashboard::setFrameListGiftCards()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mListGiftCards = new F_ListGiftCards(this);
    ui->layoutOneFrame->addWidget(mListGiftCards);
    mListGiftCards->setObjectName("ListGiftCards");
}

// Quotations

void Dashboard::setFrameListQuotations()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mListQuotations = new F_ListQuotations(this);
    ui->layoutOneFrame->addWidget(mListQuotations);
    mListQuotations->setObjectName("ListQuotations");
}

void Dashboard::setFrameAddQuotations()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mAddQuotations = new F_AddQuotations(this);
    ui->layoutOneFrame->addWidget(mAddQuotations);
    mAddQuotations->setObjectName("AddQuotations");
}

// Purchases

void Dashboard::setFrameListPurchases()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mListPurchases = new F_ListPurchases(this);
    ui->layoutOneFrame->addWidget(mListPurchases);
    mListPurchases->setObjectName("ListPurchases");
}

void Dashboard::setFrameAddPurchase()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mAddPurchase = new F_AddPurchase(this);
    ui->layoutOneFrame->addWidget(mAddPurchase);
    mAddPurchase->setObjectName("AddPurchase");
}

void Dashboard::setFrameAddPurchasesByCSV()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mAddPurchasesByCSV = new F_AddPurchasesByCSV(this);
    ui->layoutOneFrame->addWidget(mAddPurchasesByCSV);
    mAddPurchasesByCSV->setObjectName("AddPurchasesByCSV");
}

void Dashboard::setFrameListExpenses()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mListExpenses = new F_ListExpenses(this);
    ui->layoutOneFrame->addWidget(mListExpenses);
    mListExpenses->setObjectName("ListExpenses");
}

void Dashboard::setFrameAddExpense()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mAddExpense = new F_AddExpense(this);
    ui->layoutOneFrame->addWidget(mAddExpense);
    mAddExpense->setObjectName("AddExpense");
}

// Transfers

void Dashboard::setFrameListTransfers()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mListTransfers = new F_ListTransfers(this);
    ui->layoutOneFrame->addWidget(mListTransfers);
    mListTransfers->setObjectName("ListTransfers");
}

void Dashboard::setFrameAddTransfer()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mAddTransfer = new F_AddTransfer(this);
    ui->layoutOneFrame->addWidget(mAddTransfer);
    mAddTransfer->setObjectName("AddTransfer");
}

void Dashboard::setFrameAddTransferByCSV()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mAddTransferByCSV = new F_AddTransferByCSV(this);
    ui->layoutOneFrame->addWidget(mAddTransferByCSV);
    mAddTransferByCSV->setObjectName("AddTransferByCSV");
}

// People

void Dashboard::setFrameListUsers()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mListUsers = new F_ListUsers(this);
    ui->layoutOneFrame->addWidget(mListUsers);
    mListUsers->setObjectName("ListUsers");
}

void Dashboard::setFrameAddUser()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mAddUser = new F_AddUser(this);
    ui->layoutOneFrame->addWidget(mAddUser);
    mAddUser->setObjectName("AddUser");
}


void Dashboard::setFrameListBillers()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mListBillers = new F_ListBillers(this);
    ui->layoutOneFrame->addWidget(mListBillers);
    mListBillers->setObjectName("ListBillers");
}

void Dashboard::setFrameAddBiller()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mAddBiller = new F_AddBiller(this);
    ui->layoutOneFrame->addWidget(mAddBiller);
    mAddBiller->setObjectName("AddBiller");
}


void Dashboard::setFrameListCustomers()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mListCustomers = new F_ListCustomers(this);
    ui->layoutOneFrame->addWidget(mListCustomers);
    mListCustomers->setObjectName("ListCustomers");
}

void Dashboard::setFrameAddCustomer()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mAddCustomer = new F_AddCustomer(this);
    ui->layoutOneFrame->addWidget(mAddCustomer);
    mAddCustomer->setObjectName("AddCustomer");
}


void Dashboard::setFrameListSuppliers()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mListSuppliers = new F_ListSuppliers(this);
    ui->layoutOneFrame->addWidget(mListSuppliers);
    mListSuppliers->setObjectName("ListSuppliers");
}

void Dashboard::setFrameAddSupplier()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mAddSupplier = new F_AddSupplier(this);
    ui->layoutOneFrame->addWidget(mAddSupplier);
    mAddSupplier->setObjectName("AddSupplier");
}

// Notifications

// Settings

void Dashboard::setFrameSystemSettings()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mSystemSettings = new F_SystemSettings(this);
    ui->layoutOneFrame->addWidget(mSystemSettings);
    mSystemSettings->setObjectName("SystemSettings");
}

void Dashboard::setFramePOSSettings()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mPOSSettings = new F_POSSettings(this);
    ui->layoutOneFrame->addWidget(mPOSSettings);
    mPOSSettings->setObjectName("POSSettings");
}

void Dashboard::setFrameListPrinters()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mListPrinters = new F_ListPrinters(this);
    ui->layoutOneFrame->addWidget(mListPrinters);
    mListPrinters->setObjectName("ListPrinters");
}

void Dashboard::setFrameAddPrinter()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mAddPrinter = new F_AddPrinter(this);
    ui->layoutOneFrame->addWidget(mAddPrinter);
    mAddPrinter->setObjectName("AddPrinter");
}

void Dashboard::setFrameChangeLogo()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mChangeLogo = new F_ChangeLogo(this);
    ui->layoutOneFrame->addWidget(mChangeLogo);
    mChangeLogo->setObjectName("ChangeLogo");
}

void Dashboard::setFrameCurrencies()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mCurrencies = new F_Currencies(this);
    ui->layoutOneFrame->addWidget(mCurrencies);
    mCurrencies->setObjectName("Currencies");
}

void Dashboard::setFrameCustomerGroups()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mCustomerGroups = new F_CustomerGroups(this);
    ui->layoutOneFrame->addWidget(mCustomerGroups);
    mCustomerGroups->setObjectName("CustomerGroups");
}

void Dashboard::setFramePriceGroups()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mPriceGroups = new F_PriceGroups(this);
    ui->layoutOneFrame->addWidget(mPriceGroups);
    mPriceGroups->setObjectName("PriceGroups");
}

void Dashboard::setFrameCategories()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mCategories = new F_Categories(this);
    ui->layoutOneFrame->addWidget(mCategories);
    mCategories->setObjectName("Categories");
}

void Dashboard::setFrameExpenseCategories()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mExpenseCategories = new F_ExpenseCategories(this);
    ui->layoutOneFrame->addWidget(mExpenseCategories);
    mExpenseCategories->setObjectName("ExpenseCategories");
}

void Dashboard::setFrameUnits()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mUnits = new F_Units(this);
    ui->layoutOneFrame->addWidget(mUnits);
    mUnits->setObjectName("Units");
}

void Dashboard::setFrameBrands()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mBrands = new F_Brands(this);
    ui->layoutOneFrame->addWidget(mBrands);
    mBrands->setObjectName("Brands");
}

void Dashboard::setFrameVariants()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mVariants = new F_Variants(this);
    ui->layoutOneFrame->addWidget(mVariants);
    mVariants->setObjectName("Variants");
}

void Dashboard::setFrameTaxRates()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mTaxRates = new F_TaxRates(this);
    ui->layoutOneFrame->addWidget(mTaxRates);
    mTaxRates->setObjectName("TaxRates");
}

void Dashboard::setFrameWarhouses()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mWarhouses = new F_Warhouses(this);
    ui->layoutOneFrame->addWidget(mWarhouses);
    mWarhouses->setObjectName("Warhouses");
}

void Dashboard::setFrameEmailTemplates()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mEmailTemplates = new F_EmailTemplates(this);
    ui->layoutOneFrame->addWidget(mEmailTemplates);
    mEmailTemplates->setObjectName("EmailTemplates");
}

void Dashboard::setFrameGroupPermissions()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mGroupPermissions = new F_GroupPermissions(this);
    ui->layoutOneFrame->addWidget(mGroupPermissions);
    mGroupPermissions->setObjectName("GroupPermissions");
}

void Dashboard::setFrameBackUps()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mBackUps = new F_BackUps(this);
    ui->layoutOneFrame->addWidget(mBackUps);
    mBackUps->setObjectName("BackUps");
}

void Dashboard::setFrameUpdates()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mUpdates = new F_Updates(this);
    ui->layoutOneFrame->addWidget(mUpdates);
    mUpdates->setObjectName("Updates");
}

// Reports

void Dashboard::setFrameOverViewChart()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mOverViewChart = new F_OverViewChart(this);
    ui->layoutOneFrame->addWidget(mOverViewChart);
    mOverViewChart->setObjectName("OverViewChart");
}

void Dashboard::setFrameWarehouseStockChart()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mWarehouseStockChart = new F_WarehouseStockChart(this);
    ui->layoutOneFrame->addWidget(mWarehouseStockChart);
    mWarehouseStockChart->setObjectName("WarehouseStockChart");
}

void Dashboard::setFrameBestSellers()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mBestSellers = new F_BestSellers(this);
    ui->layoutOneFrame->addWidget(mBestSellers);
    mBestSellers->setObjectName("BestSellers");
}

void Dashboard::setFrameRegisterReport()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mRegisterReport = new F_RegisterReport(this);
    ui->layoutOneFrame->addWidget(mRegisterReport);
    mRegisterReport->setObjectName("RegisterReport");
}

void Dashboard::setFrameProductQuantityAlerts()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mProductQuantityAlerts = new F_ProductQuantityAlerts(this);
    ui->layoutOneFrame->addWidget(mProductQuantityAlerts);
    mProductQuantityAlerts->setObjectName("ProductQuantityAlerts");
}

void Dashboard::setFrameProductsReport()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mProductsReport = new F_ProductsReport(this);
    ui->layoutOneFrame->addWidget(mProductsReport);
    mProductsReport->setObjectName("ProductsReport");
}

void Dashboard::setFrameAdjutmentsReport()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mAdjutmentsReport = new F_AdjutmentsReport(this);
    ui->layoutOneFrame->addWidget(mAdjutmentsReport);
    mAdjutmentsReport->setObjectName("AdjutmentsReport");
}

void Dashboard::setFrameCategoriesReport()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mCategoriesReport = new F_CategoriesReport(this);
    ui->layoutOneFrame->addWidget(mCategoriesReport);
    mCategoriesReport->setObjectName("CategoriesReport");
}

void Dashboard::setFrameBandsReport()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mBandsReport = new F_BandsReport(this);
    ui->layoutOneFrame->addWidget(mBandsReport);
    mBandsReport->setObjectName("BandsReport");
}

void Dashboard::setFrameDailySales()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mDailySales = new F_DailySales(this);
    ui->layoutOneFrame->addWidget(mDailySales);
    mDailySales->setObjectName("DailySales");
}

void Dashboard::setFrameMonthlySales()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mMonthlySales = new F_MonthlySales(this);
    ui->layoutOneFrame->addWidget(mMonthlySales);
    mMonthlySales->setObjectName("MonthlySales");
}

void Dashboard::setFrameSalesReport()
{
    // Clear Old Frame
    foreach(QFrame *oldFrame,ui->mainFrame->findChildren<QFrame*>(QRegularExpression(""),Qt::FindDirectChildrenOnly))
    {
        qDebug()<<"Deleted : "<<oldFrame->objectName()<<"\n";
        delete oldFrame;
    }
    // Place the new One.
    mSalesReport = new F_SalesReport(this);
    ui->layoutOneFrame->addWidget(mSalesReport);
    mSalesReport->setObjectName("SalesReport");
}

Dashboard::~Dashboard()
{
    delete ui;
}
