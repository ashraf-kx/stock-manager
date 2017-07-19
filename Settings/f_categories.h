#ifndef F_CATEGORIES_H
#define F_CATEGORIES_H

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
#include <QtWidgets/QDataWidgetMapper>

namespace Ui {
class F_Categories;
}

class F_Categories : public QFrame
{
    Q_OBJECT

public:
    explicit F_Categories(QWidget *parent = 0);
    ~F_Categories();

    void createMapper();
    void createMapperSub();
    void keyPressEvent(QKeyEvent *e) override;


public slots:
    void addCategory();
    void addSubCategory();

    void deleteCategory();
    void deleteSubCategory();

    void updateCategoriesCombo();
private:
    Ui::F_Categories *ui;

    Toast *mToast;

    Cfg_Db *mCfgDb;
    QSqlDatabase DBH;

    QSqlTableModel        *modelCategory;
    QDataWidgetMapper     *mapper;
    QSortFilterProxyModel *proxyModelCategory;

    QSqlTableModel        *modelSubCategory;
    QDataWidgetMapper     *mapperSub;
    QSortFilterProxyModel *proxyModelSubCategory;
};

#endif // F_CATEGORIES_H
