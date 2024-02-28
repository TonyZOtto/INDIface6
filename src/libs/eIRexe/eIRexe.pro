QT -= gui
TEMPLATE = lib
DEFINES += EIREXE_LIBRARY
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
CONFIG += c++17

include(../libs.pri)

SOURCES += \
    BaseExecutable.cpp \
    CommandLine.cpp \
    ConsoleApplication.cpp \
    Log.cpp \
    Setting.cpp \
    SettingProperty.cpp \
    Settings.cpp \
    SettingsScanner.cpp \
    eIRexe.cpp

HEADERS += \
    BaseExecutable.h \
    CommandLine.h \
    ConsoleApplication.h \
    Log.h \
    Setting.h \
    SettingProperty.h \
    Settings.h \
    SettingsScanner.h \
    eIRexe_global.h \
    eIRexe.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
