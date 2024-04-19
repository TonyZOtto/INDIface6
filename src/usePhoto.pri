# {Eclipse6}/src/usePhoto.pri
INCLUDEPATH *= $$LIBDIR/eIRphoto
LIBS *= -leIRphoto6
LIBS *= -L$$DESTDIR
message(--------/src/usePhoto.pri LIBS=$$LIBS)
message(INCLUDEPATH = $$INCLUDEPATH)


