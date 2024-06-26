# {Eclipse6}/src/useCore.pri
include(DESTDIR.pri)
INCLUDEPATH *= $$LIBDIR/eIRcore
LIBS *= -leIRcore6
LIBS *= -L$$DESTDIR
message(--------/src/useCore.pri LIBS=$$LIBS)
message(INCLUDEPATH = $$INCLUDEPATH)


