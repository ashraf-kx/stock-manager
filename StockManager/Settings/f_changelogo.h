#ifndef F_CHANGELOGO_H
#define F_CHANGELOGO_H

#include <QFrame>

namespace Ui {
class F_ChangeLogo;
}

class F_ChangeLogo : public QFrame
{
    Q_OBJECT

public:
    explicit F_ChangeLogo(QWidget *parent = 0);
    ~F_ChangeLogo();

private:
    Ui::F_ChangeLogo *ui;
};

#endif // F_CHANGELOGO_H
