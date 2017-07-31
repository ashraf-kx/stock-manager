#ifndef DBH_H
#define DBH_H

#include <QObject>

//! [DB QtSql ]
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSortFilterProxyModel>
#include <QCryptographicHash>
#include <QDateTime>

//! [ LOGGER ]
#include <QDebug>
#include <QtMessageHandler>
#include <QMessageLogger>
#include <QLoggingCategory>
#include <QDebugStateSaver>

class DBH : public QSqlDatabase
{

private:
    QString    connectionName;
    QSqlQuery *query;

public:
    DBH();
    DBH(const QString& name);

    void mTransaction();
    void mCommit();
    void mRemoveDatabase(const QString& connectionName);

     int getIDSupplierBy(const QString& fullname,int company_id);
     int getIDStateBy(const QString& name,int country_id);
     int getIDCityBy(const QString& name, int country_id);

     int addState(const QString& name,int country_id);
     int addCity(const QString& name, int country_id);
     int addAddress(const QString& name,const QString& postal_code, int city_id,int state_id);

public slots:
     QStringList getAllCompanies();
     QStringList getAllCountries();

     QStringList getAllStates(int country_id);
     QStringList getAllCities(int country_id);
     int getCountryID(const QString &name);
     int getCompanyID(const QString &name);
     int getCityID(const QString &name, int country_id);
     int getStateID(const QString &name, int country_id);
     int getCustomerEmail(const QString &email);
     int getPostalCodeID(int country_id);
     QMap<QString, QString> getPostalCodeMeta(int postal_code_id);
     int getSupplierEmail(const QString &email);
     int getSupplierID(const QString &fullname, int company_id);
     int addSupplier(const QString &fullname, const QString &email, const QString &phone, const QString &vtaNumber, int company_id, int address_id);
     int getUserEmail(const QString &email);
     QStringList getAllGroups();
     int getUserName(const QString &username); // check if the given username already used ;)
     int getGroupID(const QString &name);
     int addUser(const QString &firstname, const QString &lastname, const QString &username, const QString &password, const QString &email, const QString &gender, const QString &status, int group_id, int company_id);
};

#endif // DBH_H
