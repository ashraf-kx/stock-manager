#include "dbh.h"

DBH::DBH()
{
    connectionName = ""; // this helps mtransacton & mCommit.

    QSqlDatabase::addDatabase("QMYSQL");
    QSqlDatabase::database().setDatabaseName("sma_db");
    QSqlDatabase::database().setHostName("127.0.0.1");
    QSqlDatabase::database().setPort(3306);
    QSqlDatabase::database().setUserName("root");
    QSqlDatabase::database().setPassword("");
    QSqlDatabase::database().open();

    query = new QSqlQuery(QSqlDatabase::database());
}

DBH::DBH(const QString &name)
    : connectionName(name)
{
    QSqlDatabase::addDatabase("QMYSQL",name);
    QSqlDatabase::database(name).setDatabaseName("sma_db");
    QSqlDatabase::database(name).setHostName("127.0.0.1");
    QSqlDatabase::database(name).setPort(3306);
    QSqlDatabase::database(name).setUserName("root");
    QSqlDatabase::database(name).setPassword("");
    QSqlDatabase::database(name).open();

    query = new QSqlQuery(QSqlDatabase::database(name));
}

void DBH::mTransaction()
{
    if(connectionName == "")
    {
        if(!QSqlDatabase::database().isOpen())
            QSqlDatabase::database().open();
        QSqlDatabase::database().transaction();
        query = new QSqlQuery(QSqlDatabase::database());
    }else
    {
        if(!QSqlDatabase::database(connectionName).isOpen())
            QSqlDatabase::database(connectionName).open();
        QSqlDatabase::database(connectionName).transaction();
        query = new QSqlQuery(QSqlDatabase::database(connectionName));
    }
}

void DBH::mCommit()
{
    if( connectionName == "")
        QSqlDatabase::database().commit();
    else
        QSqlDatabase::database(connectionName).commit();
}

void DBH::mRemoveDatabase(const QString& connectionName)
{
    QSqlDatabase::removeDatabase(connectionName);
}

int DBH::getSupplierID(const QString &fullname, int company_id)
{
    int supplier_id = -1;
    mTransaction();

    query->clear();
    query->prepare("SELECT `id` FROM `suppliers` WHERE `fullname`=:fullname AND `company_id`=:company_id");
    query->bindValue(":fullname",fullname);
    query->bindValue(":company_id", company_id);
    query->exec();
    if(query->next())
            supplier_id = query->value("id").toInt();

    mCommit();
    return supplier_id;
}

int DBH::getStateID(const QString &name, int country_id)
{
    int state_id= -1;
    mTransaction();

    query->clear();
    query->prepare("SELECT `id` FROM `states` WHERE `name`=:name AND `country_id`=:country_id");
    query->bindValue(":name", name);
    query->bindValue(":country_id", country_id);
    query->exec();

    if(query->next())
        state_id = query->value("id").toInt();

    mCommit();
    return state_id;
}

int DBH::addState(const QString &name, int country_id)
{
    int state_id = -1;
    mTransaction();

    query->clear();
    query->prepare("INSERT INTO `states` (`name`,`country_id`) VALUES (:name,:country_id)");
    query->bindValue(":name", name);
    query->bindValue(":country_id", country_id);
    if(query->exec())
        state_id = query->lastInsertId().toInt();

    mCommit();
    return state_id;
}

int DBH::addCity(const QString &name, int country_id)
{
    int city_id = -1;
    mTransaction();

    query->clear();
    query->prepare("INSERT INTO `cities` (`name_lang1`,`country_id`) VALUES (:name,:country_id)");
    query->bindValue(":name", name);
    query->bindValue(":country_id", country_id);
    if(query->exec())
        city_id = query->lastInsertId().toInt();

    mCommit();
    return city_id;
}

int DBH::addAddress(const QString &name, const QString &postal_code, int city_id, int state_id)
{
    int address_id = -1;
    mTransaction();

    if(state_id > 0 )
    {
        query->clear();
        query->prepare("INSERT INTO `addresses` (`name`,`postal_code`,`city_id`,`state_id`)"
                       "VALUES (:name,:postal_code,:city_id,:state_id)");
        query->bindValue(":name", name);
        query->bindValue(":postal_code", postal_code);
        query->bindValue(":city_id", city_id);
        query->bindValue(":state_id", state_id);
    }else
    {
        query->clear();
        query->prepare("INSERT INTO `addresses` (`name`,`postal_code`,`city_id`)"
                       "VALUES (:name,:postal_code,:city_id )");
        query->bindValue(":name", name);
        query->bindValue(":postal_code", postal_code);
        query->bindValue(":city_id", city_id);
    }

    if(query->exec())
        address_id = query->lastInsertId().toInt();

    mCommit();
    return address_id;
}

int DBH::addSupplier(const QString& fullname,const QString& email,const QString& phone,const QString& vtaNumber,int company_id,int address_id)
{
    int supplier_id = -1;
    mTransaction();

    query->clear();
    query->prepare("INSERT INTO `suppliers` (`fullname`,`email`,`phone`,`vat_number`,`company_id`,`address_id`) "
                   "VALUES(:fullname,:email,:phone,:vat_number,:company_id,:address_id)");

    query->bindValue(":fullname",fullname);
    query->bindValue(":email", email);
    query->bindValue(":phone", phone);
    query->bindValue(":vat_number", vtaNumber);
    query->bindValue(":company_id", company_id);
    query->bindValue(":address_id", address_id);
    query->exec();

    mCommit();
    return supplier_id;
}

QStringList DBH::getAllCompanies()
{
    QStringList tmpList;
    mTransaction();

    query->clear();
    query->prepare("SELECT `name` FROM `companies`");
    query->exec();

    tmpList.clear();

    while(query->next()){
        if(!query->value("name").toString().isEmpty())
            tmpList<<query->value("name").toString();
    }

    mCommit();
    return tmpList;
}

QStringList DBH::getAllCountries()
{
    QStringList tmpList;
    mTransaction();

    query->clear();
    query->prepare("SELECT `name` FROM `countries`");
    query->exec();

    tmpList.clear();

    while(query->next()){
        if(!query->value("name").toString().isEmpty())
            tmpList<<query->value("name").toString();
    }

    mCommit();
    return tmpList;
}

QStringList DBH::getAllStates(int country_id)
{
    QStringList tmpList;
    mTransaction();

    query->clear();
    query->prepare("SELECT `name` FROM `states` WHERE `country_id`=:country_id ");
    query->bindValue(":country_id",country_id);
    query->exec();

    tmpList.clear();

    while(query->next()){
        if(!query->value("name").toString().isEmpty())
            tmpList<<query->value("name").toString();
    }

    mCommit();
    return tmpList;
}

QStringList DBH::getAllCities(int country_id)
{
    QStringList tmpList;
    mTransaction();

    query->clear();
    query->prepare("SELECT `name_lang1` FROM `cities` WHERE `country_id`=:country_id ");
    query->bindValue(":country_id",country_id);
    query->exec();

    tmpList.clear();

    while(query->next()){
        if(!query->value("name_lang1").toString().isEmpty())
            tmpList<<query->value("name_lang1").toString();
    }

    mCommit();
    return tmpList;
}

int DBH::getCountryID(const QString &name)
{
    int country_id=0;
    mTransaction();

    query->clear();
    query->prepare("SELECT `id` FROM `countries` WHERE `name`=:name");
    query->bindValue(":name",name);
    query->exec();

    if(query->next()){
        country_id = query->value("id").toInt();
    }

    mCommit();
    return country_id;
}

int DBH::getCompanyID(const QString &name)
{
    int company_id = 0;
    mTransaction();

    query->clear();
    query->prepare("SELECT `id` FROM `companies` WHERE `name`=:name");
    query->bindValue(":name",name);
    query->exec();

    if(query->next()){
        company_id = query->value("id").toInt();
    }

    mCommit();
    return company_id;
}

int DBH::getCityID(const QString& name,int country_id)
{
    int city_id = 0;
    mTransaction();

    query->clear();
    query->prepare("SELECT `id` FROM `cities` WHERE `name_lang1`=:name AND `country_id`=:country_id");
    query->bindValue(":name",name);
    query->bindValue(":country_id",country_id);
    query->exec();

    if(query->next()){
        city_id = query->value("id").toInt();
    }

    mCommit();
    return city_id;
}

int DBH::getCustomerEmail(const QString& email)
{
    int email_id = -1;
    mTransaction();

    query->clear();
    query->prepare("SELECT `id` FROM `customers` WHERE `email`=:email");
    query->bindValue(":email",email);
    query->exec();

    if(query->next())
       email_id = query->value("id") .toInt();

    mCommit();
    return email_id;
}

int DBH::getSupplierEmail(const QString& email)
{
    int email_id = -1;
    mTransaction();

    query->clear();
    query->prepare("SELECT `id` FROM `suppliers` WHERE `email`=:email");
    query->bindValue(":email",email);
    query->exec();

    if(query->next())
        email_id = query->value("id").toInt();

    mCommit();
    return email_id;
}

int DBH::getPostalCodeID(int country_id)
{
    int code_id =-1;
    mTransaction();

    query->clear();
    query->prepare("SELECT `postal_code_id` FROM `countries` WHERE `id`=:id");
    query->bindValue(":id",country_id);
    query->exec();

    if(query->next()){
        code_id = query->value("postal_code_id").toInt();
    }

    mCommit();
    return code_id;
}

QMap<QString, QString> DBH::getPostalCodeMeta(int postal_code_id)
{
    QMap<QString, QString> row;
    row.clear();
    mTransaction();

    query->clear();
    query->prepare("SELECT `format`,`regex` FROM `postal_codes` WHERE `id`=:id");
    query->bindValue(":id",postal_code_id);
    query->exec();

    if(query->next()){
        row["regex"]    = query->value("regex").toString();
        row["format"] = query->value("format").toString();
    }

    mCommit();
    return row;
}

int DBH::getUserEmail(const QString& email)
{
    int email_id = -1;
    mTransaction();

    query->clear();
    query->prepare("SELECT `id` FROM `users` WHERE `email`=:email");
    query->bindValue(":email",email);
    query->exec();

    if(query->next())
        email_id = query->value("id").toInt();

    mCommit();
    return email_id;
}

QStringList DBH::getAllGroups()
{
    QStringList tmpList;
    tmpList.clear();
    mTransaction();

    query->clear();
    query->prepare("SELECT `name` FROM `groups`");
    query->exec();

    while(query->next()){
        if(!query->value("name").toString().isEmpty())
            tmpList<<query->value("name").toString();
    }

    mCommit();
    return tmpList;
}

int DBH::getUserName(const QString& username)
{
    int user_id = -1;
    mTransaction();

    query->clear();
    query->prepare("SELECT `id` FROM `users` WHERE `username`=:username");
    query->bindValue(":username",username);
    query->exec();

    while(query->next())
        user_id = query->value("id").toInt();

    mCommit();
    return user_id;
}

int DBH::getGroupID(const QString& name)
{
    int group_id = -1;
    mTransaction();

    query->clear();
    query->prepare("SELECT `id` FROM `groups` WHERE `name`=:name");
    query->bindValue(":name",name);
    query->exec();

    if(query->next())
            group_id = query->value("id").toInt();

    mCommit();
    return group_id;
}

int DBH::addUser(const QString& firstname,const QString& lastname,const QString& username,
                 const QString& password,const QString& email,const QString& gender,
                 const QString& status,int group_id,int company_id)
{
    int user_id = -1;
    mTransaction();

    query->clear();
    query->prepare("INSERT INTO `users` "
                   "(`first_name`,`last_name`,`username`,`password`,`email`,"
                   "`gendre`,`active`,`created_on`,`group_id`,`company_id`)"
                   " VALUES (:first_name,:last_name,:username,:password,:email,"
                   ":gendre,:active,:created_on,:group_id,:company_id)");

    query->bindValue(":first_name",firstname);
    query->bindValue(":last_name", lastname);
    query->bindValue(":username", username);
    // Crypting password Md5.
    QByteArray hashed;
    hashed = QCryptographicHash::hash(hashed.fromStdString(password.toStdString()),QCryptographicHash::Md5);

    query->bindValue(":password", QString(hashed.toHex()));
    query->bindValue(":email", email);
    query->bindValue(":gendre", gender);
    query->bindValue(":active", status);
    query->bindValue(":created_on", QDateTime::currentDateTime().toString(Qt::ISODate)); // TIME::now().tostring() Form BLABLA.
    query->bindValue(":group_id", group_id);
    query->bindValue(":company_id", company_id);
    query->exec();

    mCommit();
    return user_id;
}
