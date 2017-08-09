#ifndef TOAST_H
#define TOAST_H

#include <QFrame>
#include <QTimer>
#include <QGraphicsDropShadowEffect>
#include <QDebug>
// QAnimate Framework
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QStateMachine>
#include <QState>
#include <QSignalTransition>
#include <QTimer>

namespace Ui {
class Toast;
}

class Toast : public QFrame
{
    Q_OBJECT

public:
    explicit Toast(QWidget *parent = 0);
    void show(const QString& message, const QString &style);
    ~Toast();

public slots:
    void slideInStart();
private:
    Ui::Toast *ui;

    QStateMachine *machine;
    QState *stateShow;
    QState *stateHide;

    QPropertyAnimation *animSlideOut;
    QPropertyAnimation *animSlideIn;
};

#endif // TOAST_H
