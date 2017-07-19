#ifndef F_SYSTEMSETTINGS_H
#define F_SYSTEMSETTINGS_H

#include <QFrame>

namespace Ui {
class F_SystemSettings;
}

class F_SystemSettings : public QFrame
{
    Q_OBJECT

public:
    explicit F_SystemSettings(QWidget *parent = 0);
    ~F_SystemSettings();

private:
    Ui::F_SystemSettings *ui;
};

#endif // F_SYSTEMSETTINGS_H
