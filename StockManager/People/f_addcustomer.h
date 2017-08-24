#ifndef F_ADDCUSTOMER_H
#define F_ADDCUSTOMER_H

#include <QFrame>
#include "../classes.h"
#include "ui_f_addcustomer.h"

Q_DECLARE_LOGGING_CATEGORY(LC_XDCus)

namespace Ui {
class F_AddCustomer;
}

class F_AddCustomer : public QFrame, private Ui::F_AddCustomer
{
    Q_OBJECT

public:
    explicit F_AddCustomer(QWidget *parent = 0);
    ~F_AddCustomer();

public slots:
    void addCustomer();
    bool checkEmail(const QString & email);

    void initCompanyCombo();
    void initCountryCombo();

    void updateCityStateCompleters();
    void updatePostalCodeLEdit();

    void clearInputs();
    bool inputsVerification();

    bool checkCompany(const QString &company);
    bool checkCountry(const QString &country);
    bool checkCustomerGroup();
    bool checkName();
    bool checkVatNumber();
    bool checkPhone();
    bool checkAddress();
    bool checkCity();
    bool checkState();
    bool checkPriceGroup();
    bool checkRemarque();

    int addCompany();
    int addCity();
    int addState();
    int addAddress();

    void updateAllComboLists();
    void initCustomerGroupCombo();
    void initPriceGroupCombo();

private:
    Toast *mToast;

    Cfg_Db *mCfgDb;
    DBH    *DB;

    QStringList listCompanies;
    QStringList listCountries;
    QStringList listCities;
    QStringList listStates;

    QCompleter *C_cities;
    QCompleter *C_states;

    QString postalCodeReg;
    QString postalCodeFormat;

    QValidator  *v;
    Patterns     p;
    ActionsStyle s;
};

#endif // F_ADDCUSTOMER_H
