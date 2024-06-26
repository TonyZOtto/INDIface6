CONFIG -= qt
TEMPLATE = lib
DEFINES += EIRLOG_LIBRARY
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
CONFIG += c++17

include(../libs.pri)

SOURCES += \
    eirLog.cpp

HEADERS += \
    eirLog_global.h \
    eirLog.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
