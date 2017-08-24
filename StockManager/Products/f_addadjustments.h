#ifndef F_ADDADJUSTMENTS_H
#define F_ADDADJUSTMENTS_H

#include <QFrame>

namespace Ui {
class F_AddAdjustments;
}

class F_AddAdjustments : public QFrame
{
    Q_OBJECT

public:
    explicit F_AddAdjustments(QWidget *parent = 0);
    ~F_AddAdjustments();

private:
    Ui::F_AddAdjustments *ui;
};

#endif // F_ADDADJUSTMENTS_H
