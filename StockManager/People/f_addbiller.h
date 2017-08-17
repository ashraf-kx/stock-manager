#ifndef F_ADDBILLER_H
#define F_ADDBILLER_H

#include <QFrame>

namespace Ui {
class F_AddBiller;
}

class F_AddBiller : public QFrame
{
    Q_OBJECT

public:
    explicit F_AddBiller(QWidget *parent = 0);
    ~F_AddBiller();

private:
    Ui::F_AddBiller *ui;
};

#endif // F_ADDBILLER_H
