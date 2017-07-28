#include "f_addcustomer.h"
#include "ui_f_addcustomer.h"

Q_LOGGING_CATEGORY(LC_XDCus,"people.addcustomer")

F_AddCustomer::F_AddCustomer(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_AddCustomer)
{
    qCDebug(LC_XDCus)<<__FILE__;
    ui->setupUi(this);
    QTime t;
    t.start();
    //########### Connect To Database ###################
    mCfgDb = new Cfg_Db();

    this->DBH = QSqlDatabase::addDatabase(mCfgDb->getDriverName(),"CnxAddCustomer");
    this->DBH.setHostName(mCfgDb->getHostname());
    this->DBH.setDatabaseName(mCfgDb->getSchemaName());
    this->DBH.setUserName(mCfgDb->getUsername());
    this->DBH.setPassword(mCfgDb->getPassword());
    this->DBH.open();

    //########### UPDATE Combos & Completers ############
    listCompanies = getAllCompanies();
    listCountries = getAllCountries();
    initCompanyCombo();
    initCountryCombo();
    listCities    = getAllCities(getCountryID(ui->Cb_country->currentText()));
    listStates    = getAllStates(getCountryID(ui->Cb_country->currentText()));
    updateCityStateCompleters();
    //########## Connectors Signal ~> slots #############
    connect(ui->Bt_addCustomer,SIGNAL(clicked(bool)),this,SLOT(addCustomer()));

    connect(ui->Cb_country,SIGNAL(currentIndexChanged(int)),
            this,SLOT(updateCityStateCompleters()));
    connect(ui->Cb_country,SIGNAL(currentIndexChanged(int)),
            this,SLOT(updatePostalCodeLEdit()));


    this->setStatusTip(tr("Time elapsed : ")+QString::number(t.elapsed())+" ms.");
}

F_AddCustomer::~F_AddCustomer()
{
    delete ui;
}

bool F_AddCustomer::checkEmail(const QString &email)
{
    if(email.isEmpty())
        return false;

    bool check = false;
    if(!this->DBH.isOpen())
        this->DBH.open();
    this->DBH.transaction();

    //! [1] Execute Statements On `customers` Table.
    QSqlQuery *query = new QSqlQuery(this->DBH);

    query->prepare("SELECT `id` FROM `customers` WHERE `email`=:email");
    query->bindValue(":email",email);
    query->exec();

    if(query->next())
        check = false;
    else
        check = true;

    this->DBH.commit();
    return check;
}

void F_AddCustomer::initCompanyCombo()
{
    ui->Cb_company->addItem(tr("Select Company"));
    ui->Cb_company->addItems(listCompanies);
}

void F_AddCustomer::initCountryCombo()
{
    ui->Cb_company->addItem(tr("Select Country"));
    ui->Cb_country->addItems(listCountries);
}

void F_AddCustomer::initCustomerGroupCombo()
{

}

void F_AddCustomer::initPriceGroupCombo()
{

}

void F_AddCustomer::updateCityStateCompleters()
{
    listCities = getAllCities(getCountryID(ui->Cb_country->currentText()));
    listStates = getAllStates(getCountryID(ui->Cb_country->currentText()));

    C_states = new QCompleter(listStates);
    C_states->setCaseSensitivity(Qt::CaseInsensitive);
    ui->Le_state->setCompleter(C_states);

    C_cities = new QCompleter(listCities);
    C_cities->setCaseSensitivity(Qt::CaseInsensitive);
    ui->Le_city->setCompleter(C_cities);
}

void F_AddCustomer::updatePostalCodeLEdit()
{
    // Do not Call a Transaction inside another.
    int country_id = getCountryID(ui->Cb_country->currentText());

    if(!this->DBH.isOpen())
        this->DBH.open();
    this->DBH.transaction();

    //! [1] Execute Statements On `countries` Table.
    QSqlQuery *query = new QSqlQuery(this->DBH);

    query->prepare("SELECT `postal_code_id` FROM `countries` WHERE `id`=:id");
    query->bindValue(":id",country_id);
    query->exec();

    int code_id =-1;

    if(query->next()){
        code_id = query->value("postal_code_id").toInt();
    }

    if(code_id > -1)
    {
        query->prepare("SELECT `format`,`regex` FROM `postal_codes` WHERE `id`=:id");
        query->bindValue(":id",code_id);
        query->exec();
        if(query->next()){
            postalCodeReg    = query->value("regex").toString();
            postalCodeFormat = query->value("format").toString();
            ui->Le_postalCode->setPlaceholderText(postalCodeFormat);
            ui->Le_postalCode->setMaxLength(postalCodeFormat.length());
        }else
        {
            postalCodeReg    = "";
            postalCodeFormat = "";
            ui->Le_postalCode->setPlaceholderText("");
            ui->Le_postalCode->setMaxLength(45);
        }
    }else
    {
        postalCodeReg    = "";
        postalCodeFormat = "";
        ui->Le_postalCode->setPlaceholderText("");
        ui->Le_postalCode->setMaxLength(45);
    }

    this->DBH.commit();
}

void F_AddCustomer::clearInputs()
{
    QList<QLineEdit *> LEs = this->findChildren<QLineEdit *>();
    foreach (QLineEdit *Le, LEs) {
        Le->setStyleSheet(s["black"]);
        Le->clear();
    }
    ui->Cb_company->setCurrentIndex(0);
    ui->Cb_customerGroup->setCurrentIndex(0);
}

bool F_AddCustomer::inputsVerification()
{
    return true;
}

QStringList F_AddCustomer::getAllCompanies()
{
    QStringList tmpList;
    if(!this->DBH.isOpen())
        this->DBH.open();
    this->DBH.transaction();

    //! [1] Execute Statements On `companies` Table.
    QSqlQuery *query = new QSqlQuery(this->DBH);

    query->prepare("SELECT `name` FROM `companies`");
    query->exec();

    tmpList.clear();

    while(query->next()){
        if(!query->value("name").toString().isEmpty())
            tmpList<<query->value("name").toString();
    }

    this->DBH.commit();
    return tmpList;
}

QStringList F_AddCustomer::getAllCountries()
{
    QStringList tmpList;
    if(!this->DBH.isOpen())
        this->DBH.open();
    this->DBH.transaction();

    //! [1] Execute Statements On `countries` Table.
    QSqlQuery *query = new QSqlQuery(this->DBH);

    query->prepare("SELECT `name` FROM `countries`");
    query->exec();

    tmpList.clear();

    while(query->next()){
        if(!query->value("name").toString().isEmpty())
            tmpList<<query->value("name").toString();
    }

    this->DBH.commit();
    return tmpList;
}

QStringList F_AddCustomer::getAllCities(int country_id)
{
    QStringList tmpList;
    if(!this->DBH.isOpen())
        this->DBH.open();
    this->DBH.transaction();

    //! [1] Execute Statements On `cities` Table.
    QSqlQuery *query = new QSqlQuery(this->DBH);

    query->prepare("SELECT `name_lang1` FROM `cities` WHERE `country_id`=:country_id ");
    query->bindValue(":country_id",country_id);
    query->exec();

    tmpList.clear();

    while(query->next()){
        if(!query->value("name_lang1").toString().isEmpty())
            tmpList<<query->value("name_lang1").toString();
    }

    this->DBH.commit();
    return tmpList;
}

QStringList F_AddCustomer::getAllStates(int country_id)
{
    QStringList tmpList;
    if(!this->DBH.isOpen())
        this->DBH.open();
    this->DBH.transaction();

    //! [1] Execute Statements On `states` Table.
    QSqlQuery *query = new QSqlQuery(this->DBH);

    query->prepare("SELECT `name` FROM `states` WHERE `country_id`=:country_id ");
    query->bindValue(":country_id",country_id);
    query->exec();

    tmpList.clear();

    while(query->next()){
        if(!query->value("name").toString().isEmpty())
            tmpList<<query->value("name").toString();
    }

    this->DBH.commit();
    return tmpList;
}

int F_AddCustomer::getCountryID(const QString &name)
{
    if(!this->DBH.isOpen())
        this->DBH.open();
    this->DBH.transaction();

    //! [1] Execute Statements On `countries` Table.
    QSqlQuery *query = new QSqlQuery(this->DBH);

    query->prepare("SELECT `id` FROM `countries` WHERE `name`=:name");
    query->bindValue(":name",name);
    query->exec();

    int country_id=0;

    if(query->next()){
        country_id = query->value("id").toInt();
    }

    this->DBH.commit();
    return country_id;
}

int F_AddCustomer::getCompanyID(const QString &name)
{
    if(!this->DBH.isOpen())
        this->DBH.open();
    this->DBH.transaction();
    int company_id = 0;
    //! [1] Execute Statements On `companies` Table.
    QSqlQuery *query = new QSqlQuery(this->DBH);

    query->prepare("SELECT `id` FROM `companies` WHERE `name`=:name");
    query->bindValue(":name",name);
    query->exec();

    if(query->next()){
        company_id = query->value("id").toInt();
    }

    this->DBH.commit();
    return company_id;
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
