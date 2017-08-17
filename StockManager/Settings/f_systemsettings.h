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
    void getArea();
    void getPopulation();
    void getContinent();
    void getTld();
    void getCurrencyCode();
    void getCurrencyName();
    void getPhone();
    void getPostal_Code_Format();
    bool getPostal_Code_Regex();
    void getLanguages();
    void getGeonameid();
    QString getNeighbours();
    QString getEquivalentFipsCode();
    void getSplitOneLine();
    void clearAllInputs();
    void getUsefullText();
private:
    Ui::F_SystemSettings *ui;
    Toast *mToast;

    Cfg_Db *mCfgDb;
    QSqlDatabase DBH;

    QStringList mainList;
    QStringList listCountries;

    QString textOut;


};

#endif // F_SYSTEMSETTINGS_H
