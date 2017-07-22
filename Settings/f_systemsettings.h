#ifndef F_SYSTEMSETTINGS_H
#define F_SYSTEMSETTINGS_H

#include <QFrame>
#include "../classes.h"
#include "../toast.h"
#include <QGraphicsDropShadowEffect>
#include <QEvent>
#include <QKeyEvent>

//! [DB QtSql ]
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSortFilterProxyModel>

namespace Ui {
class F_SystemSettings;
}

class F_SystemSettings : public QFrame
{
    Q_OBJECT

public:
    explicit F_SystemSettings(QWidget *parent = 0);
    ~F_SystemSettings();

public slots:
    void getLines();
    QStringList getAllCountries();

    void getISO();
    void getISO3();
    void getISO_Numeric();
    void getFips();
    void getCountry();
    void getCapital();
    QString getArea();
    QString getPopulation();
    QString getContinent();
    QString getTld();
    QString getCurrencyCode();
    QString getCurrencyName();
    QString getPhone();
    QString getPostal_Code_Format();
    QString getPostal_Code_Regex();
    QString getLanguages();
    QString getGeonameid();
    QString getNeighbours();
    QString getEquivalentFipsCode();
    void getRest();
    void getSplitOneLine();
private:
    Ui::F_SystemSettings *ui;
    Toast *mToast;

    Cfg_Db *mCfgDb;
    QSqlDatabase DBH;

    QStringList mainList;
    QStringList listCountries;


};

#endif // F_SYSTEMSETTINGS_H
