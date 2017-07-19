#ifndef F_UNITS_H
#define F_UNITS_H

#include <QFrame>
#include "../classes.h"
#include "../toast.h"
#include <QGraphicsDropShadowEffect>
#include <QEvent>
#include <QKeyEvent>

//! [DB API linking ].
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

//! [DB QtSql ]
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSortFilterProxyModel>
#include <QtWidgets/QDataWidgetMapper>


using namespace sql;
using namespace std;

namespace Ui {
class F_Units;
}

class F_Units : public QFrame
{
    Q_OBJECT

public:
    explicit F_Units(QWidget *parent = 0);
    ~F_Units();

    void createMapper();
    void keyPressEvent(QKeyEvent *e) override;

public slots:
    void addUnit();
    void deleteUnit();
private:
    Ui::F_Units *ui;
    Toast *mToast;

    Cfg_Db *mCfgDb;
    QSqlDatabase DBH;

    QSqlTableModel        *modelUnit;
    QDataWidgetMapper     *mapper;
    QSortFilterProxyModel *proxyModelUnit;
};

#endif // F_UNITS_H
