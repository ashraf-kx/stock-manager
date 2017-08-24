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
#include "classes.h"

//! [Stupidito ] 310%
// Products
#include "Products/f_listproducts.h"
#include "Products/f_addproducts.h"
#include "Products/f_importproducts.h"
#include "Products/f_printbarcode.h"
#include "Products/f_quantityadjustments.h"
#include "Products/f_addadjustments.h"
#include "Products/f_stockcounts.h"
#include "Products/f_countstock.h"

// Sales
#include "Sales/f_listsales.h"
#include "Sales/f_possales.h"
#include "Sales/f_addsale.h"
#include "Sales/f_addsalebycsv.h"
#include "Sales/f_deliveries.h"
#include "Sales/f_listgiftcards.h"

// Quotations
#include "Quotations/f_listquotations.h"
#include "Quotations/f_addquotations.h"

// Purchases
#include "Purchases/f_listpurchases.h"
#include "Purchases/f_addpurchase.h"
#include "Purchases/f_addpurchasesbycsv.h"
#include "Purchases/f_listexpenses.h"
#include "Purchases/f_addexpense.h"

// Transfers
#include "Transfers/f_listtransfers.h"
#include "Transfers/f_addtransfer.h"
#include "Transfers/f_addtransferbycsv.h"

// People
#include "People/f_listusers.h"
#include "People/f_adduser.h"

#include "People/f_listbillers.h"
#include "People/f_addbiller.h"

#include "People/f_listcustomers.h"
#include "People/f_addcustomer.h"

#include "People/f_listsuppliers.h"
#include "People/f_addsupplier.h"

// Notifications

// Settings
#include "Settings/f_systemsettings.h"
#include "Settings/f_possettings.h"
#include "Settings/f_listprinters.h"
#include "Settings/f_addprinter.h"
#include "Settings/f_changelogo.h"
#include "Settings/f_currencies.h"
#include "Settings/f_customergroups.h"
#include "Settings/f_pricegroups.h"
#include "Settings/f_categories.h"
#include "Settings/f_expensecategories.h"
#include "Settings/f_units.h"
#include "Settings/f_brands.h"
#include "Settings/f_variants.h"
#include "Settings/f_taxrates.h"
#include "Settings/f_warhouses.h"
#include "Settings/f_emailtemplates.h"
#include "Settings/f_grouppermissions.h"
#include "Settings/f_backups.h"
#include "Settings/f_updates.h"

// Reports
#include "Reports/f_overviewchart.h"
#include "Reports/f_warehousestockchart.h"
#include "Reports/f_bestsellers.h"
#include "Reports/f_registerreport.h"
#include "Reports/f_productquantityalerts.h"
#include "Reports/f_productsreport.h"
#include "Reports/f_adjutmentsreport.h"
#include "Reports/f_categoriesreport.h"
#include "Reports/f_bandsreport.h"
#include "Reports/f_dailysales.h"
#include "Reports/f_monthlysales.h"
#include "Reports/f_salesreport.h"

#include "ui_dashboard.h"
using namespace std;

namespace Ui {
class Dashboard;
}

class Dashboard : public QMainWindow, private Ui::Dashboard
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = 0);
    ~Dashboard();

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
