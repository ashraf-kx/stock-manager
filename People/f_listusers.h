#ifndef F_LISTUSERS_H
#define F_LISTUSERS_H

#include <QFrame>

namespace Ui {
class F_ListUsers;
}

class F_ListUsers : public QFrame
{
    Q_OBJECT

public:
    explicit F_ListUsers(QWidget *parent = 0);
    ~F_ListUsers();

private:
    Ui::F_ListUsers *ui;
};

#endif // F_LISTUSERS_H
