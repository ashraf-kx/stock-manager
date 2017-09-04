#include "f_addsupplier.h"

Q_LOGGING_CATEGORY(LC_XD,"people.addsupplier")

F_AddSupplier::F_AddSupplier(QWidget *parent) :
    QFrame(parent)
{
    qCDebug(LC_XD)<<__FILE__;
    setupUi(this);
    this->setStyleSheet(Style::loadStyle("addSupplier"));
    QTime t;
    t.start();
    // ######### Graphics Effects #######################
//    QGraphicsDropShadowEffect *sh = new QGraphicsDropShadowEffect();
//    sh->setBlurRadius(8);
//    sh->setOffset(2);
//    sh->setColor(QColor(63, 63, 63, 180));
//    this->setGraphicsEffect(sh);

    qCDebug(LC_XD)<<"Add Supplier Fram is Windows : "<<this->isWindow();
    qCDebug(LC_XD)<<"Get Modality : "<<this->windowModality();

    //########### Connect To Database ###################
    mCfgDb = new Cfg_Db();

    DB = new DBH("_addSupplier_");

    //########### UPDATE Combos & Completers ############
    initCompanyCombo();
    initCountryCombo();
    updateCityStateCompleters();

    //########## Connectors Signal ~> slots #############
    connect(Bt_addSupplier,SIGNAL(clicked(bool)),this,SLOT(addSupplier()));

    connect(Cb_country,SIGNAL(currentIndexChanged(int)),
            this,SLOT(updateCityStateCompleters()));
    connect(Cb_country,SIGNAL(currentIndexChanged(int)),
            this,SLOT(updatePostalCodeLEdit()));

    this->setStatusTip(tr("Time elapsed : ")+QString::number(t.elapsed())+" ms.");
}

F_AddSupplier::~F_AddSupplier()
{
    #ifdef _WIN32
        DB->mRemoveDatabase("_addSupplier_");
    #endif
    //delete ui;
}

bool F_AddSupplier::inputsVerification()
{
    bool check = true;
    //! [4] Email Verification (Done)
    if(!W_email->text().isEmpty())
    {
        if(emailCheck(W_email->text()))
        {
            v   = new QRegExpValidator(p["email"]);
            int pos=0;
            QString tmp_str = W_email->text();
            switch (v->validate(tmp_str,pos)) {
            case QValidator::Invalid:
                W_email->getHelper()->setVisible(true);
                W_email->parseError("Error E-mail");
                check = false;
                break;
            case QValidator::Acceptable:
                W_email->getHelper()->setVisible(false);
                break;
            case QValidator::Intermediate:
                W_email->getHelper()->setVisible(true);
                W_email->parseError("Error E-mail");
                check = false;
                break;
            default:
                break;
            }
        }else
        {
            W_email->getHelper()->setVisible(true);
            W_email->parseError("E-mail Already Used.");
            check = false;
        }
    }else
    {
        W_email->getHelper()->setVisible(false);
        check = false;
    }

    if(check)
    {
        if(!companyCheck(Cb_company->currentText()))
        {
            qCDebug(LC_XD)<<__FILE__<<"Assign this new Supplier to a Company";
            Cb_company->setStyleSheet("border-bottom: 2px solid #FF1744;");
            check = false;
        }else
        {
            Cb_company->setStyleSheet("border-bottom: 2px solid #0091EA;");
        }

        if(!countryCheck(Cb_country->currentText()))
        {
            Cb_country->setStyleSheet("border-bottom: 2px solid #FF1744;");
            check = false;
        }else
        {
            Cb_country->setStyleSheet("border-bottom: 2px solid #0091EA;");
        }
    }

    return check;
}

void F_AddSupplier::addSupplier()
{
    if(inputsVerification())
    {
        int country_id = DB->getCountryID(Cb_country->currentText());
        int company_id = DB->getCompanyID(Cb_company->currentText());
        int supplier_id= DB->getSupplierID(W_name->text(),company_id);
        int state_id   = -1;
        int city_id    = -1;
        int address_id = -1;

        // dailog to make sure that admin is aware of the existance of this person who works in the company.
        bool accept = true;
        if(supplier_id > -1)
        {
//            Dialog *D = new Dialog(this);
//            D->setMessage(tr("This supplier exist Already, are you sure you want to Add it ?"),"question");
//            if(D->exec() == 1)
//                accept =true;
//            else
//                accept =false;
        }

        if(accept)
        {
            // Add State.
            if(!W_state->text().isEmpty())
            {
                state_id = DB->getStateID(W_state->text(),country_id);

                if(state_id > -1)
                {
                    state_id = DB->addState( W_state->text(),country_id);
                }
            }

            // Add City.
            if(!W_city->text().isEmpty())
            {
                city_id = DB->getCityID( W_city->text(),country_id);

                if(city_id > -1)
                {
                    city_id = DB->addCity(W_city->text(),country_id);
                }
            }

            // Add Address.
             address_id = DB->addAddress(W_address->text(),W_postalcode->text(),city_id,state_id);

        // Add Supplier.
        if(accept)
        {
            supplier_id = DB->addSupplier(W_name->text(),W_email->text(),W_phone->text(),W_vtaNumber->text(),company_id,address_id);

            this->setStatusTip(tr("Supplier Inserted seccussfully."));
            clearInputs();
        }
        }

    }
}

bool F_AddSupplier::emailCheck(const QString &email)
{
    if(email.isEmpty())
        return false;
    if(DB->getSupplierEmail(email) == -1)
        return true;
    else
        return false;
}

void F_AddSupplier::initCompanyCombo()
{
    listCompanies = DB->getAllCompanies();
    Cb_company->clear();
    Cb_company->addItem(tr("Select Company"));
    Cb_company->addItems(listCompanies);
}

void F_AddSupplier::initCountryCombo()
{
    listCountries = DB->getAllCountries();
    Cb_country->clear();
    Cb_country->addItem(tr("Select Country"));
    Cb_country->addItems(listCountries);
}

void F_AddSupplier::updateCityStateCompleters()
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

void F_AddSupplier::updatePostalCodeLEdit()
{
    int country_id = DB->getCountryID(Cb_country->currentText());
    int code_id    = DB->getPostalCodeID(country_id);

    if(code_id > -1)
    {
        QMap<QString, QString> data = DB->getPostalCodeMeta(code_id);

        if(!(data["regex"]).isEmpty() && !(data["format"]).isEmpty() )
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

void F_AddSupplier::clearInputs()
{
    QList<QLineEdit *> LEs = this->findChildren<QLineEdit *>();
    foreach (QLineEdit *Le, LEs) {
        Le->setStyleSheet(s["black"]);
        Le->clear();
    }
    Cb_company->setCurrentIndex(0);
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
    if(country == tr("Select Country") || !listCountries.contains(country))
        return false;
    else
        return true;
}
