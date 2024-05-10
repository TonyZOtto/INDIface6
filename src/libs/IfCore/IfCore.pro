QT += gui
TEMPLATE = lib
DEFINES += IFCORE_LIBRARY
CONFIG += c++17
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../libs.pri)
include(../../useBase.pri)
include(../../useCore.pri)
include(../../useExe.pri)

SOURCES += \
    BaseImage.cpp \
    ColorImage.cpp \
    EnumerateDirTask.cpp \
    FaceData.cpp \
    FrameData.cpp \
    IfCache.cpp \
    IfCore.cpp


HEADERS += \
    BaseImage.h \
    ColorImage.h \
    EnumerateDirTask.h \
    FaceData.h \
    FrameData.h \
    IfCache.h \
    IfCore_global.h \
    IfCore.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
