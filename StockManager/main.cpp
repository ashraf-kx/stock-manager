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

// TODO (1): Use DMLineEdit On the Total Widgets of the App [ 15/0 ].
// TODO (2): Complete AddCustomer Filling the GUI with data ( Group Price & ...)
// TODO (4) : SubProject>> Project [ Implement the Technique Plugins ].
// FIXME (5) : Fix Problem summon FrameAddSupplier (inputs size & style ..).
// NOTE (6) : Animate ToolBox (slideIn & Out)
// TODO (X) : Recieve Code-Bar From Phone, And display it Form Add Products.
