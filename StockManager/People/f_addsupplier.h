#ifndef F_ADDSUPPLIER_H
#define F_ADDSUPPLIER_H

#include <QFrame>
#include "ui_f_addsupplier.h"
#include "../classes.h"

Q_DECLARE_LOGGING_CATEGORY(LC_XD)

namespace Ui {
class F_AddSupplier;
}

class F_AddSupplier : public QFrame, private Ui::F_AddSupplier
{
    Q_OBJECT

public:
    explicit F_AddSupplier(QWidget *parent = 0);
    ~F_AddSupplier();

public slots:
    void addSupplier();
    bool emailCheck(const QString & email);

    void initCompanyCombo();
    void initCountryCombo();

    void updateCityStateCompleters();
    void updatePostalCodeLEdit();

    void clearInputs();

    bool inputsVerification();

    bool companyCheck(const QString &company);
    bool countryCheck(const QString &country);

private:
    Toast *mToast;

    Cfg_Db *mCfgDb;
    DBH *DB;

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

#endif // F_ADDSUPPLIER_H
