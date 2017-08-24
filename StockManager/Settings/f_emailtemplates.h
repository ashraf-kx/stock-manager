#ifndef F_EMAILTEMPLATES_H
#define F_EMAILTEMPLATES_H

#include <QFrame>

namespace Ui {
class F_EmailTemplates;
}

class F_EmailTemplates : public QFrame
{
    Q_OBJECT

public:
    explicit F_EmailTemplates(QWidget *parent = 0);
    ~F_EmailTemplates();

private:
    Ui::F_EmailTemplates *ui;
};

#endif // F_EMAILTEMPLATES_H
