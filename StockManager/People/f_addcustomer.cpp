#include "f_addcustomer.h"

Q_LOGGING_CATEGORY(LC_XDCus,"people.addcustomer")

F_AddCustomer::F_AddCustomer(QWidget *parent) :
    QFrame(parent)
{
    QTime t;
    t.start();
    qCDebug(LC_XDCus)<<__FILE__;
    setupUi(this);
    this->setStyleSheet(Style::loadStyle("addCustomer"));

    //########### Connect To Database ###################
    mCfgDb = new Cfg_Db();
    DB = new DBH("_addcustomer_");

    //########### UPDATE Combos & Completers ############
    initCompanyCombo();
    initCountryCombo();
    updateCityStateCompleters();

    //########## Connectors Signal ~> slots #############
    connect(Bt_addCustomer,SIGNAL(clicked(bool)),this,SLOT(addCustomer()));

    connect(Cb_country,SIGNAL(currentIndexChanged(int)),
            this,SLOT(updateCityStateCompleters()));
    connect(Cb_country,SIGNAL(currentIndexChanged(int)),
            this,SLOT(updatePostalCodeLEdit()));

    this->setStatusTip(tr("Time elapsed : ")+QString::number(t.elapsed())+" ms.");
}

F_AddCustomer::~F_AddCustomer()
{
    #ifdef _WIN32
        DB->mRemoveDatabase("_addcustomer_");
    #endif
    //delete ui;
}

bool F_AddCustomer::checkEmail(const QString &email)
{
    if(email.isEmpty())
        return false;
    else
        if(DB->getCustomerEmail(email) == -1)
            return true;
        else
            return false;
}

void F_AddCustomer::initCompanyCombo()
{
    listCompanies = DB->getAllCompanies();
    Cb_company->clear();
    Cb_company->addItem(tr("Select Company"));
    Cb_company->addItems(listCompanies);
}

void F_AddCustomer::initCountryCombo()
{
    listCountries = DB->getAllCountries();
    Cb_company->clear();
    Cb_company->addItem(tr("Select Country"));
    Cb_country->addItems(listCountries);
}

void F_AddCustomer::initCustomerGroupCombo()
{

}

void F_AddCustomer::initPriceGroupCombo()
{

}

void F_AddCustomer::updateCityStateCompleters()
{
    listCities = DB->getAllCities(DB->getCountryID(Cb_country->currentText()));
    listStates = DB->getAllStates(DB->getCountryID(Cb_country->currentText()));

    C_states = new QCompleter(listStates);
    C_states->setCaseSensitivity(Qt::CaseInsensitive);
    W_state->getLineEdit()->setCompleter(C_states);

    C_cities = new QCompleter(listCities);
    C_cities->setCaseSensitivity(Qt::CaseInsensitive);
    W_city->getLineEdit()->setCompleter(C_cities);
}

void F_AddCustomer::updatePostalCodeLEdit()
{
    // Do not Call a Transaction inside another.
    int country_id = DB->getCountryID(Cb_country->currentText());
    int code_id    = DB->getPostalCodeID(country_id);

    if(code_id > -1)
    {
        QMap<QString, QString> data = DB->getPostalCodeMeta(code_id);

        if( !(data["regex"]).isEmpty() && !(data["format"]).isEmpty() )
        {
            W_postalcode->getLineEdit()->setPlaceholderText(data["format"]);
            W_postalcode->getLineEdit()->setMaxLength(data["format"].length());
        }

    }else
    {
        postalCodeReg.clear();
        postalCodeFormat.clear();
        W_postalcode->getLineEdit()->setPlaceholderText("");
        W_postalcode->getLineEdit()->setMaxLength(45);
    }
}

void F_AddCustomer::clearInputs()
{
    QList<QLineEdit *> LEs = this->findChildren<QLineEdit *>();
    foreach (QLineEdit *Le, LEs) {
        Le->setStyleSheet(s["black"]);
        Le->clear();
    }

    Cb_company->setCurrentIndex(0);
    Cb_customerGroup->setCurrentIndex(0);
}

bool F_AddCustomer::inputsVerification()
{
    return true;
}

//!<><><><><><><><> Methodes Inputs Validation Against user Entries <><><><><><>

bool F_AddCustomer::checkCompany(const QString &company)
{
    if(company == tr("Select Company"))
        return false;
    else
        return true;
}

bool F_AddCustomer::checkCountry(const QString &country)
{
    if(country == tr("Select Company") || !listCountries.contains(country))
        return false;
    else
        return true;
}

bool F_AddCustomer::checkCustomerGroup()
{
    return true;
}

bool F_AddCustomer::checkName()
{
    return true;
}

bool F_AddCustomer::checkVatNumber()
{
    return true;
}

bool F_AddCustomer::checkPhone()
{
    return true;
}

bool F_AddCustomer::checkAddress()
{
    return true;
}

bool F_AddCustomer::checkCity()
{
    return true;
}

bool F_AddCustomer::checkState()
{
    return true;
}

bool F_AddCustomer::checkPriceGroup()
{
    return true;
}

bool F_AddCustomer::checkRemarque()
{
    return true;
}

//!<><><><><><><><> Methodes used to inject Data to the Database <><><><><><>

int F_AddCustomer::addCompany()
{
    return 0;
}

int F_AddCustomer::addCity()
{
    return 0;
}

int F_AddCustomer::addState()
{
    return 0;
}

int F_AddCustomer::addAddress()
{
    return 0;
}

void F_AddCustomer::addCustomer()
{

}

void F_AddCustomer::updateAllComboLists()
{

}
