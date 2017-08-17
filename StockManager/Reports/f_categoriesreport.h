#ifndef F_CATEGORIESREPORT_H
#define F_CATEGORIESREPORT_H

#include <QFrame>

namespace Ui {
class F_CategoriesReport;
}

class F_CategoriesReport : public QFrame
{
    Q_OBJECT

public:
    explicit F_CategoriesReport(QWidget *parent = 0);
    ~F_CategoriesReport();

private:
    Ui::F_CategoriesReport *ui;
};

#endif // F_CATEGORIESREPORT_H
