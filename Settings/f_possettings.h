#ifndef F_POSSETTINGS_H
#define F_POSSETTINGS_H

#include <QFrame>

namespace Ui {
class F_POSSettings;
}

class F_POSSettings : public QFrame
{
    Q_OBJECT

public:
    explicit F_POSSettings(QWidget *parent = 0);
    ~F_POSSettings();

private:
    Ui::F_POSSettings *ui;
};

#endif // F_POSSETTINGS_H
