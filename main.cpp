#include "dashboard.h"
#include <QApplication>
#include <QTranslator>
#include <QDebug>

using namespace std;

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(icons);
    Q_INIT_RESOURCE(styles);
    Q_INIT_RESOURCE(languages);

    QApplication a(argc, argv);

    QTranslator translator;
    translator.load(":StockManager_ar");
    a.installTranslator(&translator);

    Dashboard w;

    w.show();

    return a.exec();
}
