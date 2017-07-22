#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QDebug>

//! [ Include our Classes ]
#include "side_navigator.h"
#include "top_navigator.h"
#include "toast.h"

//! [Stupidito ] 310%
// Products
#include "Products/f_ListProducts.h"
#include "Products/f_AddProducts.h"
#include "Products/f_ImportProducts.h"
#include "Products/f_PrintBarcode.h"
#include "Products/f_QuantityAdjustments.h"
#include "Products/f_AddAdjustments.h"
#include "Products/f_StockCounts.h"
#include "Products/f_CountStock.h"

// Sales
#include "Sales/f_ListSales.h"
#include "Sales/f_POSSales.h"
#include "Sales/f_AddSale.h"
#include "Sales/f_AddSaleByCSV.h"
#include "Sales/f_Deliveries.h"
#include "Sales/f_ListGiftCards.h"

// Quotations
#include "Quotations/f_ListQuotations.h"
#include "Quotations/f_AddQuotations.h"

// Purchases
#include "Purchases/f_ListPurchases.h"
#include "Purchases/f_AddPurchase.h"
#include "Purchases/f_AddPurchasesByCSV.h"
#include "Purchases/f_ListExpenses.h"
#include "Purchases/f_AddExpense.h"

// Transfers
#include "Transfers/f_ListTransfers.h"
#include "Transfers/f_AddTransfer.h"
#include "Transfers/f_AddTransferByCSV.h"

// People
#include "People/f_ListUsers.h"
#include "People/f_AddUser.h"

#include "People/f_ListBillers.h"
#include "People/f_AddBiller.h"

#include "People/f_ListCustomers.h"
#include "People/f_AddCustomer.h"

#include "People/f_ListSuppliers.h"
#include "People/f_AddSupplier.h"

// Notifications

// Settings
#include "Settings/f_SystemSettings.h"
#include "Settings/f_POSSettings.h"
#include "Settings/f_ListPrinters.h"
#include "Settings/f_AddPrinter.h"
#include "Settings/f_ChangeLogo.h"
#include "Settings/f_Currencies.h"
#include "Settings/f_CustomerGroups.h"
#include "Settings/f_PriceGroups.h"
#include "Settings/f_Categories.h"
#include "Settings/f_ExpenseCategories.h"
#include "Settings/f_Units.h"
#include "Settings/f_Brands.h"
#include "Settings/f_Variants.h"
#include "Settings/f_TaxRates.h"
#include "Settings/f_Warhouses.h"
#include "Settings/f_EmailTemplates.h"
#include "Settings/f_GroupPermissions.h"
#include "Settings/f_BackUps.h"
#include "Settings/f_Updates.h"

// Reports
#include "Reports/f_OverViewChart.h"
#include "Reports/f_WarehouseStockChart.h"
#include "Reports/f_BestSellers.h"
#include "Reports/f_RegisterReport.h"
#include "Reports/f_ProductQuantityAlerts.h"
#include "Reports/f_ProductsReport.h"
#include "Reports/f_AdjutmentsReport.h"
#include "Reports/f_CategoriesReport.h"
#include "Reports/f_BandsReport.h"
#include "Reports/f_DailySales.h"
#include "Reports/f_MonthlySales.h"
#include "Reports/f_SalesReport.h"

using namespace std;

namespace Ui {
class Dashboard;
}

class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = 0);
    ~Dashboard();

    QString QKStyle(int n);
public slots:
    //! [Stupidito] 100%
    // Products
        void setFrameListProducts();
        void setFrameAddProducts();
        void setFrameImportProducts();
        void setFramePrintBarcode();
        void setFrameQuantityAdjustments();
        void setFrameAddAdjustments();
        void setFrameStockCounts();
        void setFrameCountStock();

        // Sales
        void setFrameListSales();
        void setFramePOSSales();
        void setFrameAddSale();
        void setFrameAddSaleByCSV();
        void setFrameDeliveries();
        void setFrameListGiftCards();

        // Quotations
        void setFrameListQuotations();
        void setFrameAddQuotations();

        // Purchases
        void setFrameListPurchases();
        void setFrameAddPurchase();
        void setFrameAddPurchasesByCSV();
        void setFrameListExpenses();
        void setFrameAddExpense();

        // Transfers
        void setFrameListTransfers();
        void setFrameAddTransfer();
        void setFrameAddTransferByCSV();

        // People
        void setFrameListUsers();
        void setFrameAddUser();

        void setFrameListBillers();
        void setFrameAddBiller();

        void setFrameListCustomers();
        void setFrameAddCustomer();

        void setFrameListSuppliers();
        void setFrameAddSupplier();

        // Notifications

        // Settings
        void setFrameSystemSettings();
        void setFramePOSSettings();
        void setFrameListPrinters();
        void setFrameAddPrinter();
        void setFrameChangeLogo();
        void setFrameCurrencies();
        void setFrameCustomerGroups();
        void setFramePriceGroups();
        void setFrameCategories();
        void setFrameExpenseCategories();
        void setFrameUnits();
        void setFrameBrands();
        void setFrameVariants();
        void setFrameTaxRates();
        void setFrameWarhouses();
        void setFrameEmailTemplates();
        void setFrameGroupPermissions();
        void setFrameBackUps();
        void setFrameUpdates();

        // Reports
        void setFrameOverViewChart();
        void setFrameWarehouseStockChart();
        void setFrameBestSellers();
        void setFrameRegisterReport();
        void setFrameProductQuantityAlerts();
        void setFrameProductsReport();
        void setFrameAdjutmentsReport();
        void setFrameCategoriesReport();
        void setFrameBandsReport();
        void setFrameDailySales();
        void setFrameMonthlySales();
        void setFrameSalesReport();
private:
    Ui::Dashboard *ui;

    Side_navigator *mSideNAV;
    Top_navigator  *mTopNav;



    //! [Stupidito] 300%

    // Products
    F_ListProducts *mListProducts;
    F_AddProducts *mAddProducts;
    F_ImportProducts *mImportProducts;
    F_PrintBarcode *mPrintBarcode;
    F_QuantityAdjustments *mQuantityAdjustments;
    F_AddAdjustments *mAddAdjustments;
    F_StockCounts *mStockCounts;
    F_CountStock *mCountStock;

    // Sales
    F_ListSales *mListSales;
    F_POSSales *mPOSSales;
    F_AddSale *mAddSale;
    F_AddSaleByCSV *mAddSaleByCSV;
    F_Deliveries *mDeliveries;
    F_ListGiftCards *mListGiftCards;

    // Quotations
    F_ListQuotations *mListQuotations;
    F_AddQuotations *mAddQuotations;

    // Purchases
    F_ListPurchases *mListPurchases;
    F_AddPurchase *mAddPurchase;
    F_AddPurchasesByCSV *mAddPurchasesByCSV;
    F_ListExpenses *mListExpenses;
    F_AddExpense *mAddExpense;

    // Transfers
    F_ListTransfers *mListTransfers;
    F_AddTransfer *mAddTransfer;
    F_AddTransferByCSV *mAddTransferByCSV;

    // People
    F_ListUsers *mListUsers;
    F_AddUser *mAddUser;

    F_ListBillers *mListBillers;
    F_AddBiller *mAddBiller;

    F_ListCustomers *mListCustomers;
    F_AddCustomer *mAddCustomer;

    F_ListSuppliers *mListSuppliers;
    F_AddSupplier *mAddSupplier;

    // Notifications

    // Settings
    F_SystemSettings *mSystemSettings;
    F_POSSettings *mPOSSettings;
    F_ListPrinters *mListPrinters;
    F_AddPrinter *mAddPrinter;
    F_ChangeLogo *mChangeLogo;
    F_Currencies *mCurrencies;
    F_CustomerGroups *mCustomerGroups;
    F_PriceGroups *mPriceGroups;
    F_Categories *mCategories;
    F_ExpenseCategories *mExpenseCategories;
    F_Units *mUnits;
    F_Brands *mBrands;
    F_Variants *mVariants;
    F_TaxRates *mTaxRates;
    F_Warhouses *mWarhouses;
    F_EmailTemplates *mEmailTemplates;
    F_GroupPermissions *mGroupPermissions;
    F_BackUps *mBackUps;
    F_Updates *mUpdates;

    // Reports
    F_OverViewChart *mOverViewChart;
    F_WarehouseStockChart *mWarehouseStockChart;
    F_BestSellers *mBestSellers;
    F_RegisterReport *mRegisterReport;
    F_ProductQuantityAlerts *mProductQuantityAlerts;
    F_ProductsReport *mProductsReport;
    F_AdjutmentsReport *mAdjutmentsReport;
    F_CategoriesReport *mCategoriesReport;
    F_BandsReport *mBandsReport;
    F_DailySales *mDailySales;
    F_MonthlySales *mMonthlySales;
    F_SalesReport *mSalesReport;
};

#endif // DASHBOARD_H
