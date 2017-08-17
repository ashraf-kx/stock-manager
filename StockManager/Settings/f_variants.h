#ifndef F_VARIANTS_H
#define F_VARIANTS_H

#include <QFrame>

namespace Ui {
class F_Variants;
}

class F_Variants : public QFrame
{
    Q_OBJECT

public:
    explicit F_Variants(QWidget *parent = 0);
    ~F_Variants();

private:
    Ui::F_Variants *ui;
};

#endif // F_VARIANTS_H
