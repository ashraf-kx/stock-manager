#ifndef F_LISTBILLERS_H
#define F_LISTBILLERS_H

#include <QFrame>

namespace Ui {
class F_ListBillers;
}

class F_ListBillers : public QFrame
{
    Q_OBJECT

public:
    explicit F_ListBillers(QWidget *parent = 0);
    ~F_ListBillers();

private:
    Ui::F_ListBillers *ui;
};

#endif // F_LISTBILLERS_H
