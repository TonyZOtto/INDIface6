QT *= core
#CONFIG -= qt
TEMPLATE = lib
DEFINES += EIRLOG_LIBRARY
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
CONFIG += c++17

include(../libs.pri)

SOURCES += \
    Log.cpp \
    LogContext.cpp \
    LogFormat.cpp \
    LogFormatTxtFile.cpp \
    LogHeader.cpp \
    LogItem.cpp \
    LogOutput.cpp \
    LogOutputTroll.cpp \
    LogOutputTxtFile.cpp \
    Logger.cpp \
    eirLog.cpp

HEADERS += \
    Log.h \
    LogContext.h \
    LogFormat.h \
    LogFormatTxtFile.h \
    LogHeader.h \
    LogItem.h \
    LogOutput.h \
    LogOutputTroll.h \
    LogOutputTxtFile.h \
    Logger.h \
    eirLog_global.h \
    eirLog.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
