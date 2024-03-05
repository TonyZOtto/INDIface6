QT -= gui
TEMPLATE = lib
DEFINES += EIRCORE_LIBRARY
CONFIG += c++17
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../libs.pri)

SOURCES += \
    ObjectHelper.cpp \
    QQFileInfo.cpp \
    eIRcore.cpp

HEADERS += \
    ObjectHelper.h \
    QQFileInfo.h \
    eIRcore_global.h \
    eIRcore.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
