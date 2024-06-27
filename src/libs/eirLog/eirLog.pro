QT *= core
#CONFIG -= qt
TEMPLATE = lib
DEFINES += EIRLOG_LIBRARY
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
CONFIG += c++17

include(../libs.pri)

SOURCES += \
    ../../../ottoZcode/src/libs/ozLog/Log.cpp \
    ../../../ottoZcode/src/libs/ozLog/LogContext.cpp \
    ../../../ottoZcode/src/libs/ozLog/LogFormat.cpp \
    ../../../ottoZcode/src/libs/ozLog/LogFormatTxtFile.cpp \
    ../../../ottoZcode/src/libs/ozLog/LogFunctionInfo.cpp \
    ../../../ottoZcode/src/libs/ozLog/LogHeader.cpp \
    ../../../ottoZcode/src/libs/ozLog/LogItem.cpp \
    ../../../ottoZcode/src/libs/ozLog/LogOutput.cpp \
    ../../../ottoZcode/src/libs/ozLog/LogOutputTroll.cpp \
    ../../../ottoZcode/src/libs/ozLog/LogOutputTxtFile.cpp \
    ../../../ottoZcode/src/libs/ozLog/Logger.cpp \
    eirLog.cpp \

HEADERS += \
    ../../../ottoZcode/src/libs/ozLog/Log.h \
    ../../../ottoZcode/src/libs/ozLog/LogContext.h \
    ../../../ottoZcode/src/libs/ozLog/LogFormat.h \
    ../../../ottoZcode/src/libs/ozLog/LogFormatTxtFile.h \
    ../../../ottoZcode/src/libs/ozLog/LogFunctionInfo.h \
    ../../../ottoZcode/src/libs/ozLog/LogHeader.h \
    ../../../ottoZcode/src/libs/ozLog/LogItem.h \
    ../../../ottoZcode/src/libs/ozLog/LogOutput.h \
    ../../../ottoZcode/src/libs/ozLog/LogOutputTroll.h \
    ../../../ottoZcode/src/libs/ozLog/LogOutputTxtFile.h \
    ../../../ottoZcode/src/libs/ozLog/Logger.h \
    eirLog_global.h \
    eirLog.h \

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
