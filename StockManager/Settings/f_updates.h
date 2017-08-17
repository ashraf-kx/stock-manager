#ifndef F_UPDATES_H
#define F_UPDATES_H

#include <QFrame>

namespace Ui {
class F_Updates;
}

class F_Updates : public QFrame
{
    Q_OBJECT

public:
    explicit F_Updates(QWidget *parent = 0);
    ~F_Updates();

private:
    Ui::F_Updates *ui;
};

#endif // F_UPDATES_H
