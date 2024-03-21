QT -= gui
QT += network
TEMPLATE = lib
DEFINES += EIREXE_LIBRARY
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
CONFIG += c++17

include(../libs.pri)
include(../../useBase.pri)
include(../../useCore.pri)

SOURCES += \
    BaseExecutable.cpp \
    BaseLogOutput.cpp \
    BaseLogUrl.cpp \
    CommandLine.cpp \
    ConsoleApplication.cpp \
    Context.cpp \
    FileLogOutput.cpp \
    FunctionInfo.cpp \
    LogItem.cpp \
    LogObject.cpp \
    Logger.cpp \
    OutputLogUrl.cpp \
    Setting.cpp \
    SettingProperty.cpp \
    Settings.cpp \
    SettingsScanner.cpp \
    TrollLogOutput.cpp \
    eIRexe.cpp

HEADERS += \
    BaseExecutable.h \
    BaseLogOutput.h \
    BaseLogUrl.h \
    CommandLine.h \
    ConsoleApplication.h \
    Context.h \
    FileLogOutput.h \
    FunctionInfo.h \
    Log.h \
    LogItem.h \
    LogMacros.h \
    LogObject.h \
    Logger.h \
    OutputLogUrl.h \
    Setting.h \
    SettingProperty.h \
    Settings.h \
    SettingsScanner.h \
    TrollLogOutput.h \
    eIRexe_global.h \
    eIRexe.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
