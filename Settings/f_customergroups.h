#ifndef F_CUSTOMERGROUPS_H
#define F_CUSTOMERGROUPS_H

#include <QFrame>

namespace Ui {
class F_CustomerGroups;
}

class F_CustomerGroups : public QFrame
{
    Q_OBJECT

public:
    explicit F_CustomerGroups(QWidget *parent = 0);
    ~F_CustomerGroups();

private:
    Ui::F_CustomerGroups *ui;
};

#endif // F_CUSTOMERGROUPS_H
