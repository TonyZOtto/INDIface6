# {Eclipse6}/src/useIfBase.pri
INCLUDEPATH *= $$LIBDIR/IfBase
LIBS *= -lIfBase6
LIBS *= -L$$DESTDIR
message(--------/src/useIfBase.pri LIBS=$$LIBS)
message(INCLUDEPATH = $$INCLUDEPATH)


