#ifndef TOAST_H
#define TOAST_H

#include <QFrame>
#include <QTimer>

namespace Ui {
class Toast;
}

class Toast : public QFrame
{
    Q_OBJECT

public:
    explicit Toast(QWidget *parent = 0);
    ~Toast();

public slots:
    void fade();
    void setMessage(const QString &msg);
private:
    Ui::Toast *ui;
    QTimer *mTimer;
    int colorA;
};

#endif // TOAST_H
