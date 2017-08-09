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

    QApplication app(argc, argv);

    QTranslator translator;
    translator.load(":language_en");
    app.installTranslator(&translator);

    Dashboard w;

    w.show();

    return app.exec();
}
