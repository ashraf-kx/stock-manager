#include "f_adduser.h"
#include "ui_f_adduser.h"

F_AddUser::F_AddUser(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_AddUser)
{
    QTime t;
    t.start();

    ui->setupUi(this);
    //########### Connect To Database ###################
    mCfgDb = new Cfg_Db();
    DB = new DBH("_addUser_");

    //############ Assign Completers ####################
    initCompanyCombo();
    initGroupCombo();

    //########## Connectors Signal ~> slots #############
    connect(ui->Bt_addUser,SIGNAL(clicked(bool)),this,SLOT(addUser()));

    this->setStatusTip(tr("Time elapsed : ")+QString::number(t.elapsed())+" ms.");
}

F_AddUser::~F_AddUser()
{
    DB->mRemoveDatabase("_addUser_");
    delete ui;
}

void F_AddUser::initCompanyCombo()
{
    listCompanies = DB->getAllCompanies();
    ui->Cb_company->addItem(tr("Select Company"));
    ui->Cb_company->addItems(listCompanies);
}

void F_AddUser::initGroupCombo()
{
    listGroups = DB->getAllGroups();
    ui->Cb_group->addItem(tr("Select User Group"));
    ui->Cb_group->addItems(listGroups);
}

bool F_AddUser::inputsVerification()
{
    // Entries Verification
    ui->Bt_addUser->setDisabled(true);
    bool check = true;
//    if(!ui->Le_firstName->text().isEmpty())
//    {
//        v   = new QRegExpValidator(p["firstname"]);
//        int pos=0;
//        switch (v->validate(ui->Le_firstName->text(),pos)) {
//        case v->Invalid:
//            qDebug()<<"Error firstName";
//           // ui->Le_firstName->setToolTip(tr("Error in firstName."));
//            ui->Le_firstName->setStyleSheet(s["error"]);
//            check = false;
//            break;
//        case v->Acceptable:
//            qDebug()<<"valide firstName";
//           // ui->Le_firstName->setToolTip(tr("Good Job"));
//            ui->Le_firstName->setStyleSheet(s["accepted"]);
//            break;
//        case v->Intermediate:
//            qDebug()<<"firstName not finished yet";
//           // ui->Le_firstName->setToolTip(tr("Complete typing"));
//            ui->Le_firstName->setStyleSheet(s["error"]);
//            check = false;
//            break;
//        default:
//            break;
//        }
//    }else
//    {
//        qDebug()<<"firstName empty.";
//        ui->Le_firstName->setStyleSheet(s["error"]);
//        check = false;
//    }

//    if(!ui->Le_lastName->text().isEmpty())
//    {
//        v   = new QRegExpValidator(p["lastname"]);
//        int pos=0;
//        switch (v->validate(ui->Le_lastName->text(),pos)) {
//        case v->Invalid:
//            qDebug()<<"Error lastName";
//           // ui->Le_lastName->setToolTip(tr("Error in lastName."));
//            ui->Le_lastName->setStyleSheet(s["error"]);
//            check = false;
//            break;
//        case v->Acceptable:
//            qDebug()<<"valide lastName";
//           // ui->Le_lastName->setToolTip(tr("Good Job"));
//            ui->Le_lastName->setStyleSheet(s["accepted"]);
//            break;
//        case v->Intermediate:
//            qDebug()<<"lastName not finished yet";
//           // ui->Le_lastName->setToolTip(tr("Complete typing"));
//            ui->Le_lastName->setStyleSheet(s["error"]);
//            check = false;
//            break;
//        default:
//            break;
//        }
//    }else
//    {
//        qDebug()<<"Last Name empty.";
//        ui->Le_lastName->setStyleSheet(s["error"]);
//        check = false;
//    }

//    if(!ui->Le_phone->text().isEmpty())
//    {
//        v   = new QRegExpValidator(p["phone"]);
//        int pos=0;
//        switch (v->validate(ui->Le_phone->text(),pos)) {
//        case v->Invalid:
//            qDebug()<<"Error phone";
//           // ui->Le_phone->setToolTip(tr("Error in phone."));
//            ui->Le_phone->setStyleSheet(s["error"]);
//            check = false;
//            break;
//        case v->Acceptable:
//            qDebug()<<"valide phone";
//           // ui->Le_phone->setToolTip(tr("Good Job"));
//            ui->Le_phone->setStyleSheet(s["accepted"]);
//            break;
//        case v->Intermediate:
//            qDebug()<<"phone not finished yet";
//           // ui->Le_phone->setToolTip(tr("Complete typing"));
//            ui->Le_phone->setStyleSheet(s["error"]);
//            check = false;
//            break;
//        default:
//            break;
//        }
//    }else
//    {
//        qDebug()<<"Last Name empty.";
//        ui->Le_phone->setStyleSheet(s["error"]);
//        check = false;
//    }

    if(emailCheck(ui->Le_email->text()))
    {
        v   = new QRegExpValidator(p["email"]);
        int pos=0;
        switch (v->validate(ui->Le_email->text(),pos)) {
        case v->Invalid:
            qDebug()<<"Error email";
            mToast = new Toast(this);
            mToast->show(tr("Invalide Em@il"),s["error_alert"]);
            ui->Le_email->setStyleSheet(s["error"]);
            check = false;
            break;
        case v->Acceptable:
            qDebug()<<"valide email";
            mToast = new Toast(this);
            mToast->show(tr("email verified"),s["accepted_alert"]);
            ui->Le_email->setStyleSheet(s["accepted"]);
            break;
        case v->Intermediate:
            qDebug()<<"email not finished yet";
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
        mToast = new Toast(this);
        mToast->show(tr("Em@il Already Used."),s["warning_alert"]);
        check = false;
    }

    if(usernameCheck(ui->Le_username->text()))
    {
        //ui->Le_username->setStyleSheet(s["accepted"]);
        v   = new QRegExpValidator(p["username"]);
        int pos=0;
        switch (v->validate(ui->Le_username->text(),pos)) {
        case v->Invalid:
            qDebug()<<"Error username";
           // ui->Le_username->setToolTip(tr("Error in username."));
            ui->Le_username->setStyleSheet(s["error"]);
            check = false;
            break;
        case v->Acceptable:
            qDebug()<<"valide username";
           // ui->Le_username->setToolTip(tr("Good Job"));
            ui->Le_username->setStyleSheet(s["accepted"]);
            break;
        case v->Intermediate:
            qDebug()<<"username not finished yet";
           // ui->Le_username->setToolTip(tr("Complete typing"));
            ui->Le_username->setStyleSheet(s["error"]);
            check = false;
            break;
        default:
            break;
        }
    }else
    {
        ui->Le_username->setStyleSheet(s["error"]);
        check = false;
    }

    if(passwordCheck(ui->Le_password->text(),ui->Le_confirmePass->text()))
    {
        v   = new QRegExpValidator(p["password"]);
        int pos=0;
        switch (v->validate(ui->Le_password->text(),pos)) {
        case v->Invalid:
            qDebug()<<"Error password";
            ui->Le_password->setToolTip(tr("respect the password norme"));
            ui->Le_password->setStyleSheet(s["error"]);
            ui->Le_confirmePass->setStyleSheet(s["error"]);
            check = false;
            break;
        case v->Acceptable:
            qDebug()<<"password verified";
            ui->Le_password->setToolTip(tr("Good Job"));
            ui->Le_password->setStyleSheet(s["accepted"]);
            ui->Le_confirmePass->setStyleSheet(s["accepted"]);
            break;
        case v->Intermediate:
            qDebug()<<"waiting...";
            ui->Le_password->setToolTip(tr("Complete typing"));
            ui->Le_password->setStyleSheet(s["error"]);
            ui->Le_confirmePass->setStyleSheet(s["error"]);
            check = false;
            break;
        default:
            break;
        }

    }else
    {
      qDebug()<<"Mis-Match passwords";
      ui->Le_password->setStyleSheet(s["error"]);
      ui->Le_confirmePass->setStyleSheet(s["error"]);
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
        int user_id = DB->addUser(ui->Le_firstName->text(), ui->Le_lastName->text(),ui->Le_username->text(),
                                  ui->Le_password->text(), ui->Le_email->text(), ui->Cb_gender->currentText(),
                                  ui->Cb_status->currentText(),group_id,company_id);
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
