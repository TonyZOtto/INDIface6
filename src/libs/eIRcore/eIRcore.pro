QT -= gui
TEMPLATE = lib
DEFINES += EIRCORE_LIBRARY
CONFIG += c++17
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../libs.pri)
include(../../useBase.pri)

SOURCES += \
    BaseCacheEntry.cpp \
    BaseCacheWorker.cpp \
    BaseUidCache.cpp \
    IODevice.cpp \
    MutexQueue.cpp \
    ObjectHelper.cpp \
    QQFileInfo.cpp \
    QQObject.cpp \
    eIRcore.cpp

HEADERS += \
    BaseCacheEntry.h \
    BaseCacheWorker.h \
    BaseUidCache.h \
    IODevice.h \
    MutexQueue.h \
    ObjectHelper.h \
    QQFileInfo.h \
    QQObject.h \
    eIRcore_global.h \
    eIRcore.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
