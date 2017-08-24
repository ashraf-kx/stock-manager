#ifndef TOP_NAVIGATOR_H
#define TOP_NAVIGATOR_H

#include <QFrame>
#include "classes.h"
#include <QGraphicsDropShadowEffect>

namespace Ui {
class Top_navigator;
}

class Top_navigator : public QFrame
{
    Q_OBJECT

public:
    explicit Top_navigator(QWidget *parent = 0);
    ~Top_navigator();

    QPushButton *getBtToolBox();
public slots:
    void updateInfo();
    void changeIcon();
private:
    Ui::Top_navigator *ui;
    bool isToolBoxVisible;
};

#endif // TOP_NAVIGATOR_H
