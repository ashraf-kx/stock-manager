#include "f_adduser.h"
#include "ui_f_adduser.h"

F_AddUser::F_AddUser(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_AddUser)
{
    QTime t;
    t.start();

    ui->setupUi(this);

    this->setStyleSheet(Style::loadStyle("addUser"));

    QFont f = QFont();
    f.setPointSizeF(15);
    this->setFont(f);

    qDebug()<<this->objectName()<<" font Size of "<<this->fontInfo().pointSizeF();
    //########### Connect To Database ###################
    mCfgDb = new Cfg_Db();
    DB = new DBH("_addUser_");

    //############ Assign Completers ####################
    initCompanyCombo();
    initGroupCombo();

    ui->Cb_company->setGraphicsEffect(Style::shadow());
    ui->Cb_gender->setGraphicsEffect(Style::shadow());
    ui->Cb_group->setGraphicsEffect(Style::shadow());
    ui->Cb_status->setGraphicsEffect(Style::shadow());

    //########## Connectors Signal ~> slots #############
    connect(ui->Bt_addUser,SIGNAL(clicked(bool)),this,SLOT(addUser()));

    this->setStatusTip(tr("Time elapsed : ")+QString::number(t.elapsed())+" ms.");
//this->setGraphicsEffect(Style::shadow());
}

F_AddUser::~F_AddUser()
{
    DB->mRemoveDatabase("_addUser_");
    delete ui;
}

void F_AddUser::initCompanyCombo()
{
    listCompanies = DB->getAllCompanies();
    ui->Cb_company->clear();
    ui->Cb_company->addItem(tr("Select Company"));
    ui->Cb_company->addItems(listCompanies);
}

void F_AddUser::initGroupCombo()
{
    listGroups = DB->getAllGroups();
    ui->Cb_group->clear();
    ui->Cb_group->addItem(tr("Select User Group"));
    ui->Cb_group->addItems(listGroups);
}

bool F_AddUser::inputsVerification()
{
    // Entries Verification
    ui->Bt_addUser->setDisabled(true);
    bool check = true;
//    if(!ui->W_firstName->text().isEmpty())
//    {
//        v   = new QRegExpValidator(p["firstname"]);
//        int pos=0;
//        switch (v->validate(ui->W_firstName->text(),pos)) {
//        case v->Invalid:
//            qDebug()<<"Error firstName";
//           // ui->W_firstName->setToolTip(tr("Error in firstName."));
//            ui->W_firstName->setStyleSheet(s["error"]);
//            check = false;
//            break;
//        case v->Acceptable:
//            qDebug()<<"valide firstName";
//           // ui->W_firstName->setToolTip(tr("Good Job"));
//            ui->W_firstName->setStyleSheet(s["accepted"]);
//            break;
//        case v->Intermediate:
//            qDebug()<<"firstName not finished yet";
//           // ui->W_firstName->setToolTip(tr("Complete typing"));
//            ui->W_firstName->setStyleSheet(s["error"]);
//            check = false;
//            break;
//        default:
//            break;
//        }
//    }else
//    {
//        qDebug()<<"firstName empty.";
//        ui->W_firstName->setStyleSheet(s["error"]);
//        check = false;
//    }

//    if(!ui->W_lastName->text().isEmpty())
//    {
//        v   = new QRegExpValidator(p["lastname"]);
//        int pos=0;
//        switch (v->validate(ui->W_lastName->text(),pos)) {
//        case v->Invalid:
//            qDebug()<<"Error lastName";
//           // ui->W_lastName->setToolTip(tr("Error in lastName."));
//            ui->W_lastName->setStyleSheet(s["error"]);
//            check = false;
//            break;
//        case v->Acceptable:
//            qDebug()<<"valide lastName";
//           // ui->W_lastName->setToolTip(tr("Good Job"));
//            ui->W_lastName->setStyleSheet(s["accepted"]);
//            break;
//        case v->Intermediate:
//            qDebug()<<"lastName not finished yet";
//           // ui->W_lastName->setToolTip(tr("Complete typing"));
//            ui->W_lastName->setStyleSheet(s["error"]);
//            check = false;
//            break;
//        default:
//            break;
//        }
//    }else
//    {
//        qDebug()<<"Last Name empty.";
//        ui->W_lastName->setStyleSheet(s["error"]);
//        check = false;
//    }

//    if(!ui->W_phone->text().isEmpty())
//    {
//        v   = new QRegExpValidator(p["phone"]);
//        int pos=0;
//        switch (v->validate(ui->W_phone->text(),pos)) {
//        case v->Invalid:
//            qDebug()<<"Error phone";
//           // ui->W_phone->setToolTip(tr("Error in phone."));
//            ui->W_phone->setStyleSheet(s["error"]);
//            check = false;
//            break;
//        case v->Acceptable:
//            qDebug()<<"valide phone";
//           // ui->W_phone->setToolTip(tr("Good Job"));
//            ui->W_phone->setStyleSheet(s["accepted"]);
//            break;
//        case v->Intermediate:
//            qDebug()<<"phone not finished yet";
//           // ui->W_phone->setToolTip(tr("Complete typing"));
//            ui->W_phone->setStyleSheet(s["error"]);
//            check = false;
//            break;
//        default:
//            break;
//        }
//    }else
//    {
//        qDebug()<<"Last Name empty.";
//        ui->W_phone->setStyleSheet(s["error"]);
//        check = false;
//    }

    if(emailCheck(ui->W_email->text()))
    {
        v   = new QRegExpValidator(p["email"]);
        int pos=0;
        QString tmp_str = ui->W_email->text();
        switch (v->validate(tmp_str,pos)) {
        case v->Invalid:
            qDebug()<<"Error email";
            mToast = new Toast(this);
            mToast->show(tr("Invalide Em@il"),s["error_alert"]);
            //ui->W_email->setStyleSheet(s["error"]);
            check = false;
            break;
        case v->Acceptable:
            qDebug()<<"valide email";
            mToast = new Toast(this);
            mToast->show(tr("email verified"),s["accepted_alert"]);
            //ui->W_email->setStyleSheet(s["accepted"]);
            break;
        case v->Intermediate:
            qDebug()<<"email not finished yet";
            mToast = new Toast(this);
            mToast->show(tr("Type Email"),s["info_alert"]);
            //ui->W_email->setStyleSheet(s["error"]);
            check = false;
            break;
        default:
            break;
        }
    }else
    {
        //ui->W_email->setStyleSheet(s["error"]);
        mToast = new Toast(this);
        mToast->show(tr("Em@il Already Used."),s["warning_alert"]);
        check = false;
    }

    if(usernameCheck(ui->W_username->text()))
    {
        //ui->W_username->setStyleSheet(s["accepted"]);
        v   = new QRegExpValidator(p["username"]);
        int pos=0;
        QString tmp_str = ui->W_username->text();
        switch (v->validate(tmp_str,pos)) {
        case v->Invalid:
            qDebug()<<"Error username";
           // ui->W_username->setToolTip(tr("Error in username."));
            ui->W_username->setStyleSheet(s["error"]);
            check = false;
            break;
        case v->Acceptable:
            qDebug()<<"valide username";
           // ui->W_username->setToolTip(tr("Good Job"));
            ui->W_username->setStyleSheet(s["accepted"]);
            break;
        case v->Intermediate:
            qDebug()<<"username not finished yet";
           // ui->W_username->setToolTip(tr("Complete typing"));
            ui->W_username->setStyleSheet(s["error"]);
            check = false;
            break;
        default:
            break;
        }
    }else
    {
        ui->W_username->setStyleSheet(s["error"]);
        check = false;
    }

    if(passwordCheck(ui->W_password->text(),ui->W_confirmePass->text()))
    {
        v   = new QRegExpValidator(p["password"]);
        int pos=0;
        QString tmp_str = ui->W_password->text();
        switch (v->validate(tmp_str,pos)) {
        case v->Invalid:
            qDebug()<<"Error password";
            ui->W_password->setToolTip(tr("respect the password norme"));
            ui->W_password->setStyleSheet(s["error"]);
            ui->W_confirmePass->setStyleSheet(s["error"]);
            check = false;
            break;
        case v->Acceptable:
            qDebug()<<"password verified";
            ui->W_password->setToolTip(tr("Good Job"));
            ui->W_password->setStyleSheet(s["accepted"]);
            ui->W_confirmePass->setStyleSheet(s["accepted"]);
            break;
        case v->Intermediate:
            qDebug()<<"waiting...";
            ui->W_password->setToolTip(tr("Complete typing"));
            ui->W_password->setStyleSheet(s["error"]);
            ui->W_confirmePass->setStyleSheet(s["error"]);
            check = false;
            break;
        default:
            break;
        }

    }else
    {
      qDebug()<<"Mis-Match passwords";
      ui->W_password->setStyleSheet(s["error"]);
      ui->W_confirmePass->setStyleSheet(s["error"]);
      check = false;
    }

    if(check)
    {
        if(!groupCheck(ui->Cb_group->currentText()))
        {
            //mToast  = new Toast();
            //mToast ->setMessage(tr("Select User Group"));
            check = false;
        }

        if(!companyCheck(ui->Cb_company->currentText()))
        {
//            mToast = new Toast();
//            mToast->setMessage(tr("Assign this new user to a Company."));
            check = false;
        }
    }

    return check;
}

void F_AddUser::addUser()
{
     //INSERT THE NEW USERS.
    if(inputsVerification())
    {
        int company_id = -1;
        int group_id   = -1;

        company_id  = DB->getCompanyID(ui->Cb_company->currentText());
        group_id    = DB->getGroupID(ui->Cb_group->currentText());
        DB->addUser(ui->W_firstName->text(),
                    ui->W_lastName->text(),
                    ui->W_username->text(),
                    ui->W_password->text(),
                    ui->W_email->text(),
                    ui->Cb_gender->currentText(),
                    ui->Cb_status->currentText(),
                    group_id,company_id);

        clearInputs();
    }
    ui->Bt_addUser->setEnabled(true);
}

bool F_AddUser::emailCheck(const QString& email) /* IF does not exits return TRUE. */
{
    if(email.isEmpty())
        return false;

    if(DB->getUserEmail(email) == -1)
        return true;
    else
        return false;
}

bool F_AddUser::usernameCheck(const QString& username)
{
    if(username.isEmpty())
        return false;

    if(DB->getUserName(username) == -1)
        return true;
    else
        return false;
}

bool F_AddUser::groupCheck(const QString& group)
{
    if(group == tr("Select User Group"))
        return false;
    else
        return true;
}

bool F_AddUser::companyCheck(const QString& company)
{
    if(company == tr("Select Company"))
        return false;
    else
        return true;
}

bool F_AddUser::passwordCheck(const QString& password,const QString& Confirme)
{
    return (password == Confirme);
}

void F_AddUser::clearInputs()
{
    QList<QLineEdit *> LEs = this->findChildren<QLineEdit *>();
    foreach (QLineEdit *Le, LEs) {
        Le->setStyleSheet(s["black"]);
        Le->clear();
    }
    ui->Cb_gender->setCurrentIndex(0);
    ui->Cb_company->setCurrentIndex(0);
    ui->Cb_status->setCurrentIndex(0);
    ui->Cb_group->setCurrentIndex(0);
}
