# {Eclipse6}/src/useExe.pri
include(DESTDIR.pri)
INCLUDEPATH *= $$LIBDIR/eIRexe
LIBS *= -leIRexe6
LIBS *= -L$$DESTDIR
message(--------/src/useExe.pri LIBS=$$LIBS)
message(INCLUDEPATH = $$INCLUDEPATH)


