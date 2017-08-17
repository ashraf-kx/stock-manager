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
    // ######### Graphics Effects #######################
    QGraphicsDropShadowEffect *sh = new QGraphicsDropShadowEffect();
    sh->setBlurRadius(8);
    sh->setOffset(2);
    sh->setColor(QColor(63, 63, 63, 180));
    this->setGraphicsEffect(sh);

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
    connect(ui->Bt_addSupplier,SIGNAL(clicked(bool)),this,SLOT(addSupplier()));

    connect(ui->Cb_country,SIGNAL(currentIndexChanged(int)),
            this,SLOT(updateCityStateCompleters()));
    connect(ui->Cb_country,SIGNAL(currentIndexChanged(int)),
            this,SLOT(updatePostalCodeLEdit()));

    this->setStatusTip(tr("Time elapsed : ")+QString::number(t.elapsed())+" ms.");
}

F_AddSupplier::~F_AddSupplier()
{
    #ifdef _WIN32
        DB->mRemoveDatabase("_addSupplier_");
    #endif
    delete ui;
}

bool F_AddSupplier::inputsVerification()
{
    bool check = true;
    if(emailCheck(ui->Le_email->text()))
    {
        v   = new QRegExpValidator(p["email"]);
        int pos=0;
        QString tmp_str = ui->Le_email->text();
        switch (v->validate(tmp_str,pos)) {
        case QValidator::Invalid:
            qCDebug(LC_XD)<<__FILE__<<"Error email";
            mToast = new Toast(this);
            mToast->show(tr("Invalide Em@il"),s["error_alert"]);
            ui->Le_email->setStyleSheet(s["error"]);
            check = false;
            break;
        case QValidator::Acceptable:
            qCDebug(LC_XD)<<__FILE__<<"valide email <ok>";
            mToast = new Toast(this);
            mToast->show(tr("email verified"),s["accepted_alert"]);
            ui->Le_email->setStyleSheet(s["accepted"]);
            break;
        case QValidator::Intermediate:
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
        int country_id = DB->getCountryID(ui->Cb_country->currentText());
        int company_id = DB->getCompanyID(ui->Cb_company->currentText());
        int supplier_id= DB->getSupplierID(ui->Le_name->text(),company_id);
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
            if(!ui->Le_state->text().isEmpty())
            {
                state_id = DB->getStateID(ui->Le_state->text(),country_id);

                if(state_id > -1)
                {
                    state_id = DB->addState( ui->Le_state->text(),country_id);
                }
            }

            // Add City.
            if(!ui->Le_city->text().isEmpty())
            {
                city_id = DB->getCityID( ui->Le_city->text(),country_id);

                if(city_id > -1)
                {
                    city_id = DB->addCity(ui->Le_city->text(),country_id);
                }
            }

            // Add Address.
             address_id = DB->addAddress(ui->Le_address->text(),ui->Le_postalCode->text(),city_id,state_id);

        // Add Supplier.
        if(accept)
        {
            supplier_id = DB->addSupplier(ui->Le_name->text(),ui->Le_email->text(),ui->Le_phone->text(),ui->Le_vtaNumber->text(),company_id,address_id);

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
    ui->Cb_company->clear();
    ui->Cb_company->addItem(tr("Select Company"));
    ui->Cb_company->addItems(listCompanies);
}

void F_AddSupplier::initCountryCombo()
{
    listCountries = DB->getAllCountries();
    ui->Cb_country->clear();
    ui->Cb_country->addItem(tr("Select Country"));
    ui->Cb_country->addItems(listCountries);
}

void F_AddSupplier::updateCityStateCompleters()
{
    listCities = DB->getAllCities(DB->getCountryID(ui->Cb_country->currentText()));
    listStates = DB->getAllStates(DB->getCountryID(ui->Cb_country->currentText()));

    C_states = new QCompleter(listStates);
    C_states->setCaseSensitivity(Qt::CaseInsensitive);
    ui->Le_state->setCompleter(C_states);

    C_cities = new QCompleter(listCities);
    C_cities->setCaseSensitivity(Qt::CaseInsensitive);
    ui->Le_city->setCompleter(C_cities);
}

void F_AddSupplier::updatePostalCodeLEdit()
{
    int country_id = DB->getCountryID(ui->Cb_country->currentText());
    int code_id    = DB->getPostalCodeID(country_id);

    if(code_id > -1)
    {
        QMap<QString, QString> data = DB->getPostalCodeMeta(code_id);

        if(!(data["regex"]).isEmpty() && !(data["format"]).isEmpty() )
        {
            ui->Le_postalCode->setPlaceholderText(data["format"]);
            ui->Le_postalCode->setMaxLength(data["format"].length());
        }
    }else
    {
        postalCodeReg.clear();
        postalCodeFormat.clear();
        ui->Le_postalCode->setPlaceholderText("");
        ui->Le_postalCode->setMaxLength(45);
    }
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
