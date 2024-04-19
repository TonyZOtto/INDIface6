QT += gui
TEMPLATE = lib
DEFINES += EIRPHOTO_LIBRARY
CONFIG += c++17
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../libs.pri)
include(../../useCore.pri)

SOURCES += \
    BaseImage.cpp \
    ImageCache.cpp \
    eIRphoto.cpp

HEADERS += \
    BaseImage.h \
    ImageCache.h \
    eIRphoto_global.h \
    eIRphoto.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
