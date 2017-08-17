#ifndef F_POSSALES_H
#define F_POSSALES_H

#include <QFrame>

namespace Ui {
class F_POSSales;
}

class F_POSSales : public QFrame
{
    Q_OBJECT

public:
    explicit F_POSSales(QWidget *parent = 0);
    ~F_POSSales();

private:
    Ui::F_POSSales *ui;
};

#endif // F_POSSALES_H
