#ifndef F_CATEGORIES_H
#define F_CATEGORIES_H

#include <QFrame>
#include "../classes.h"

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
    DBH *DB;

    QSqlTableModel        *modelCategory;
    QDataWidgetMapper     *mapper;
    QSortFilterProxyModel *proxyModelCategory;

    QSqlTableModel        *modelSubCategory;
    QDataWidgetMapper     *mapperSub;
    QSortFilterProxyModel *proxyModelSubCategory;
};

#endif // F_CATEGORIES_H
