QT *= core
QT *= sql # Because Log has QSqlRecord output; can eliminate if not using?``
CONFIG += cmdline
CONFIG += c++17

include(../console.pri)
include(../../useBase.pri)
include(../../useCore.pri)
include(../../useExe.pri)
include(../../useIfCore.pri)

SOURCES += \
        IfConsoleApp.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../../version.h \
    IfConsoleApp.h \
    version.h
