QT -= gui
TEMPLATE = lib
DEFINES += EIRBASE_LIBRARY
CONFIG += c++17

include(../libs.pri)

SOURCES += \
    AText.cpp \
    Key.cpp \
    KeyMap.cpp \
    KeySeg.cpp \
    KeySegList.cpp \
    Uid.cpp \
    VersionInfo.cpp \
    eirBase.cpp

HEADERS += \
    AText.h \
    Key.h \
    KeyMap.h \
    KeySeg.h \
    KeySegList.h \
    Types.h \
    Uid.h \
    VersionInfo.h \
    eirBase_global.h \
    eirBase.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
