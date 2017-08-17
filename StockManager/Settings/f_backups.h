#ifndef F_BACKUPS_H
#define F_BACKUPS_H

#include <QFrame>

namespace Ui {
class F_BackUps;
}

class F_BackUps : public QFrame
{
    Q_OBJECT

public:
    explicit F_BackUps(QWidget *parent = 0);
    ~F_BackUps();

private:
    Ui::F_BackUps *ui;
};

#endif // F_BACKUPS_H
