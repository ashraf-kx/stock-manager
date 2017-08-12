#ifndef F_ADDQUOTATIONS_H
#define F_ADDQUOTATIONS_H

#include <QFrame>

namespace Ui {
class F_AddQuotations;
}

class F_AddQuotations : public QFrame
{
    Q_OBJECT

public:
    explicit F_AddQuotations(QWidget *parent = 0);
    ~F_AddQuotations();

private:
    Ui::F_AddQuotations *ui;
};

#endif // F_ADDQUOTATIONS_H
