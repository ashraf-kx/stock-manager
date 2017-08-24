#include "side_navigator.h"
#include "ui_side_navigator.h"

#include <QtMultimedia/QSound>

Side_navigator::Side_navigator(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Side_navigator)
{
    ui->setupUi(this);
    isToolBoxVisible = true;

    this->setStyleSheet(Style::loadStyle("SideNavigator"));


    QGraphicsDropShadowEffect *sh = new QGraphicsDropShadowEffect();
    sh->setBlurRadius(8);
    sh->setOffset(2);
    sh->setColor(QColor(63, 63, 63, 180));
    this->setGraphicsEffect(sh);

    createProductsItems();
    createSalesItems();
    createQuotationsItems();
    createPurchasesItems();
    createTransfersItems();
    createPeopleItems();
    createNotificationsItems();
    createSettingsItems();
    createReportsItems();

    this->setMouseTracking(true);

    // Products
    connect(mListProducts,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mAddProducts,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mImportProducts,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mPrintBarcode,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mQuantityAdjustments,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mAddAdjustments,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mStockCounts,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mCountStock,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));

        // Sales
    connect(mListSales,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mPOSSales,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mAddSale,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mAddSaleByCSV,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mDeliveries,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mListGiftCards,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));

        // Quotations
    connect(mListQuotations,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mAddQuotations,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));

        // Purchases
    connect(mListPurchases,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mAddPurchase,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mAddPurchasesByCSV,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mListExpenses,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mAddExpense,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));

        // Transfers
    connect(mListTransfers,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mAddTransfer,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mAddTransferByCSV,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));

        // People
    connect(mListUsers,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mAddUser,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));

    connect(mListBillers,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mAddBiller,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));

    connect(mListCustomers,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mAddCustomer,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));

    connect(mListSuppliers,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mAddSupplier,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));

        // Notifications

        // Settings
    connect(mSystemSettings,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mPOSSettings,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mListPrinters,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mAddPrinter,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mChangeLogo,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mCurrencies,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mCustomerGroups,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mPriceGroups,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mCategories,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mExpenseCategories,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mUnits,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mBrands,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mVariants,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mTaxRates,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mWarhouses,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mEmailTemplates,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mGroupPermissions,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mBackUps,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mUpdates,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));

        // Reports
    connect(mOverViewChart,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mWarehouseStockChart,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mBestSellers,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mRegisterReport,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mProductQuantityAlerts,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mProductsReport,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mAdjutmentsReport,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mCategoriesReport,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mBandsReport,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mDailySales,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mMonthlySales,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));
    connect(mSalesReport,SIGNAL(clicked(bool)),this,SLOT(ClickSound()));

    currentSize = this->size();
}

Side_navigator::~Side_navigator()
{
    delete ui;
}

void Side_navigator::visibility()
{
    if(isToolBoxVisible)
        isToolBoxVisible = false;
    else
        isToolBoxVisible = true;

    if(isToolBoxVisible)
        slideIn();
    else
        slideOut();
}

//! [ Animation Come In Come out ]
void Side_navigator::slideIn() // <+++++++>
{
    this->show();
    animateSize = new QPropertyAnimation(this, "size");
    animateSize->setDuration(200);
    animateSize->setStartValue(QSize(0,currentSize.height()));
    animateSize->setEndValue(currentSize);
    animateSize->setEasingCurve(QEasingCurve::OutSine);
    animateSize->start();
    //QTimer::singleShot(200, this, SLOT(show()));
}

void Side_navigator::slideOut() // ---->++<-----
{
    currentSize = this->size();
    animateSize = new QPropertyAnimation(this, "size");
    animateSize->setDuration(200);
    animateSize->setStartValue(currentSize);
    animateSize->setEndValue(QSize(0,currentSize.height()));
    animateSize->setEasingCurve(QEasingCurve::InSine);
    animateSize->start();
    QTimer::singleShot(200, this, SLOT(hide()));
}

void Side_navigator::ClickSound()
{
    QSound::play("://sounds/click_04.wav");
}

void Side_navigator::createProductsItems()
{
    mListProducts  = new QPushButton(tr("List products"));
    mListProducts->setIcon(QIcon(":/w/icons/w/ic_view_list_white_2x.png"));

    mAddProducts   = new QPushButton(tr("Add Products"));
    mAddProducts->setIcon(QIcon(":/w/icons/w/ic_add_circle_outline_white_2x.png"));

    mImportProducts= new QPushButton(tr("Import Products"));
    mPrintBarcode  = new QPushButton(tr("Print Barcode/Label"));
    mQuantityAdjustments = new QPushButton(tr("Quantity Adjustments"));
    mAddAdjustments      = new QPushButton(tr("Add Adjustments"));
    mStockCounts         = new QPushButton(tr("Stock Counts"));
    mCountStock          = new QPushButton(tr("Count Stock"));

    ui->layoutProductsItems->addWidget(mListProducts);
    ui->layoutProductsItems->addWidget(mAddProducts);
    ui->layoutProductsItems->addWidget(mImportProducts);
    ui->layoutProductsItems->addWidget(mPrintBarcode);
    ui->layoutProductsItems->addWidget(mQuantityAdjustments);
    ui->layoutProductsItems->addWidget(mAddAdjustments);
    ui->layoutProductsItems->addWidget(mStockCounts);
    ui->layoutProductsItems->addWidget(mCountStock);
}

void Side_navigator::createSalesItems()
{
    mListSales   = new QPushButton(tr("List Sales"));
    mListSales->setIcon(QIcon("://icons/18x18/ic_format_list_bulleted_white_18dp.png"));
    mPOSSales    = new QPushButton(tr("POS Sales"));

    mAddSale    = new QPushButton(tr("Add Sales"));
    mAddSaleByCSV = new QPushButton(tr("Add Sales by CSV"));
    mDeliveries    = new QPushButton(tr("Deliveries"));
    mListGiftCards = new QPushButton(tr("List Gift Cards"));

    ui->layoutSalesItems->addWidget(mListSales);
    ui->layoutSalesItems->addWidget(mPOSSales);
    ui->layoutSalesItems->addWidget(mAddSale);
    ui->layoutSalesItems->addWidget(mAddSaleByCSV);
    ui->layoutSalesItems->addWidget(mDeliveries);
    ui->layoutSalesItems->addWidget(mListGiftCards);
}

void Side_navigator::createQuotationsItems()
{
    mListQuotations  = new QPushButton(tr("List Quotations"));
    mAddQuotations   = new QPushButton(tr("Add Quotations"));

    ui->layoutQuotationsItems->addWidget(mListQuotations);
    ui->layoutQuotationsItems->addWidget(mAddQuotations);
}

void Side_navigator::createPurchasesItems()
{
     mListPurchases  = new QPushButton(tr("List Purchases"));
     mListPurchases->setIcon(QIcon("://icons/18x18/ic_format_list_bulleted_white_18dp.png"));
     mAddPurchase    = new QPushButton(tr("Add Purchase"));
     mAddPurchasesByCSV = new QPushButton(tr("Add Purchases by CSV"));
     mListExpenses   = new QPushButton(tr("List Expenses"));
     mAddExpense     = new QPushButton(tr("Add Expense"));

     ui->layoutPurchasesItems->addWidget(mListPurchases);
     ui->layoutPurchasesItems->addWidget(mAddPurchase);
     ui->layoutPurchasesItems->addWidget(mAddPurchasesByCSV);
     ui->layoutPurchasesItems->addWidget(mListExpenses);
     ui->layoutPurchasesItems->addWidget(mAddExpense);
}

void Side_navigator::createTransfersItems()
{
    mListTransfers    = new QPushButton(tr("List Transfers"));
    mListTransfers->setIcon(QIcon("://icons/18x18/ic_format_list_bulleted_white_18dp.png"));
    mAddTransfer      = new QPushButton(tr("Add Transfer"));
    mAddTransferByCSV = new QPushButton(tr("Add Transfer by CSV"));

    ui->layoutTransfersItems->addWidget(mListTransfers);
    ui->layoutTransfersItems->addWidget(mAddTransfer);
    ui->layoutTransfersItems->addWidget(mAddTransferByCSV);
}

void Side_navigator::createPeopleItems()
{
    mListUsers = new QPushButton(tr("List Users"));
    mListUsers->setIcon(QIcon(":/w/icons/w/ic_view_list_white_2x.png"));
    mAddUser = new QPushButton(tr("Add User"));
    mAddUser->setIcon(QIcon(":/w/icons/w/ic_person_add_white_2x.png"));

    mListBillers = new QPushButton(tr("List Billers"));
    mListBillers->setIcon(QIcon(":/w/icons/w/ic_view_list_white_2x.png"));
    mAddBiller = new QPushButton(tr("Add Biller"));
    mAddBiller->setIcon(QIcon(":/w/icons/w/ic_person_add_white_2x.png"));

    mListCustomers = new QPushButton(tr("List Customers"));
    mListCustomers->setIcon(QIcon(":/w/icons/w/ic_view_list_white_2x.png"));
    mAddCustomer = new QPushButton(tr("Add Customer"));
    mAddCustomer->setIcon(QIcon(":/w/icons/w/ic_person_add_white_2x.png"));

    mListSuppliers = new QPushButton(tr("List Suppliers"));
    mListSuppliers->setIcon(QIcon(":/w/icons/w/ic_view_list_white_2x.png"));
    mAddSupplier = new QPushButton(tr("Add Supplier"));
    mAddSupplier->setIcon(QIcon(":/w/icons/w/ic_person_add_white_2x.png"));

    ui->layoutPeopleItems->addWidget(mListUsers);
    ui->layoutPeopleItems->addWidget(mAddUser);

    ui->layoutPeopleItems->addWidget(mListBillers);
    ui->layoutPeopleItems->addWidget(mAddBiller);

    ui->layoutPeopleItems->addWidget(mListCustomers);
    ui->layoutPeopleItems->addWidget(mAddCustomer);

    ui->layoutPeopleItems->addWidget(mListSuppliers);
    ui->layoutPeopleItems->addWidget(mAddSupplier);
}

void Side_navigator::createNotificationsItems()
{
    // Notifications
}

void Side_navigator::createSettingsItems()
{
    mSystemSettings = new QPushButton(tr("System Settings"));
    mPOSSettings = new QPushButton(tr("POS Settings"));
    mListPrinters = new QPushButton(tr("List Printers"));
    mListPrinters->setIcon(QIcon("://icons/18x18/ic_format_list_bulleted_white_18dp.png"));
    mAddPrinter = new QPushButton(tr("Add Printer"));
    mChangeLogo = new QPushButton(tr("Change Logo"));
    mCurrencies = new QPushButton(tr("Currencies"));
    mCustomerGroups = new QPushButton(tr("Customer Groups"));
    mPriceGroups = new QPushButton(tr("Price Groups"));
    mCategories = new QPushButton(tr("Categories"));
    mExpenseCategories = new QPushButton(tr("Expense Categories"));
    mUnits = new QPushButton(tr("Units"));
    mBrands = new QPushButton(tr("Brands"));
    mVariants = new QPushButton(tr("Variants"));
    mTaxRates = new QPushButton(tr("Tax Rates"));
    mWarhouses = new QPushButton(tr("Warhouses"));
    mEmailTemplates = new QPushButton(tr("Email Templates"));
    mGroupPermissions = new QPushButton(tr("Group Permissions"));
    mBackUps = new QPushButton(tr("BackUps"));
    mUpdates = new QPushButton(tr("Updates"));

    ui->layoutSettingsItems->addWidget(mSystemSettings);
    ui->layoutSettingsItems->addWidget(mPOSSettings);
    ui->layoutSettingsItems->addWidget(mListPrinters);
    ui->layoutSettingsItems->addWidget(mAddPrinter);
    ui->layoutSettingsItems->addWidget(mChangeLogo);
    ui->layoutSettingsItems->addWidget(mCurrencies);
    ui->layoutSettingsItems->addWidget(mCustomerGroups);
    ui->layoutSettingsItems->addWidget(mPriceGroups);
    ui->layoutSettingsItems->addWidget(mCategories);
    ui->layoutSettingsItems->addWidget(mExpenseCategories);
    ui->layoutSettingsItems->addWidget(mUnits);
    ui->layoutSettingsItems->addWidget(mBrands);
    ui->layoutSettingsItems->addWidget(mVariants);
    ui->layoutSettingsItems->addWidget(mTaxRates);
    ui->layoutSettingsItems->addWidget(mWarhouses);
    ui->layoutSettingsItems->addWidget(mEmailTemplates);
    ui->layoutSettingsItems->addWidget(mGroupPermissions);
    ui->layoutSettingsItems->addWidget(mBackUps);
    ui->layoutSettingsItems->addWidget(mUpdates);
}

void Side_navigator::createReportsItems()
{
    mOverViewChart = new QPushButton(tr("Overview Chart"));
    mWarehouseStockChart = new QPushButton(tr("Warehouse Stock Chart"));
    mBestSellers = new QPushButton(tr("Best Sellers"));
    mRegisterReport = new QPushButton(tr("Register Report"));
    mProductQuantityAlerts = new QPushButton(tr("Product Quantity Alerts"));
    mProductsReport = new QPushButton(tr("Products Report"));
    mAdjutmentsReport = new QPushButton(tr("Adjutments Report"));
    mCategoriesReport = new QPushButton(tr("Categories Report"));
    mBandsReport = new QPushButton(tr("Bands Report"));
    mDailySales = new QPushButton(tr("Daily Sales"));
    mMonthlySales = new QPushButton(tr("Monthly Sales"));
    mSalesReport = new QPushButton(tr("Sales Report"));

    ui->layoutReportsItems->addWidget(mOverViewChart);
    ui->layoutReportsItems->addWidget(mWarehouseStockChart);
    ui->layoutReportsItems->addWidget(mBestSellers);
    ui->layoutReportsItems->addWidget(mRegisterReport);
    ui->layoutReportsItems->addWidget(mProductQuantityAlerts);
    ui->layoutReportsItems->addWidget(mProductsReport);
    ui->layoutReportsItems->addWidget(mAdjutmentsReport);
    ui->layoutReportsItems->addWidget(mCategoriesReport);
    ui->layoutReportsItems->addWidget(mBandsReport);
    ui->layoutReportsItems->addWidget(mDailySales);
    ui->layoutReportsItems->addWidget(mMonthlySales);
    ui->layoutReportsItems->addWidget(mSalesReport);
}

//! [ LOL ;) ]
// Products
QPushButton* Side_navigator::getBtnListProducts()
{
    return mListProducts;
}

QPushButton* Side_navigator::getBtnAddProducts()
{
    return mAddProducts;
}

QPushButton* Side_navigator::getBtnImportProducts()
{
    return mImportProducts;
}

QPushButton* Side_navigator::getBtnPrintBarcode()
{
    return mPrintBarcode;
}

QPushButton* Side_navigator::getBtnQuantityAdjustments()
{
    return mQuantityAdjustments;
}

QPushButton* Side_navigator::getBtnAddAdjustments()
{
    return mAddAdjustments;
}

QPushButton* Side_navigator::getBtnStockCounts()
{
    return mStockCounts;
}

QPushButton* Side_navigator::getBtnCountStock()
{
    return mCountStock;
}


// Sales
QPushButton* Side_navigator::getBtnListSales()
{
    return mListSales;
}

QPushButton* Side_navigator::getBtnPOSSales()
{
    return mPOSSales;
}

QPushButton* Side_navigator::getBtnAddSale()
{
    return mAddSale;
}

QPushButton* Side_navigator::getBtnAddSaleByCSV()
{
    return mAddSaleByCSV;
}

QPushButton* Side_navigator::getBtnDeliveries()
{
    return mDeliveries;
}

QPushButton* Side_navigator::getBtnListGiftCards()
{
    return mListGiftCards;
}


// Quotations
QPushButton* Side_navigator::getBtnListQuotations()
{
    return mListQuotations;
}

QPushButton* Side_navigator::getBtnAddQuotations()
{
    return mAddQuotations;
}


// Purchases
QPushButton* Side_navigator::getBtnListPurchases()
{
    return mListPurchases;
}

QPushButton* Side_navigator::getBtnAddPurchase()
{
    return mAddPurchase;
}

QPushButton* Side_navigator::getBtnAddPurchasesByCSV()
{
    return mAddPurchasesByCSV;
}

QPushButton* Side_navigator::getBtnListExpenses()
{
    return mListExpenses;
}

QPushButton* Side_navigator::getBtnAddExpense()
{
    return mAddExpense;
}


// Transfers
QPushButton* Side_navigator::getBtnListTransfers()
{
    return mListTransfers;
}

QPushButton* Side_navigator::getBtnAddTransfer()
{
    return mAddTransfer;
}

QPushButton* Side_navigator::getBtnAddTransferByCSV()
{
    return mAddTransferByCSV;
}


// People
QPushButton* Side_navigator::getBtnListUsers()
{
    return mListUsers;
}

QPushButton* Side_navigator::getBtnAddUser()
{
    return mAddUser;
}


QPushButton* Side_navigator::getBtnListBillers()
{
    return mListBillers;
}

QPushButton* Side_navigator::getBtnAddBiller()
{
    return mAddBiller;
}


QPushButton* Side_navigator::getBtnListCustomers()
{
    return mListCustomers;
}

QPushButton* Side_navigator::getBtnAddCustomer()
{
    return mAddCustomer;
}


QPushButton* Side_navigator::getBtnListSuppliers()
{
    return mListSuppliers;
}

QPushButton* Side_navigator::getBtnAddSupplier()
{
    return mAddSupplier;
}


// Notifications

// Settings
QPushButton* Side_navigator::getBtnSystemSettings()
{
    return mSystemSettings;
}

QPushButton* Side_navigator::getBtnPOSSettings()
{
    return mPOSSettings;
}

QPushButton* Side_navigator::getBtnListPrinters()
{
    return mListPrinters;
}

QPushButton* Side_navigator::getBtnAddPrinter()
{
    return mAddPrinter;
}

QPushButton* Side_navigator::getBtnChangeLogo()
{
    return mChangeLogo;
}

QPushButton* Side_navigator::getBtnCurrencies()
{
    return mCurrencies;
}

QPushButton* Side_navigator::getBtnCustomerGroups()
{
    return mCustomerGroups;
}

QPushButton* Side_navigator::getBtnPriceGroups()
{
    return mPriceGroups;
}

QPushButton* Side_navigator::getBtnCategories()
{
    return mCategories;
}

QPushButton* Side_navigator::getBtnExpenseCategories()
{
    return mExpenseCategories;
}

QPushButton* Side_navigator::getBtnUnits()
{
    return mUnits;
}

QPushButton* Side_navigator::getBtnBrands()
{
    return mBrands;
}

QPushButton* Side_navigator::getBtnVariants()
{
    return mVariants;
}

QPushButton* Side_navigator::getBtnTaxRates()
{
    return mTaxRates;
}

QPushButton* Side_navigator::getBtnWarhouses()
{
    return mWarhouses;
}

QPushButton* Side_navigator::getBtnEmailTemplates()
{
    return mEmailTemplates;
}

QPushButton* Side_navigator::getBtnGroupPermissions()
{
    return mGroupPermissions;
}

QPushButton* Side_navigator::getBtnBackUps()
{
    return mBackUps;
}

QPushButton* Side_navigator::getBtnUpdates()
{
    return mUpdates;
}


// Reports
QPushButton* Side_navigator::getBtnOverViewChart()
{
    return mOverViewChart;
}

QPushButton* Side_navigator::getBtnWarehouseStockChart()
{
    return mWarehouseStockChart;
}

QPushButton* Side_navigator::getBtnBestSellers()
{
    return mBestSellers;
}

QPushButton* Side_navigator::getBtnRegisterReport()
{
    return mRegisterReport;
}

QPushButton* Side_navigator::getBtnProductQuantityAlerts()
{
    return mProductQuantityAlerts;
}

QPushButton* Side_navigator::getBtnProductsReport()
{
    return mProductsReport;
}

QPushButton* Side_navigator::getBtnAdjutmentsReport()
{
    return mAdjutmentsReport;
}

QPushButton* Side_navigator::getBtnCategoriesReport()
{
    return mCategoriesReport;
}

QPushButton* Side_navigator::getBtnBandsReport()
{
    return mBandsReport;
}

QPushButton* Side_navigator::getBtnDailySales()
{
    return mDailySales;
}

QPushButton* Side_navigator::getBtnMonthlySales()
{
    return mMonthlySales;
}

QPushButton* Side_navigator::getBtnSalesReport()
{
    return mSalesReport;
}

