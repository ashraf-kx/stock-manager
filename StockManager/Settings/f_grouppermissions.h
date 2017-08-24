#ifndef F_GROUPPERMISSIONS_H
#define F_GROUPPERMISSIONS_H

#include <QFrame>

namespace Ui {
class F_GroupPermissions;
}

class F_GroupPermissions : public QFrame
{
    Q_OBJECT

public:
    explicit F_GroupPermissions(QWidget *parent = 0);
    ~F_GroupPermissions();

private:
    Ui::F_GroupPermissions *ui;
};

#endif // F_GROUPPERMISSIONS_H
