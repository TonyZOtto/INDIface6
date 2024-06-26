# {Eclipse6}/src/useIfCore.pri
include(DESTDIR.pri)
INCLUDEPATH *= $$LIBDIR/IfCore
LIBS *= -lIfCore6
LIBS *= -L$$DESTDIR
message(--------/src/useIfCore.pri LIBS=$$LIBS)
message(INCLUDEPATH = $$INCLUDEPATH)


