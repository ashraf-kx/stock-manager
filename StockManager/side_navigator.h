#ifndef SIDE_NAVIGATOR_H
#define SIDE_NAVIGATOR_H

#include <QFrame>
#include <QPushButton>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include <QMouseEvent>
#include "classes.h"

// QAnimate Framework
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QStateMachine>
#include <QState>
#include <QSignalTransition>
#include <QTimer>


namespace Ui {
class Side_navigator;
}

class Side_navigator : public QFrame
{
    Q_OBJECT

public:
    explicit Side_navigator(QWidget *parent = 0);
    ~Side_navigator();

    // Products, Sales, Quotations, Purchases, Transfers, People, Notifications, Settings, Reports.
    void createProductsItems();
    void createSalesItems();
    void createQuotationsItems();
    void createPurchasesItems();
    void createTransfersItems();
    void createPeopleItems();
    void createNotificationsItems();
    void createSettingsItems();
    void createReportsItems();

    void loadStyle();

private:
    Ui::Side_navigator *ui;

    QPushButton *mClickedBtn;
    // Products
    QPushButton *mListProducts;
    QPushButton *mAddProducts;
    QPushButton *mImportProducts;
    QPushButton *mPrintBarcode;
    QPushButton *mQuantityAdjustments;
    QPushButton *mAddAdjustments;
    QPushButton *mStockCounts;
    QPushButton *mCountStock;

    // Sales
    QPushButton *mListSales;
    QPushButton *mPOSSales;
    QPushButton *mAddSale;
    QPushButton *mAddSaleByCSV;
    QPushButton *mDeliveries;
    QPushButton *mListGiftCards;

    // Quotations
    QPushButton *mListQuotations;
    QPushButton *mAddQuotations;

    // Purchases
    QPushButton *mListPurchases;
    QPushButton *mAddPurchase;
    QPushButton *mAddPurchasesByCSV;
    QPushButton *mListExpenses;
    QPushButton *mAddExpense;

    // Transfers
    QPushButton *mListTransfers;
    QPushButton *mAddTransfer;
    QPushButton *mAddTransferByCSV;

    // People
    QPushButton *mListUsers;
    QPushButton *mAddUser;

    QPushButton *mListBillers;
    QPushButton *mAddBiller;

    QPushButton *mListCustomers;
    QPushButton *mAddCustomer;

    QPushButton *mListSuppliers;
    QPushButton *mAddSupplier;

    // Notifications

    // Settings
    QPushButton *mSystemSettings;
    QPushButton *mPOSSettings;
    QPushButton *mListPrinters;
    QPushButton *mAddPrinter;
    QPushButton *mChangeLogo;
    QPushButton *mCurrencies;
    QPushButton *mCustomerGroups;
    QPushButton *mPriceGroups;
    QPushButton *mCategories;
    QPushButton *mExpenseCategories;
    QPushButton *mUnits;
    QPushButton *mBrands;
    QPushButton *mVariants;
    QPushButton *mTaxRates;
    QPushButton *mWarhouses;
    QPushButton *mEmailTemplates;
    QPushButton *mGroupPermissions;
    QPushButton *mBackUps;
    QPushButton *mUpdates;

    // Reports
    QPushButton *mOverViewChart;
    QPushButton *mWarehouseStockChart;
    QPushButton *mBestSellers;
    QPushButton *mRegisterReport;
    QPushButton *mProductQuantityAlerts;
    QPushButton *mProductsReport;
    QPushButton *mAdjutmentsReport;
    QPushButton *mCategoriesReport;
    QPushButton *mBandsReport;
    QPushButton *mDailySales;
    QPushButton *mMonthlySales;
    QPushButton *mSalesReport;

public:
    // Products
    QPushButton* getBtnListProducts();
    QPushButton* getBtnAddProducts();
    QPushButton* getBtnImportProducts();
    QPushButton* getBtnPrintBarcode();
    QPushButton* getBtnQuantityAdjustments();
    QPushButton* getBtnAddAdjustments();
    QPushButton* getBtnStockCounts();
    QPushButton* getBtnCountStock();

    // Sales
    QPushButton* getBtnListSales();
    QPushButton* getBtnPOSSales();
    QPushButton* getBtnAddSale();
    QPushButton* getBtnAddSaleByCSV();
    QPushButton* getBtnDeliveries();
    QPushButton* getBtnListGiftCards();

    // Quotations
    QPushButton* getBtnListQuotations();
    QPushButton* getBtnAddQuotations();

    // Purchases
    QPushButton* getBtnListPurchases();
    QPushButton* getBtnAddPurchase();
    QPushButton* getBtnAddPurchasesByCSV();
    QPushButton* getBtnListExpenses();
    QPushButton* getBtnAddExpense();

    // Transfers
    QPushButton* getBtnListTransfers();
    QPushButton* getBtnAddTransfer();
    QPushButton* getBtnAddTransferByCSV();

    // People
    QPushButton* getBtnListUsers();
    QPushButton* getBtnAddUser();

    QPushButton* getBtnListBillers();
    QPushButton* getBtnAddBiller();

    QPushButton* getBtnListCustomers();
    QPushButton* getBtnAddCustomer();

    QPushButton* getBtnListSuppliers();
    QPushButton* getBtnAddSupplier();

    // Notifications

    // Settings
    QPushButton* getBtnSystemSettings();
    QPushButton* getBtnPOSSettings();
    QPushButton* getBtnListPrinters();
    QPushButton* getBtnAddPrinter();
    QPushButton* getBtnChangeLogo();
    QPushButton* getBtnCurrencies();
    QPushButton* getBtnCustomerGroups();
    QPushButton* getBtnPriceGroups();
    QPushButton* getBtnCategories();
    QPushButton* getBtnExpenseCategories();
    QPushButton* getBtnUnits();
    QPushButton* getBtnBrands();
    QPushButton* getBtnVariants();
    QPushButton* getBtnTaxRates();
    QPushButton* getBtnWarhouses();
    QPushButton* getBtnEmailTemplates();
    QPushButton* getBtnGroupPermissions();
    QPushButton* getBtnBackUps();
    QPushButton* getBtnUpdates();

    // Reports
    QPushButton* getBtnOverViewChart();
    QPushButton* getBtnWarehouseStockChart();
    QPushButton* getBtnBestSellers();
    QPushButton* getBtnRegisterReport();
    QPushButton* getBtnProductQuantityAlerts();
    QPushButton* getBtnProductsReport();
    QPushButton* getBtnAdjutmentsReport();
    QPushButton* getBtnCategoriesReport();
    QPushButton* getBtnBandsReport();
    QPushButton* getBtnDailySales();
    QPushButton* getBtnMonthlySales();
    QPushButton* getBtnSalesReport();

    void slideIn();
    void slideOut();
public slots:
    void ClickSound();
    void visibility();

private:
    QPropertyAnimation *animateSize;
    QSize currentSize;
    bool isToolBoxVisible;
};

#endif // SIDE_NAVIGATOR_H
