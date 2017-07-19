#include "dashboard.h"
#include <QApplication>
#include <QTranslator>
#include <QtSql>
#include <QDebug>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(icons);
    Q_INIT_RESOURCE(styles);
    Q_INIT_RESOURCE(languages);

    QApplication a(argc, argv);

    QTranslator translator;
    translator.load(":StockManager_ar");
    a.installTranslator(&translator);

    /*QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","sunShine");
    db.setHostName("localhost");
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("");
    bool ok = db.open();
    if(ok) qDebug() << "ok";
    else qDebug() << "no";*/

    Dashboard w;

    w.show();

    return a.exec();
}
