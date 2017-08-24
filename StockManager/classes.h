#ifndef CLASSES_H
#define CLASSES_H

#include <QObject>

#include <QValidator>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QByteArray>

#include "toast.h"
#include "dialog.h"
#include <QGraphicsDropShadowEffect>
#include <QEvent>
#include <QKeyEvent>
#include <QCryptographicHash>

//! [DB QtSql ]
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSortFilterProxyModel>
#include <QtWidgets/QDataWidgetMapper>
#include <QCompleter>

//! [ LOGGER ]
#include <QDebug>
#include <QtMessageHandler>
#include <QMessageLogger>
#include <QLoggingCategory>
#include <QDebugStateSaver>

//! [ Custom DBH ]
#include "dbh.h"

//! [ Sound Effects ]
#include <QtMultimedia/QSound>

//! [ Qmd Gui ]
#include <mdlineedit.h>

class Cfg_Db {

public:
    explicit Cfg_Db(){
        driverName = "QMYSQL";
        hostname   = "localhost";
        username   = "root";
        password   = "root";
        schemaName = "sma_db";
        port       = 3306;
    }
    ~Cfg_Db();

    void setDriverName(const QString& val){ this->driverName = val; }
    void setHostname(const QString& val)  { this->hostname   = val; }
    void setUsername(const QString& val)  { this->username   = val; }
    void setPassword(const QString& val)  { this->password   = val; }
    void setSchemaName(const QString& val){ this->schemaName = val; }
    void setPort(int val){ this->port = val; }


    QString getDriverName(){ return this->driverName; }
    QString getHostname()  { return this->hostname;   }
    QString getUsername()  { return this->username;   }
    QString getPassword()  { return this->password;   }
    QString getSchemaName(){ return this->schemaName; }
    uint getPort()      { return this->port; }


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
    int     port;
};

class Patterns
{

public:
    explicit Patterns(){
        // We Need To Run Tests On Them All.
        pattern["firstname"] = QRegExp("^[a-z ,.'-]+$"); // UpVoted [111]
        pattern["lastname"]  = QRegExp("^[a-z ,.'-]+$");
        pattern["username"]  = QRegExp("^(?!.*[-_]{2,})(?=^[^-_].*[^-_]$)[\\w\\s-]{3,9}$"); // UpVoted 2
        pattern["phone"]     = QRegExp("^(?:(?:\\+?1\\s*(?:[.-]\\s*)?)?(?:\\(\\s*([2-9]1[02-9]|[2-9][02-8]1|[2-9][02-8][02-9])\\s*\\)|([2-9]1[02-9]|[2-9][02-8]1|[2-9][02-8][02-9]))\\s*(?:[.-]\\s*)?)?([2-9]1[02-9]|[2-9][02-9]1|[2-9][02-9]{2})\\s*(?:[.-]\\s*)?([0-9]{4})(?:\\s*(?:#|x\\.?|ext\\.?|extension)\\s*(\\d+))?$");
        pattern["password"]  = QRegExp("(?=.*\\d)(?=.*[a-z])(?=.*[A-Z]).{8,}");
        pattern["email"]     = QRegExp("[a-z0-9._%+-]+@[a-z0-9.-]+\\.[a-z]{2,3}$");
        pattern["search"]    = QRegExp("[^'\x22]+");
    }

    QRegExp operator[](const QString &index)
    {
        if(!index.isEmpty() && pattern.keys().contains(index))
            return pattern[index];
        else
            return QRegExp("");
    }

private:
    QMap<QString,QRegExp> pattern;
};

class ActionsStyle
{
public:
    explicit ActionsStyle(){
        //######## Text Color ##########
        style["info"]     = setColor("#40c4ff");
        style["warning"]  = setColor("#ffeb3b");
        style["error"]    = setColor("#d50000");
        style["danger"]   = setColor("#f44336");
        style["accepted"] = setColor("#00e676");
        //style["valide"]   = setColor("");
        style["black"]    = setColor("#000000");
        style["white"]    = setColor("#ffffff");

        //######## Alerts Color ##########
//        style["info_alert"]     = setAlertColors("#80d8ff","#40c4ff");
//        style["warning_alert"]  = setAlertColors("#fff9c4","#ffeb3b");
//        style["error_alert"]    = setAlertColors("#ff5722","#d50000");
//        style["danger_alert"]   = setAlertColors("#ff5722","#f44336");
//        style["accepted_alert"] = setAlertColors("#b2ff59","#00e676");
        style["black_alert"]    = setAlertColors("#000000","#ffffff");
        style["white_alert"]    = setAlertColors("#ffffff","#000000");

        style["info_alert"]     = setAlertColors("#80d8ff","#ffffff");
        style["warning_alert"]  = setAlertColors("#fff9c4","#ffffff");
        style["error_alert"]    = setAlertColors("#ff5722","#ffffff");
        style["danger_alert"]   = setAlertColors("#ff5722","#ffffff");
        style["accepted_alert"] = setAlertColors("#b2ff59","#ffffff");
    }

    QString operator[](const QString &index)
    {
        if(!index.isEmpty() && style.keys().contains(index))
            return style[index];
        else
            return ("");
    }

    QString setAlertColors(const QString& colorWidget,const QString& colorFont)
    {
        return ("border:1px solid "+colorWidget+";"
                "background-color:"+colorWidget+";"
                "color:"+colorFont+";");
    }

    QString setColor(const QString& color)
    {
        return ("color:"+color+";");
    }

private:
    QMap<QString,QString> style;
};

class Style
{
public:

    explicit Style();
    static QString loadStyle(const QString& file)
    {
        QFile MDFile(":"+file);
        if (MDFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&MDFile);
            return in.readAll().simplified();
        }
        return "";
    }

    static QGraphicsDropShadowEffect *shadowbutton()
    {
        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
        shadow->setBlurRadius(8);
        shadow->setOffset(1);
        shadow->setColor(QColor(63, 63, 63, 180));
        return shadow;
    }

    static QGraphicsDropShadowEffect *shadow()
    {
        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
        shadow->setBlurRadius(8);
        shadow->setOffset(3);
        shadow->setColor(QColor(63, 63, 63, 180));
        return shadow;
    }
};

#endif // CLASSES_H
