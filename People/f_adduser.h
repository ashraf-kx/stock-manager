#ifndef F_ADDUSER_H
#define F_ADDUSER_H

#include <QFrame>
#include "../classes.h"


namespace Ui {
class F_AddUser;
}

class F_AddUser : public QFrame
{
    Q_OBJECT

public:
    explicit F_AddUser(QWidget *parent = 0);
    ~F_AddUser();

    bool emailCheck(const QString & email);
    bool usernameCheck(const QString& username);

    bool groupCheck(const QString &group);
    bool companyCheck(const QString &company);
    bool passwordCheck(const QString& password,const QString& Confirme);
    bool statusCheck(const QString &status);

public slots:
    void addUser();

    void clearInputs();

    bool inputsVerification();
    void initGroupCombo();
    void initCompanyCombo();

    void showPassword();
    void hidePassword();
private:
    Ui::F_AddUser *ui;
    Toast         *mToast;
    Cfg_Db        *mCfgDb;
    DBH           *DB;

    QStringList listCompanies;
    QStringList listGroups;

    QValidator  *v;
    Patterns     p;
    ActionsStyle s;

};

#endif // F_ADDUSER_H
