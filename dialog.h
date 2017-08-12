#ifndef DIALOG_H
#define DIALOG_H

#include <QtWidgets/QDialog>
#include <QGridLayout>
// QAnimate Framework
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QStateMachine>
#include <QState>
#include <QSignalTransition>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void setMessage(const QString &msg, const QString &typeM);
private:
    Ui::Dialog *ui;

    QStateMachine *machine;
    QState *stateShow;
    QState *stateHide;

    QPropertyAnimation *animSlideOut;
    QPropertyAnimation *animSlideIn;
};




#endif // DIALOG_H
