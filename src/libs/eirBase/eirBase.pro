QT -= gui
TEMPLATE = lib
DEFINES += EIRBASE_LIBRARY
CONFIG += c++17

include(../libs.pri)

SOURCES += \
    AText.cpp \
    Boolean.cpp \
    ErrorCode.cpp \
    Ident.cpp \
    Key.cpp \
    KeyMap.cpp \
    KeySeg.cpp \
    KeySegList.cpp \
    QQBitArray.cpp \
    Uid.cpp \
    UidPak.cpp \
    VersionInfo.cpp \
    eirBase.cpp

HEADERS += \
    AText.h \
    Boolean.h \
    ErrorCode.h \
    Ident.h \
    Key.h \
    KeyMap.h \
    KeySeg.h \
    KeySegList.h \
    QQBitArray.h \
    Types.h \
    Uid.h \
    UidPak.h \
    VersionInfo.h \
    eirBase_global.h \
    eirBase.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
