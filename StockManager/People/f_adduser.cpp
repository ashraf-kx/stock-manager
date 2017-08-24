#include "f_adduser.h"

F_AddUser::F_AddUser(QWidget *parent) :
    QFrame(parent)
{
    QTime t;
    t.start();

    setupUi(this);

    this->setStyleSheet(Style::loadStyle("addUser"));
    //this->setGraphicsEffect(Style::shadow());

//    QFont f = QFont();
//    f.setPointSizeF(15);
//    this->setFont(f);

    //########### Connect To Database ###################
    mCfgDb = new Cfg_Db();
    DB = new DBH("_addUser_");

    //############ Assign Completers ####################
    initCompanyCombo();
    initGroupCombo();

//    Cb_company->setGraphicsEffect(Style::shadowbutton());
//    Cb_gender->setGraphicsEffect(Style::shadow());
//    Cb_group->setGraphicsEffect(Style::shadow());
//    Cb_status->setGraphicsEffect(Style::shadow());


    W_password->getLineEdit()->setEchoMode(QLineEdit::Password);
    W_confirmePass->getLineEdit()->setEchoMode(QLineEdit::Password);

    Bt_addUser->raise();

    Bt_addUser->setGraphicsEffect(Style::shadowbutton());
    connect(W_password->getRightBtn(),SIGNAL(pressed()),this,SLOT(showPassword()));
    connect(W_password->getRightBtn(),SIGNAL(released()),this,SLOT(hidePassword()));

    //########## Connectors Signal ~> slots #############
    connect(Bt_addUser,SIGNAL(clicked(bool)),this,SLOT(addUser()));

    initTabOrder();

    this->setStatusTip(tr("Time elapsed : ")+QString::number(t.elapsed())+" ms.");    
}

F_AddUser::~F_AddUser()
{
    #ifdef _WIN32
        DB->mRemoveDatabase("_addUser_");
    #endif
    // delete ui;
}

void F_AddUser::initTabOrder()
{
    this->setTabOrder(Cb_company,W_firstName);
    this->setTabOrder(W_firstName,W_lastName);
    this->setTabOrder(W_lastName,Cb_gender);
    this->setTabOrder(Cb_gender,W_phone);
}

void F_AddUser::showPassword()
{
    W_password->getLineEdit()->setEchoMode(QLineEdit::Normal);
}

void F_AddUser::hidePassword()
{
    W_password->getLineEdit()->setEchoMode(QLineEdit::Password);
}

void F_AddUser::initCompanyCombo()
{
    listCompanies = DB->getAllCompanies();
    Cb_company->clear();
    Cb_company->addItem(tr("Select a Company"));
    Cb_company->addItems(listCompanies);
}

void F_AddUser::initGroupCombo()
{
    listGroups = DB->getAllGroups();
    Cb_group->clear();
    Cb_group->addItem(tr("Select User Group"));
    Cb_group->addItems(listGroups);
}

bool F_AddUser::inputsVerification()
{
    // Entries Verification
    bool check = true;
//    if(!W_firstName->text().isEmpty())
//    {
//        v   = new QRegExpValidator(p["firstname"]);
//        int pos=0;
//        switch (v->validate(W_firstName->text(),pos)) {
//        case v->Invalid:
//            qDebug()<<"Error firstName";
//           // W_firstName->setToolTip(tr("Error in firstName."));
//            W_firstName->setStyleSheet(s["error"]);
//            check = false;
//            break;
//        case v->Acceptable:
//            qDebug()<<"valide firstName";
//           // W_firstName->setToolTip(tr("Good Job"));
//            W_firstName->setStyleSheet(s["accepted"]);
//            break;
//        case v->Intermediate:
//            qDebug()<<"firstName not finished yet";
//           // W_firstName->setToolTip(tr("Complete typing"));
//            W_firstName->setStyleSheet(s["error"]);
//            check = false;
//            break;
//        default:
//            break;
//        }
//    }else
//    {
//        qDebug()<<"firstName empty.";
//        W_firstName->setStyleSheet(s["error"]);
//        check = false;
//    }

//    if(!W_lastName->text().isEmpty())
//    {
//        v   = new QRegExpValidator(p["lastname"]);
//        int pos=0;
//        switch (v->validate(W_lastName->text(),pos)) {
//        case v->Invalid:
//            qDebug()<<"Error lastName";
//           // W_lastName->setToolTip(tr("Error in lastName."));
//            W_lastName->setStyleSheet(s["error"]);
//            check = false;
//            break;
//        case v->Acceptable:
//            qDebug()<<"valide lastName";
//           // W_lastName->setToolTip(tr("Good Job"));
//            W_lastName->setStyleSheet(s["accepted"]);
//            break;
//        case v->Intermediate:
//            qDebug()<<"lastName not finished yet";
//           // W_lastName->setToolTip(tr("Complete typing"));
//            W_lastName->setStyleSheet(s["error"]);
//            check = false;
//            break;
//        default:
//            break;
//        }
//    }else
//    {
//        qDebug()<<"Last Name empty.";
//        W_lastName->setStyleSheet(s["error"]);
//        check = false;
//    }

//    if(!W_phone->text().isEmpty())
//    {
//        v   = new QRegExpValidator(p["phone"]);
//        int pos=0;
//        switch (v->validate(W_phone->text(),pos)) {
//        case v->Invalid:
//            qDebug()<<"Error phone";
//           // W_phone->setToolTip(tr("Error in phone."));
//            W_phone->setStyleSheet(s["error"]);
//            check = false;
//            break;
//        case v->Acceptable:
//            qDebug()<<"valide phone";
//           // W_phone->setToolTip(tr("Good Job"));
//            W_phone->setStyleSheet(s["accepted"]);
//            break;
//        case v->Intermediate:
//            qDebug()<<"phone not finished yet";
//           // W_phone->setToolTip(tr("Complete typing"));
//            W_phone->setStyleSheet(s["error"]);
//            check = false;
//            break;
//        default:
//            break;
//        }
//    }else
//    {
//        qDebug()<<"Last Name empty.";
//        W_phone->setStyleSheet(s["error"]);
//        check = false;
//    }
    //! [1] Company Verification (Done)
    if(!companyCheck(Cb_company->currentText()))
    {
        Cb_company->setStyleSheet("border-bottom: 2px solid #FF1744;");
        check = false;
    }else
    {
        Cb_company->setStyleSheet("border-bottom: 2px solid #0091EA;");
    }

    //! [2] First-Name Verification (Done)

    //! [3] Last-Name Verification (Done)

    //! [4] Gender Verification (Done)

    //! [5] Phone Verification (Done)

    //! [6] Email Verification (Done)
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

    //! [7] Username Verification (Done)
    if(usernameCheck(W_username->text()))
    {
        v   = new QRegExpValidator(p["username"]);
        int pos=0;
        QString tmp_str = W_username->text();
        switch (v->validate(tmp_str,pos)) {
        case QValidator::Invalid:
            qDebug()<<"Error username";
            W_username->getHelper()->setVisible(true);
            W_username->parseError("Only Letters, numbers and (_, -)");
            check = false;
            break;
        case QValidator::Acceptable:
            qDebug()<<"valide username";
            W_username->getHelper()->setVisible(false);
            break;
        case QValidator::Intermediate:
            W_username->getHelper()->setVisible(true);
            W_username->parseError("Only Letters, numbers and (_, -)");
            check = false;
            break;
        default:
            break;
        }
    }else
    {
        check = false;
    }

    //! [8~9] Password Verification (Done)
    if(!W_password->text().isEmpty())
    {
        v   = new QRegExpValidator(p["password"]);
        int pos=0;
        QString tmp_str = W_password->text();
        switch (v->validate(tmp_str,pos)) {
        case QValidator::Invalid:
            W_password->getHelper()->setVisible(true);
            W_password->parseError("");
            check = false;
            break;
        case QValidator::Acceptable:
            W_password->getHelper()->setVisible(false);
            check = true;
            break;
        case QValidator::Intermediate:
            W_password->getHelper()->setVisible(true);
            W_password->parseError("");
            check = false;
            break;
        default:
            break;
        }
        if(check)
        {
            if(passwordCheck(W_password->text(),W_confirmePass->text()))
            {
                W_confirmePass->setHelperText("");
                W_confirmePass->getHelper()->setVisible(false);
            }else
            {
              W_confirmePass->getHelper()->setVisible(true);
              W_confirmePass->parseError("MisMatch Passwords");
              check = false;
            }
        }
    }

    //! [10] Status Verification (Done)
    if(!statusCheck(Cb_status->currentText()))
    {
        Cb_status->setStyleSheet("border-bottom: 2px solid #FF1744;");
        check = false;
    }else
    {
        Cb_status->setStyleSheet("border-bottom: 2px solid #0091EA;");
    }

    //! [11] Group Verification (Done)
    if(!groupCheck(Cb_group->currentText()))
    {
        Cb_group->setStyleSheet("border-bottom: 2px solid #FF1744;");
        check = false;
    }else
    {
        Cb_group->setStyleSheet("border-bottom: 2px solid #0091EA;");
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

        company_id  = DB->getCompanyID(Cb_company->currentText());
        group_id    = DB->getGroupID(Cb_group->currentText());
        DB->addUser(W_firstName->text(),
                    W_lastName->text(),
                    W_username->text(),
                    W_password->text(),
                    W_email->text(),
                    Cb_gender->currentText(),
                    Cb_status->currentText(),
                    group_id,company_id);

        clearInputs();
    }
    Bt_addUser->setEnabled(true);
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

bool F_AddUser::statusCheck(const QString& status)
{
    if(status == tr("Status"))
        return false;
    else
        return true;
}

bool F_AddUser::companyCheck(const QString& company)
{
    if(company == tr("Select a Company"))
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
        Le->clear();
    }
    Cb_gender->setCurrentIndex(0);
    Cb_company->setCurrentIndex(0);
    Cb_status->setCurrentIndex(0);
    Cb_group->setCurrentIndex(0);
}
