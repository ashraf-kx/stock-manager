#include "f_addsupplier.h"
#include "ui_f_addsupplier.h"

Q_LOGGING_CATEGORY(LC_XD,"people.addsupplier")

F_AddSupplier::F_AddSupplier(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_AddSupplier)
{
    qCDebug(LC_XD)<<__FILE__;
    ui->setupUi(this);

    QTime t;
    t.start();
    //########### Connect To Database ###################
    mCfgDb = new Cfg_Db();

    this->DBH = QSqlDatabase::addDatabase(mCfgDb->getDriverName(),"CnxAddSupplier");
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
    connect(ui->Bt_addSupplier,SIGNAL(clicked(bool)),this,SLOT(addSupplier()));

    connect(ui->Cb_country,SIGNAL(currentIndexChanged(int)),
            this,SLOT(updateCityStateCompleters()));
    connect(ui->Cb_country,SIGNAL(currentIndexChanged(int)),
            this,SLOT(updatePostalCodeLEdit()));


    this->setStatusTip(tr("Time elapsed : ")+QString::number(t.elapsed())+" ms.");
}

F_AddSupplier::~F_AddSupplier()
{
    delete ui;
}

bool F_AddSupplier::inputsVerification()
{
    bool check = true;
    if(emailCheck(ui->Le_email->text()))
    {
        v   = new QRegExpValidator(p["email"]);
        int pos=0;
        switch (v->validate(ui->Le_email->text(),pos)) {
        case v->Invalid:
            qCDebug(LC_XD)<<__FILE__<<"Error email";
            mToast = new Toast(this);
            mToast->show(tr("Invalide Em@il"),s["error_alert"]);
            ui->Le_email->setStyleSheet(s["error"]);
            check = false;
            break;
        case v->Acceptable:
            qCDebug(LC_XD)<<__FILE__<<"valide email <ok>";
            mToast = new Toast(this);
            mToast->show(tr("email verified"),s["accepted_alert"]);
            ui->Le_email->setStyleSheet(s["accepted"]);
            break;
        case v->Intermediate:
            qCDebug(LC_XD)<<__FILE__<<"email not finished yet";
            mToast = new Toast(this);
            mToast->show(tr("Type Email"),s["info_alert"]);
            ui->Le_email->setStyleSheet(s["error"]);
            check = false;
            break;
        default:
            break;
        }
    }else
    {
        ui->Le_email->setStyleSheet(s["error"]);
        qCDebug(LC_XD)<<__FILE__<<"Em@il Already Used";
        mToast = new Toast(this);
        mToast->show(tr("Em@il Already Used."),s["warning_alert"]);
        check = false;
    }

    if(check)
    {
        if(!companyCheck(ui->Cb_company->currentText()))
        {
            qCDebug(LC_XD)<<__FILE__<<"Assign this new Supplier to a Company";
            mToast = new Toast(this);
            mToast->show(tr("Assign this new Supplier to a Company."),s["info_alert"]);
            check = false;
        }

        if(!countryCheck(ui->Cb_country->currentText()))
        {
            qCDebug(LC_XD)<<__FILE__<<"Select Country.";
            mToast = new Toast(this);
            mToast->show(tr("Select Country."),s["info_alert"]);
            check = false;
        }
    }

    return check;
}

void F_AddSupplier::addSupplier()
{
    if(inputsVerification())
    {
        int country_id = getCountryID(ui->Cb_country->currentText());
        qCDebug(LC_XD)<<__LINE__<<"country_id : "<<country_id<<"->"<<ui->Cb_country->currentText();
        int company_id = getCompanyID(ui->Cb_company->currentText());
        qCDebug(LC_XD)<<__LINE__<<"company_id : "<<company_id<<"->"<<ui->Cb_company->currentText();

        if(!this->DBH.isOpen())
            this->DBH.open();
        this->DBH.transaction();

        //! [1] Execute Statements On `addresses`,`suppliers`,`states`,`cities`,`countries` Table.
        QSqlQuery *query = new QSqlQuery(this->DBH);

        int supplier_id = 0;
        int address_id = 0;
        int state_id = 0;
        int city_id =0;

        query->clear();
        query->prepare("SELECT `id` FROM `suppliers` WHERE `fullname`=:fullname AND `company_id`=:company_id");
        query->bindValue(":fullname",ui->Le_name->text());
        query->bindValue(":company_id", company_id);
        query->exec();
        if(query->next())
                supplier_id = query->value("id").toInt();
        qCDebug(LC_XD)<<__LINE__<<"supplier_id(find) : "<<supplier_id;

        // dailog to make sure that admin is aware of the existance of this person who works in the company.
        bool accept = true;
        if(supplier_id > 0)
        {
            Dialog *D = new Dialog(this);
            D->setMessage(tr("This supplier exist Already, are you sure you want to Add it ?"),"question");
            if(D->exec() == 1)
                accept =true;
            else
                accept =false;
        }
        if(accept)
        {

            // Add State.
            if(!ui->Le_state->text().isEmpty())
            {
                query->clear();
                query->prepare("SELECT `id` FROM `states` WHERE `name`=:name AND `country_id`=:country_id");
                query->bindValue(":name", ui->Le_state->text());
                query->bindValue(":country_id", country_id);
                query->exec();

                if(query->next())
                    state_id = query->value("id").toInt();
                qCDebug(LC_XD)<<__LINE__<<"state_id(find) : "<<state_id<<"->"<<ui->Le_state->text();
                if(state_id == 0)
                {
                    query->clear();
                    query->prepare("INSERT INTO `states` (`name`,`country_id`) VALUES (:name,:country_id)");
                    query->bindValue(":name", ui->Le_state->text());
                    query->bindValue(":country_id", country_id);
                    query->exec();
                    qCDebug(LC_XD)<<__LINE__<<"State_id (Get by Funt After insertion) : "<<query->lastInsertId().toInt();

                    query->clear();
                    query->prepare("SELECT `id` FROM `states` WHERE `name`=:name AND `country_id`=:country_id ");
                    query->bindValue(":name", ui->Le_state->text());
                    query->bindValue(":country_id", country_id);
                    query->exec();

                    if(query->next())
                        state_id = query->value("id").toInt();
                    qCDebug(LC_XD)<<__LINE__<<"state_id : "<<state_id<<"->"<<ui->Le_state->text();
                }
            }
            // Add City.

            if(!ui->Le_city->text().isEmpty())
            {
                query->clear();
                query->prepare("SELECT `id` FROM `cities` WHERE `name_lang1`=:name AND `country_id`=:country_id");
                query->bindValue(":name", ui->Le_city->text());
                query->bindValue(":country_id", country_id);
                query->exec();
                if(query->next())
                    city_id = query->value("id").toInt();
                qCDebug(LC_XD)<<__LINE__<<"city_id (find): "<<city_id<<"->"<<ui->Le_city->text();

                if(city_id == 0)
                {
                    query->clear();
                    query->prepare("INSERT INTO `cities` (`name_lang1`,`country_id`) VALUES (:name,:country_id)");
                    query->bindValue(":name", ui->Le_city->text());
                    query->bindValue(":country_id", country_id);
                    query->exec();
                    qCDebug(LC_XD)<<__LINE__<<"city_id (getIsertID-Funt): "<<query->lastInsertId().toInt();

                    query->clear();
                    query->prepare("SELECT `id` FROM `cities` WHERE `name_lang1`=:name AND `country_id`=:country_id ");
                    query->bindValue(":name", ui->Le_city->text());
                    query->bindValue(":country_id", country_id);
                    query->exec();

                    if(query->next())
                        city_id = query->value("id").toInt();
                    qCDebug(LC_XD)<<__LINE__<<"city_id (manual): "<<city_id<<"=>"<<ui->Le_city->text();
                }
            }

            // Add Address.
            query->clear();
            if(state_id > 0)
            {
                query->prepare("INSERT INTO `addresses` (`name`,`postal_code`,`city_id`,`state_id`)"
                               "VALUES (:name,:postal_code,:city_id,:state_id)");
                query->bindValue(":name", ui->Le_address->text());
                query->bindValue(":postal_code", ui->Le_postalCode->text());
                query->bindValue(":city_id", city_id);
                query->bindValue(":state_id", state_id);
                query->exec();
                if(query->lastInsertId().toInt() > 0) address_id = query->lastInsertId().toInt();
                qCDebug(LC_XD)<<__LINE__<<"address_id(Funt) : "<<query->lastInsertId().toInt();

            }else{
                query->prepare("INSERT INTO `addresses` (`name`,`postal_code`,`city_id`)"
                               "VALUES (:name,:postal_code,:city_id)");
                query->bindValue(":name", ui->Le_address->text());
                query->bindValue(":postal_code", ui->Le_postalCode->text());
                query->bindValue(":city_id", city_id);
                query->exec();
                if(query->lastInsertId().toInt() > 0) address_id = query->lastInsertId().toInt();
                qCDebug(LC_XD)<<__LINE__<<"address_id(Funt) : "<<query->lastInsertId().toInt();
            }

            if (query->next()) {
                    address_id = query->value("id").toInt();
            }
            qCDebug(LC_XD)<<__LINE__<<"address_id(manual) : "<<address_id;
        }

        // Add Supplier.
        if(accept)
        {
            query->clear();
            query->prepare("INSERT INTO `suppliers` (`fullname`,`email`,`phone`,`vat_number`,`company_id`,`address_id`) "
                           "VALUES(:fullname,:email,:phone,:vat_number,:company_id,:address_id)");

            query->bindValue(":fullname",ui->Le_name->text());
            query->bindValue(":email", ui->Le_email->text());
            query->bindValue(":phone", ui->Le_phone->text());
            query->bindValue(":vat_number", ui->Le_vtaNumber->text());
            query->bindValue(":company_id", company_id);
            query->bindValue(":address_id", address_id);
            qCDebug(LC_XD)<<__LINE__<<ui->Le_name->text()<<ui->Le_email->text()
                         <<ui->Le_phone->text()<<company_id<<address_id;
            query->exec();
            qCDebug(LC_XD)<<__LINE__<<"supplier_id (Funt) : "<<query->lastInsertId().toInt();

            this->setStatusTip(tr("Supplier Inserted seccussfully."));
            clearInputs();
        }
        this->DBH.commit();
    }
}

int F_AddSupplier::getCountryID(const QString& name)
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

int F_AddSupplier::getCompanyID(const QString &name)
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

bool F_AddSupplier::emailCheck(const QString &email)
{
    if(email.isEmpty())
        return false;

    bool check = false;
    if(!this->DBH.isOpen())
        this->DBH.open();
    this->DBH.transaction();

    //! [1] Execute Statements On `suppliers` Table.
    QSqlQuery *query = new QSqlQuery(this->DBH);

    query->prepare("SELECT `id` FROM `suppliers` WHERE `email`=:email");
    query->bindValue(":email",email);
    query->exec();

    if(query->next())
        check = false;
    else
        check = true;

    this->DBH.commit();
    return check;
}

void F_AddSupplier::initCompanyCombo()
{
    ui->Cb_company->addItem(tr("Select Company"));
    ui->Cb_company->addItems(listCompanies);
}

void F_AddSupplier::initCountryCombo()
{
    ui->Cb_company->addItem(tr("Select Country"));
    ui->Cb_country->addItems(listCountries);
}

void F_AddSupplier::updateCityStateCompleters()
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

void F_AddSupplier::updatePostalCodeLEdit()
{
    int country_id = getCountryID(ui->Cb_country->currentText()); // Do not Call a Transaction inside another.

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

void F_AddSupplier::clearInputs()
{
    QList<QLineEdit *> LEs = this->findChildren<QLineEdit *>();
    foreach (QLineEdit *Le, LEs) {
        Le->setStyleSheet(s["black"]);
        Le->clear();
    }
    ui->Cb_company->setCurrentIndex(0);
}

QStringList F_AddSupplier::getAllCompanies()
{
    QStringList tmpList;
    if(!this->DBH.isOpen())
        this->DBH.open();
    this->DBH.transaction();

    //! [1] Execute Statements On `companies` Table.
    QSqlQuery *query = new QSqlQuery(this->DBH);

    query->prepare("SELECT name FROM companies");
    query->exec();

    tmpList.clear();

    while(query->next()){
        if(!query->value("name").toString().isEmpty())
            tmpList<<query->value("name").toString();
    }

    this->DBH.commit();
    return tmpList;
}

QStringList F_AddSupplier::getAllCountries()
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
        if(!query->value(0).toString().isEmpty())
            tmpList<<query->value(0).toString();
    }

    this->DBH.commit();
    return tmpList;
}

QStringList F_AddSupplier::getAllCities(int country_id)
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
        if(!query->value(0).toString().isEmpty())
            tmpList<<query->value(0).toString();
    }

    this->DBH.commit();
    return tmpList;
}

QStringList F_AddSupplier::getAllStates(int country_id)
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
        if(!query->value(0).toString().isEmpty())
            tmpList<<query->value(0).toString();
    }

    this->DBH.commit();
    return tmpList;
}

bool F_AddSupplier::companyCheck(const QString &company)
{
    if(company == tr("Select Company"))
        return false;
    else
        return true;
}

bool F_AddSupplier::countryCheck(const QString &country)
{
    if(country == tr("Select Company") || !listCountries.contains(country))
        return false;
    else
        return true;
}
