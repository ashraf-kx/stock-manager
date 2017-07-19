#ifndef CLASSES_H
#define CLASSES_H

#include <QObject>
#include <QtDebug>

//! [DB API linking ].
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>


using namespace sql;
using namespace std;

class Tables
{
public:
    Tables();
};

class Unit
{
private:
    int ID;
    QString sizeName;
    QString measurement;
public:
    explicit Unit(){ ID=-1; sizeName.clear(); measurement.clear(); }
    ~Unit();


    void setID(int ID){ this->ID = ID; }
    void setSizeName(const QString& sizeName){ this->sizeName = sizeName; }
    void setMeasurement(const QString& measurement){ this->measurement = measurement; }

    int getID(){ return this->ID; }
    QString getSizeName(){ return this->sizeName; }
    QString getMeasurement(){return this->measurement;}

};

class DB {
public:
    explicit DB();
    DB(const QString& hostName,const QString& userName,const QString& password,const QString& schemaName)
    {
        this->hostName   = hostName;
        this->userName   = userName;
        this->password   = password;
        this->schemaName = schemaName;
    }

    ~DB();

    Connection* getConnection()
    {
        try{
           this->mDriver      = get_driver_instance();
           this->mConnection  = this->mDriver->connect(this->hostName.toStdString(),
                                                       this->userName.toStdString(),
                                                       this->password.toStdString());
           this->mConnection->setAutoCommit(0);
           this->mConnection->setSchema(this->schemaName.toStdString());

           qDebug()<<"Connected to "<<this->schemaName<<"\n";

        }catch(SQLException &ex){
           std::cout<<"Exception Occurred > "<<ex.getErrorCode()<<endl;
        }
        return this->mConnection;
    }


private:
    Driver     *mDriver;
    Connection *mConnection;

    QString hostName;
    QString userName;
    QString password;
    QString schemaName;

};

class Cfg_Db {

public:
    explicit Cfg_Db(){
        driverName = "QMYSQL";
        hostname   = "localhost";
        username   = "root";
        password   = "";
        schemaName = "sma_db";
    }
    ~Cfg_Db();

    void setDriverName(const QString& val){ this->driverName = val; }
    void setHostname(const QString& val)  { this->hostname   = val; }
    void setUsername(const QString& val)  { this->username   = val; }
    void setPassword(const QString& val)  { this->password   = val; }
    void setSchemaName(const QString& val){ this->schemaName = val; }


    QString getDriverName(){ return this->driverName; }
    QString getHostname()  { return this->hostname;   }
    QString getUsername()  { return this->username;   }
    QString getPassword()  { return this->password;   }
    QString getSchemaName(){ return this->schemaName; }


    void setCfgDb(const QString& driverName,const QString& hostname,const QString& username,const QString& password,const QString& schemaName)
    {
        this->driverName = driverName;
        this->hostname   = hostname;
        this->username   = username;
        this->password   = password;
        this->schemaName = schemaName;
    }

private:
    QString driverName;
    QString hostname;
    QString username;
    QString password;
    QString schemaName;
};

#endif // CLASSES_H
