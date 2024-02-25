QT -= gui
TEMPLATE = lib
DEFINES += EIRBASE_LIBRARY
CONFIG += c++17

include(../libs.pri)

SOURCES += \
    AText.cpp \
    VersionInfo.cpp \
    eirBase.cpp

HEADERS += \
    AText.h \
    Types.h \
    VersionInfo.h \
    eirBase_global.h \
    eirBase.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
