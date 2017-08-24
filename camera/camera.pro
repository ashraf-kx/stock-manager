TEMPLATE = app
TARGET   = camera

CONFIG += C++11

QT     += multimedia multimediawidgets core widgets gui

#HEADERS += \
#    camera.h \
#    imagesettings.h \
#    displayframesurface.h \
#    displaywidget.h

#SOURCES += \
#    main.cpp \
#    camera.cpp \
#    imagesettings.cpp \
#    displayframesurface.cpp \
#    displaywidget.cpp

#FORMS += \
#    camera.ui \
#    imagesettings.ui

target.path = $$[QT_INSTALL_EXAMPLES]/multimediawidgets/camera
INSTALLS += target

include(camera.pri)

RESOURCES += \
    sounds.qrc \
    icons.qrc
