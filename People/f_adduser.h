#ifndef F_ADDUSER_H
#define F_ADDUSER_H

#include <QFrame>

namespace Ui {
class F_AddUser;
}

class F_AddUser : public QFrame
{
    Q_OBJECT

public:
    explicit F_AddUser(QWidget *parent = 0);
    ~F_AddUser();

private:
    Ui::F_AddUser *ui;
};

#endif // F_ADDUSER_H
