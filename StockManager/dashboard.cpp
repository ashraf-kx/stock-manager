#include "dashboard.h"

Dashboard::Dashboard(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    this->setWindowTitle(tr("Stock Manager V 0.0.1"));
    this->setWindowIcon(QIcon("://icons/inventory.png"));
    this->setStyleSheet(Style::loadStyle("MaterialDesgin"));

    QFont f = QFont();
    f.setPointSizeF(14.0);
    this->setFont(f);

    mTopNav     = new Top_navigator(this);
    mSideNAV    = new Side_navigator(this);

    gridLayout->addWidget(mTopNav,0,0,1,2);
    gridLayout->addWidget(mSideNAV,1,0,1,1);

    this->showMaximized();

    connect(mTopNav->getBtToolBox(),SIGNAL(clicked(bool)),
            mSideNAV,SLOT(visibility()));

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
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mListProducts = new F_ListProducts(this);
    gridLayout->addWidget(mListProducts,1,1,1,1);
    mListProducts->setObjectName("ListProducts");
}

void Dashboard::setFrameAddProducts()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mAddProducts = new F_AddProducts(this);
    gridLayout->addWidget(mAddProducts,1,1,1,1);
    mAddProducts->setObjectName("AddProducts");
}

void Dashboard::setFrameImportProducts()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mImportProducts = new F_ImportProducts(this);
    gridLayout->addWidget(mImportProducts,1,1,1,1);
    mImportProducts->setObjectName("ImportProducts");
}

void Dashboard::setFramePrintBarcode()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mPrintBarcode = new F_PrintBarcode(this);
    gridLayout->addWidget(mPrintBarcode,1,1,1,1);
    mPrintBarcode->setObjectName("PrintBarcode");
}

void Dashboard::setFrameQuantityAdjustments()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mQuantityAdjustments = new F_QuantityAdjustments(this);
    gridLayout->addWidget(mQuantityAdjustments,1,1,1,1);
    mQuantityAdjustments->setObjectName("QuantityAdjustments");
}

void Dashboard::setFrameAddAdjustments()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mAddAdjustments = new F_AddAdjustments(this);
    gridLayout->addWidget(mAddAdjustments,1,1,1,1);
    mAddAdjustments->setObjectName("AddAdjustments");
}

void Dashboard::setFrameStockCounts()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mStockCounts = new F_StockCounts(this);
    gridLayout->addWidget(mStockCounts,1,1,1,1);
    mStockCounts->setObjectName("StockCounts");
}

void Dashboard::setFrameCountStock()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mCountStock = new F_CountStock(this);
    gridLayout->addWidget(mCountStock,1,1,1,1);
    mCountStock->setObjectName("CountStock");
}

// Sales

void Dashboard::setFrameListSales()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mListSales = new F_ListSales(this);
    gridLayout->addWidget(mListSales,1,1,1,1);
    mListSales->setObjectName("ListSales");
}

void Dashboard::setFramePOSSales()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mPOSSales = new F_POSSales(this);
    gridLayout->addWidget(mPOSSales,1,1,1,1);
    mPOSSales->setObjectName("POSSales");
}

void Dashboard::setFrameAddSale()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mAddSale = new F_AddSale(this);
    gridLayout->addWidget(mAddSale,1,1,1,1);
    mAddSale->setObjectName("AddSale");
}

void Dashboard::setFrameAddSaleByCSV()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mAddSaleByCSV = new F_AddSaleByCSV(this);
    gridLayout->addWidget(mAddSaleByCSV,1,1,1,1);
    mAddSaleByCSV->setObjectName("AddSaleByCSV");
}

void Dashboard::setFrameDeliveries()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mDeliveries = new F_Deliveries(this);
    gridLayout->addWidget(mDeliveries,1,1,1,1);
    mDeliveries->setObjectName("Deliveries");
}

void Dashboard::setFrameListGiftCards()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mListGiftCards = new F_ListGiftCards(this);
    gridLayout->addWidget(mListGiftCards,1,1,1,1);
    mListGiftCards->setObjectName("ListGiftCards");
}

// Quotations

void Dashboard::setFrameListQuotations()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mListQuotations = new F_ListQuotations(this);
    gridLayout->addWidget(mListQuotations,1,1,1,1);
    mListQuotations->setObjectName("ListQuotations");
}

void Dashboard::setFrameAddQuotations()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mAddQuotations = new F_AddQuotations(this);
    gridLayout->addWidget(mAddQuotations,1,1,1,1);
    mAddQuotations->setObjectName("AddQuotations");
}

// Purchases

void Dashboard::setFrameListPurchases()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mListPurchases = new F_ListPurchases(this);
    gridLayout->addWidget(mListPurchases,1,1,1,1);
    mListPurchases->setObjectName("ListPurchases");
}

void Dashboard::setFrameAddPurchase()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mAddPurchase = new F_AddPurchase(this);
    gridLayout->addWidget(mAddPurchase,1,1,1,1);
    mAddPurchase->setObjectName("AddPurchase");
}

void Dashboard::setFrameAddPurchasesByCSV()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mAddPurchasesByCSV = new F_AddPurchasesByCSV(this);
    gridLayout->addWidget(mAddPurchasesByCSV,1,1,1,1);
    mAddPurchasesByCSV->setObjectName("AddPurchasesByCSV");
}

void Dashboard::setFrameListExpenses()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mListExpenses = new F_ListExpenses(this);
    gridLayout->addWidget(mListExpenses,1,1,1,1);
    mListExpenses->setObjectName("ListExpenses");
}

void Dashboard::setFrameAddExpense()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mAddExpense = new F_AddExpense(this);
    gridLayout->addWidget(mAddExpense,1,1,1,1);
    mAddExpense->setObjectName("AddExpense");
}

// Transfers

void Dashboard::setFrameListTransfers()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mListTransfers = new F_ListTransfers(this);
    gridLayout->addWidget(mListTransfers,1,1,1,1);
    mListTransfers->setObjectName("ListTransfers");
}

void Dashboard::setFrameAddTransfer()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mAddTransfer = new F_AddTransfer(this);
    gridLayout->addWidget(mAddTransfer,1,1,1,1);
    mAddTransfer->setObjectName("AddTransfer");
}

void Dashboard::setFrameAddTransferByCSV()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mAddTransferByCSV = new F_AddTransferByCSV(this);
    gridLayout->addWidget(mAddTransferByCSV,1,1,1,1);
    mAddTransferByCSV->setObjectName("AddTransferByCSV");
}

// People

void Dashboard::setFrameListUsers()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mListUsers = new F_ListUsers(this);
    gridLayout->addWidget(mListUsers,1,1,1,1);
    mListUsers->setObjectName("ListUsers");
}

void Dashboard::setFrameAddUser()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mAddUser = new F_AddUser(this);
    gridLayout->addWidget(mAddUser,1,1,1,1);
    mAddUser->setObjectName("AddUser");
}


void Dashboard::setFrameListBillers()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mListBillers = new F_ListBillers(this);
    gridLayout->addWidget(mListBillers,1,1,1,1);
    mListBillers->setObjectName("ListBillers");
}

void Dashboard::setFrameAddBiller()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mAddBiller = new F_AddBiller(this);
    gridLayout->addWidget(mAddBiller,1,1,1,1);
    mAddBiller->setObjectName("AddBiller");
}


void Dashboard::setFrameListCustomers()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mListCustomers = new F_ListCustomers(this);
    gridLayout->addWidget(mListCustomers,1,1,1,1);
    mListCustomers->setObjectName("ListCustomers");
}

void Dashboard::setFrameAddCustomer()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mAddCustomer = new F_AddCustomer(this);
    gridLayout->addWidget(mAddCustomer,1,1,1,1);
    mAddCustomer->setObjectName("AddCustomer");
}


void Dashboard::setFrameListSuppliers()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mListSuppliers = new F_ListSuppliers(this);
    gridLayout->addWidget(mListSuppliers,1,1,1,1);
    mListSuppliers->setObjectName("ListSuppliers");
}

void Dashboard::setFrameAddSupplier()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mAddSupplier = new F_AddSupplier(this);
    gridLayout->addWidget(mAddSupplier,1,1,1,1);
    mAddSupplier->setObjectName("AddSupplier");
}

// Notifications

// Settings

void Dashboard::setFrameSystemSettings()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mSystemSettings = new F_SystemSettings(this);
    gridLayout->addWidget(mSystemSettings,1,1,1,1);
    mSystemSettings->setObjectName("SystemSettings");
}

void Dashboard::setFramePOSSettings()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mPOSSettings = new F_POSSettings(this);
    gridLayout->addWidget(mPOSSettings,1,1,1,1);
    mPOSSettings->setObjectName("POSSettings");
}

void Dashboard::setFrameListPrinters()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mListPrinters = new F_ListPrinters(this);
    gridLayout->addWidget(mListPrinters,1,1,1,1);
    mListPrinters->setObjectName("ListPrinters");
}

void Dashboard::setFrameAddPrinter()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mAddPrinter = new F_AddPrinter(this);
    gridLayout->addWidget(mAddPrinter,1,1,1,1);
    mAddPrinter->setObjectName("AddPrinter");
}

void Dashboard::setFrameChangeLogo()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mChangeLogo = new F_ChangeLogo(this);
    gridLayout->addWidget(mChangeLogo,1,1,1,1);
    mChangeLogo->setObjectName("ChangeLogo");
}

void Dashboard::setFrameCurrencies()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mCurrencies = new F_Currencies(this);
    gridLayout->addWidget(mCurrencies,1,1,1,1);
    mCurrencies->setObjectName("Currencies");
}

void Dashboard::setFrameCustomerGroups()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mCustomerGroups = new F_CustomerGroups(this);
    gridLayout->addWidget(mCustomerGroups,1,1,1,1);
    mCustomerGroups->setObjectName("CustomerGroups");
}

void Dashboard::setFramePriceGroups()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mPriceGroups = new F_PriceGroups(this);
    gridLayout->addWidget(mPriceGroups,1,1,1,1);
    mPriceGroups->setObjectName("PriceGroups");
}

void Dashboard::setFrameCategories()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mCategories = new F_Categories(this);
    gridLayout->addWidget(mCategories,1,1,1,1);
    mCategories->setObjectName("Categories");
}

void Dashboard::setFrameExpenseCategories()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mExpenseCategories = new F_ExpenseCategories(this);
    gridLayout->addWidget(mExpenseCategories,1,1,1,1);
    mExpenseCategories->setObjectName("ExpenseCategories");
}

void Dashboard::setFrameUnits()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mUnits = new F_Units(this);
    gridLayout->addWidget(mUnits,1,1,1,1);
    mUnits->setObjectName("Units");
}

void Dashboard::setFrameBrands()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mBrands = new F_Brands(this);
    gridLayout->addWidget(mBrands,1,1,1,1);
    mBrands->setObjectName("Brands");
}

void Dashboard::setFrameVariants()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mVariants = new F_Variants(this);
    gridLayout->addWidget(mVariants,1,1,1,1);
    mVariants->setObjectName("Variants");
}

void Dashboard::setFrameTaxRates()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mTaxRates = new F_TaxRates(this);
    gridLayout->addWidget(mTaxRates,1,1,1,1);
    mTaxRates->setObjectName("TaxRates");
}

void Dashboard::setFrameWarhouses()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mWarhouses = new F_Warhouses(this);
    gridLayout->addWidget(mWarhouses,1,1,1,1);
    mWarhouses->setObjectName("Warhouses");
}

void Dashboard::setFrameEmailTemplates()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mEmailTemplates = new F_EmailTemplates(this);
    gridLayout->addWidget(mEmailTemplates,1,1,1,1);
    mEmailTemplates->setObjectName("EmailTemplates");
}

void Dashboard::setFrameGroupPermissions()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mGroupPermissions = new F_GroupPermissions(this);
    gridLayout->addWidget(mGroupPermissions,1,1,1,1);
    mGroupPermissions->setObjectName("GroupPermissions");
}

void Dashboard::setFrameBackUps()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mBackUps = new F_BackUps(this);
    gridLayout->addWidget(mBackUps,1,1,1,1);
    mBackUps->setObjectName("BackUps");
}

void Dashboard::setFrameUpdates()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mUpdates = new F_Updates(this);
    gridLayout->addWidget(mUpdates,1,1,1,1);
    mUpdates->setObjectName("Updates");
}

// Reports

void Dashboard::setFrameOverViewChart()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mOverViewChart = new F_OverViewChart(this);
    gridLayout->addWidget(mOverViewChart,1,1,1,1);
    mOverViewChart->setObjectName("OverViewChart");
}

void Dashboard::setFrameWarehouseStockChart()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mWarehouseStockChart = new F_WarehouseStockChart(this);
    gridLayout->addWidget(mWarehouseStockChart,1,1,1,1);
    mWarehouseStockChart->setObjectName("WarehouseStockChart");
}

void Dashboard::setFrameBestSellers()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mBestSellers = new F_BestSellers(this);
    gridLayout->addWidget(mBestSellers,1,1,1,1);
    mBestSellers->setObjectName("BestSellers");
}

void Dashboard::setFrameRegisterReport()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mRegisterReport = new F_RegisterReport(this);
    gridLayout->addWidget(mRegisterReport,1,1,1,1);
    mRegisterReport->setObjectName("RegisterReport");
}

void Dashboard::setFrameProductQuantityAlerts()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mProductQuantityAlerts = new F_ProductQuantityAlerts(this);
    gridLayout->addWidget(mProductQuantityAlerts,1,1,1,1);
    mProductQuantityAlerts->setObjectName("ProductQuantityAlerts");
}

void Dashboard::setFrameProductsReport()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mProductsReport = new F_ProductsReport(this);
    gridLayout->addWidget(mProductsReport,1,1,1,1);
    mProductsReport->setObjectName("ProductsReport");
}

void Dashboard::setFrameAdjutmentsReport()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mAdjutmentsReport = new F_AdjutmentsReport(this);
    gridLayout->addWidget(mAdjutmentsReport,1,1,1,1);
    mAdjutmentsReport->setObjectName("AdjutmentsReport");
}

void Dashboard::setFrameCategoriesReport()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mCategoriesReport = new F_CategoriesReport(this);
    gridLayout->addWidget(mCategoriesReport,1,1,1,1);
    mCategoriesReport->setObjectName("CategoriesReport");
}

void Dashboard::setFrameBandsReport()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mBandsReport = new F_BandsReport(this);
    gridLayout->addWidget(mBandsReport,1,1,1,1);
    mBandsReport->setObjectName("BandsReport");
}

void Dashboard::setFrameDailySales()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mDailySales = new F_DailySales(this);
    gridLayout->addWidget(mDailySales,1,1,1,1);
    mDailySales->setObjectName("DailySales");
}

void Dashboard::setFrameMonthlySales()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mMonthlySales = new F_MonthlySales(this);
    gridLayout->addWidget(mMonthlySales,1,1,1,1);
    mMonthlySales->setObjectName("MonthlySales");
}

void Dashboard::setFrameSalesReport()
{
    // Clear Old Frame
    if(gridLayout->itemAtPosition(1,1) != NULL)
        delete gridLayout->itemAtPosition(1,1)->widget();
    // Place the new One.
    mSalesReport = new F_SalesReport(this);
    gridLayout->addWidget(mSalesReport,1,1,1,1);
    mSalesReport->setObjectName("SalesReport");
}

Dashboard::~Dashboard()
{
    //delete ui;
}
