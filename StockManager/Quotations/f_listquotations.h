#ifndef F_LISTQUOTATIONS_H
#define F_LISTQUOTATIONS_H

#include <QFrame>

namespace Ui {
class F_ListQuotations;
}

class F_ListQuotations : public QFrame
{
    Q_OBJECT

public:
    explicit F_ListQuotations(QWidget *parent = 0);
    ~F_ListQuotations();

private:
    Ui::F_ListQuotations *ui;
};

#endif // F_LISTQUOTATIONS_H
