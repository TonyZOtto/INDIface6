# {Eclipse6}/src/useBase.pri
include(DESTDIR.pri)
INCLUDEPATH *= $$LIBDIR/eIRbase
LIBS *= -leIRbase6
LIBS *= -L$$DESTDIR
message(--------/src/useBase.pri LIBS=$$LIBS)
message(INCLUDEPATH = $$INCLUDEPATH)
message(LIBDIR = $$LIBDIR)


