# {Eclipse6}/src/useLog.pri
include(DESTDIR.pri)
INCLUDEPATH *= $$LIBDIR/eIRLog
LIBS *= -leIRLog6
LIBS *= -L$$DESTDIR
message(--------/src/useLog.pri LIBS=$$LIBS)
message(INCLUDEPATH = $$INCLUDEPATH)
message(LIBDIR = $$LIBDIR)


