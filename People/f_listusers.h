#ifndef F_LISTUSERS_H
#define F_LISTUSERS_H

#include <QFrame>
#include <QHash>
#include "../classes.h"

Q_DECLARE_LOGGING_CATEGORY(PLU)

namespace Ui {
class F_ListUsers;
}

class F_ListUsers : public QFrame
{
    Q_OBJECT

public:
    explicit F_ListUsers(QWidget *parent = 0);
    ~F_ListUsers();

    void createMapper();
    void keyPressEvent(QKeyEvent *e) override;

public slots:
    void hideAllRows();
    void showAllRows();
    void showPageRows();
    void initListRowsPerPage();
    void initListNumberPages();
    void updateTableViewRows();
    void selectedColumn();
    void nextPage();
    void previousPage();
    void updateMessageInfo();
private:
    Ui::F_ListUsers *ui;
    Toast *mToast;

    Cfg_Db *mCfgDb;
    DBH *DB;

    QSqlTableModel        *modelUser;
    QSqlQueryModel        *queryModelUser;
    QDataWidgetMapper     *mapper;
    QSortFilterProxyModel *proxyModelUser;
    QHash<QString,int>    TA;
    int idxColSelected;
};

#endif // F_LISTUSERS_H
