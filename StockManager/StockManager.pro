#-------------------------------------------------
#
# Project created by QtCreator 2017-07-15T10:54:01
#
#-------------------------------------------------

QT       += core gui sql multimedia

CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StockManager
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../MDLineEditPlugin/mdlineedit.pri)
include(../camera/camera.pri)

SOURCES += main.cpp\
        dashboard.cpp \
    toast.cpp \
    top_navigator.cpp \
    side_navigator.cpp \
    Products/f_addproducts.cpp \
    Settings/f_units.cpp \
    Products/f_listproducts.cpp \
    Products/f_importproducts.cpp \
    Products/f_printbarcode.cpp \
    Products/f_quantityadjustments.cpp \
    Products/f_addadjustments.cpp \
    Products/f_stockcounts.cpp \
    Products/f_countstock.cpp \
    Sales/f_listsales.cpp \
    Sales/f_possales.cpp \
    Sales/f_addsale.cpp \
    Sales/f_addsalebycsv.cpp \
    Sales/f_deliveries.cpp \
    Sales/f_listgiftcards.cpp \
    Settings/f_systemsettings.cpp \
    Settings/f_possettings.cpp \
    Settings/f_listprinters.cpp \
    Settings/f_addprinter.cpp \
    Settings/f_changelogo.cpp \
    Settings/f_currencies.cpp \
    Settings/f_customergroups.cpp \
    Settings/f_pricegroups.cpp \
    Settings/f_categories.cpp \
    Settings/f_expensecategories.cpp \
    Settings/f_brands.cpp \
    Settings/f_variants.cpp \
    Settings/f_taxrates.cpp \
    Settings/f_warhouses.cpp \
    Settings/f_emailtemplates.cpp \
    Settings/f_grouppermissions.cpp \
    Settings/f_backups.cpp \
    Settings/f_updates.cpp \
    People/f_listusers.cpp \
    People/f_adduser.cpp \
    People/f_listbillers.cpp \
    People/f_addbiller.cpp \
    People/f_listcustomers.cpp \
    People/f_addcustomer.cpp \
    People/f_listsuppliers.cpp \
    Quotations/f_listquotations.cpp \
    Quotations/f_addquotations.cpp \
    Purchases/f_listpurchases.cpp \
    Purchases/f_addpurchase.cpp \
    Purchases/f_addpurchasesbycsv.cpp \
    Purchases/f_listexpenses.cpp \
    Purchases/f_addexpense.cpp \
    Transfers/f_listtransfers.cpp \
    Transfers/f_addtransfer.cpp \
    Transfers/f_addtransferbycsv.cpp \
    Reports/f_overviewchart.cpp \
    Reports/f_warehousestockchart.cpp \
    Reports/f_bestsellers.cpp \
    Reports/f_registerreport.cpp \
    Reports/f_productquantityalerts.cpp \
    Reports/f_productsreport.cpp \
    Reports/f_adjutmentsreport.cpp \
    Reports/f_categoriesreport.cpp \
    Reports/f_bandsreport.cpp \
    Reports/f_dailysales.cpp \
    Reports/f_monthlysales.cpp \
    Reports/f_salesreport.cpp \
    People/f_addsupplier.cpp \
    dialog.cpp \
    dbh.cpp \
    mdialog.cpp

HEADERS  += dashboard.h \
    toast.h \
    top_navigator.h \
    side_navigator.h \
    Settings/f_units.h \
    Products/f_listproducts.h \
    Products/f_importproducts.h \
    Products/f_printbarcode.h \
    Products/f_quantityadjustments.h \
    Products/f_addadjustments.h \
    Products/f_stockcounts.h \
    Products/f_countstock.h \
    Products/f_addproducts.h \
    Sales/f_listsales.h \
    Sales/f_possales.h \
    Sales/f_addsale.h \
    Sales/f_addsalebycsv.h \
    Sales/f_deliveries.h \
    Sales/f_listgiftcards.h \
    Settings/f_systemsettings.h \
    Settings/f_possettings.h \
    Settings/f_listprinters.h \
    Settings/f_addprinter.h \
    Settings/f_changelogo.h \
    Settings/f_currencies.h \
    Settings/f_customergroups.h \
    Settings/f_pricegroups.h \
    Settings/f_categories.h \
    Settings/f_expensecategories.h \
    Settings/f_brands.h \
    Settings/f_variants.h \
    Settings/f_taxrates.h \
    Settings/f_warhouses.h \
    Settings/f_emailtemplates.h \
    Settings/f_grouppermissions.h \
    Settings/f_backups.h \
    Settings/f_updates.h \
    People/f_listusers.h \
    People/f_adduser.h \
    People/f_listbillers.h \
    People/f_addbiller.h \
    People/f_listcustomers.h \
    People/f_addcustomer.h \
    People/f_listsuppliers.h \
    Quotations/f_listquotations.h \
    Quotations/f_addquotations.h \
    Purchases/f_listpurchases.h \
    Purchases/f_addpurchase.h \
    Purchases/f_addpurchasesbycsv.h \
    Purchases/f_listexpenses.h \
    Purchases/f_addexpense.h \
    Transfers/f_listtransfers.h \
    Transfers/f_addtransfer.h \
    Transfers/f_addtransferbycsv.h \
    Reports/f_overviewchart.h \
    Reports/f_warehousestockchart.h \
    Reports/f_bestsellers.h \
    Reports/f_registerreport.h \
    Reports/f_productquantityalerts.h \
    Reports/f_productsreport.h \
    Reports/f_adjutmentsreport.h \
    Reports/f_categoriesreport.h \
    Reports/f_bandsreport.h \
    Reports/f_dailysales.h \
    Reports/f_monthlysales.h \
    Reports/f_salesreport.h \
    classes.h \
    People/f_addsupplier.h \
    dialog.h \
    dbh.h \
    mdialog.h

FORMS    += dashboard.ui \
    toast.ui \
    top_navigator.ui \
    side_navigator.ui \
    Products/f_addproducts.ui \
    Settings/f_units.ui \
    Products/f_listproducts.ui \
    Products/f_importproducts.ui \
    Products/f_printbarcode.ui \
    Products/f_quantityadjustments.ui \
    Products/f_addadjustments.ui \
    Products/f_stockcounts.ui \
    Products/f_countstock.ui \
    Sales/f_listsales.ui \
    Sales/f_possales.ui \
    Sales/f_addsale.ui \
    Sales/f_addsalebycsv.ui \
    Sales/f_deliveries.ui \
    Sales/f_listgiftcards.ui \
    Settings/f_systemsettings.ui \
    Settings/f_possettings.ui \
    Settings/f_listprinters.ui \
    Settings/f_addprinter.ui \
    Settings/f_changelogo.ui \
    Settings/f_currencies.ui \
    Settings/f_customergroups.ui \
    Settings/f_pricegroups.ui \
    Settings/f_categories.ui \
    Settings/f_expensecategories.ui \
    Settings/f_brands.ui \
    Settings/f_variants.ui \
    Settings/f_taxrates.ui \
    Settings/f_warhouses.ui \
    Settings/f_emailtemplates.ui \
    Settings/f_grouppermissions.ui \
    Settings/f_backups.ui \
    Settings/f_updates.ui \
    People/f_listusers.ui \
    People/f_adduser.ui \
    People/f_listbillers.ui \
    People/f_addbiller.ui \
    People/f_listcustomers.ui \
    People/f_addcustomer.ui \
    People/f_listsuppliers.ui \
    Quotations/f_listquotations.ui \
    Quotations/f_addquotations.ui \
    Purchases/f_listpurchases.ui \
    Purchases/f_addpurchase.ui \
    Purchases/f_addpurchasesbycsv.ui \
    Purchases/f_listexpenses.ui \
    Purchases/f_addexpense.ui \
    Transfers/f_listtransfers.ui \
    Transfers/f_addtransfer.ui \
    Transfers/f_addtransferbycsv.ui \
    Reports/f_overviewchart.ui \
    Reports/f_warehousestockchart.ui \
    Reports/f_bestsellers.ui \
    Reports/f_registerreport.ui \
    Reports/f_productquantityalerts.ui \
    Reports/f_productsreport.ui \
    Reports/f_adjutmentsreport.ui \
    Reports/f_categoriesreport.ui \
    Reports/f_bandsreport.ui \
    Reports/f_dailysales.ui \
    Reports/f_monthlysales.ui \
    Reports/f_salesreport.ui \
    People/f_addsupplier.ui \
    dialog.ui \
    mdialog.ui


RESOURCES += \
    icons.qrc \
    styles.qrc \
    languages.qrc \
    sounds.qrc

TRANSLATIONS = languages/StockManager_ar.ts \
               languages/StockManager_fr.ts \
               languages/StockManager_en.ts

DISTFILES += \
#    StockManager_ar.ts \
#    StockManager_ar.qm \
    SM_Loggoer.ini



##### Using MySql Connector C++  #####################
#win32:CONFIG(release, debug|release): LIBS += -L'D:/MySql ConnectorC++/lib/opt/' -lmysqlcppconn
#else:win32:CONFIG(debug, debug|release): LIBS += -L'D:/MySql ConnectorC++/lib/opt/' -lmysqlcppconnd

#INCLUDEPATH += 'D:/MySql ConnectorC++/include'
