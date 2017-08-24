#! [0]
QT       += widgets uiplugin
#! [0]
CONFIG   += c++11

CONFIG(debug, debug|release) {
    DESTDIR = debug
} else {
    DESTDIR = designer
}

QTDIR_build {
# This is only for the Qt build. Do not use externally. We mean it.
PLUGIN_TYPE = designer
PLUGIN_CLASS_NAME = MDLineEditPlugin
load(qt_plugin)
CONFIG += install_ok
} else {
# Public example:

#! [2]
CONFIG      += plugin
TEMPLATE    = lib

#! [2]

TARGET = $$qtLibraryTarget($$TARGET)

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target

}

#! [3]
HEADERS      = mdlineeditplugin.h
SOURCES      = mdlineeditplugin.cpp
OTHER_FILES += mdlineedit.json
#! [3]

include(mdlineedit.pri)
RESOURCES += \
    icons.qrc

SUBDIRS += \
    MDLineEdit \
