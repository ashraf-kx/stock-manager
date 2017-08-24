INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/camera.h \
    $$PWD/imagesettings.h \
    $$PWD/displayframesurface.h \
    $$PWD/displaywidget.h

SOURCES += \
    $$PWD/camera.cpp \
    $$PWD/imagesettings.cpp \
    $$PWD/displayframesurface.cpp \
    $$PWD/displaywidget.cpp

FORMS += \
    $$PWD/camera.ui \
    $$PWD/imagesettings.ui

#RESOURCES += \
#    $$PWD/iconsCamera.qrc \
#    $$PWD/soundsCamera.qrc

include(QZXing/QZXing.pri)
